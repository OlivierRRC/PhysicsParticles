#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	windowSize = floor(ofGetWindowSize()/ unitSize);
	resizeVector();
	//bgMusic.load("C:/Users/oproulx/source/repos/of_v0.12.0/of_v0.12.0_vs_release/apps/myApps/PhysicsParticles/assets/BGMusic.mp3", false);
	bgMusic.load("BGMusic.mp3", false);
	bgMusic.play();
	bgMusic.setLoop(true);

}

//--------------------------------------------------------------
void ofApp::update(){
	for (size_t y = v.size()-1; y != -1; y--) //size_t is unsigned so I have to use a funky for loop
	{
		for (size_t x = 0; x < v[0].size(); x++)
		{
			if (v[y][x] != NULL && v[y][x]->updated == false) {

				gatherNeighbours(x, y);
				glm::ivec2 delta = v[y][x].get()->rules();

				shared_ptr<Water> water = dynamic_pointer_cast<Water>(v[y][x]);

				if (delta != glm::ivec2(0, 0)) {
					v[y][x]->updated = true;

					v[y][x]->position = glm::vec2(x + delta.x, y + delta.y);

					if (v[y + delta.y][x + delta.x] != NULL) {
						v[y + delta.y][x+ delta.x]->position = glm::ivec2(x, y);
					}


					swap(v[y][x], v[y + delta.y][x + delta.x]);
				}
				else if (water != NULL) {
					v = water->spread(v);
				}
			}
		}
	}

	//loop through everything
	//set the particle to be un-updated
	//remove unused particles from array
	//remvoe unused particles neighbours
	for (size_t y = v.size() - 1; y != -1; y--) //size_t is unsigned so I have to use a funky for loop
	{
		for (size_t x = 0; x < v[0].size(); x++)
		{
			if (v[y][x] != NULL) {
				if (v[y][x]->destroy == true) {
					
					vector<vector<std::shared_ptr<BaseParticle>>> empty;
					empty.resize(3);
					for (auto& row : empty) {
						row.resize(3);
					}

					v[y][x]->setNeighbours(empty);
					v[y][x] = NULL;
					continue;
				}
				v[y][x]->updated = false;
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	for (size_t y = 0; y < v.size(); y++)
	{
		for (size_t x = 0; x < v[0].size(); x++)
		{
			if (v[y][x] != NULL) {
				ofPushMatrix();
				ofTranslate(x*unitSize, y*unitSize);
				v[y][x]->render();
				ofPopMatrix();
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//c and C key
	if (key == 99 || key == 67) {
		v.resize(0);
		v.resize(windowSize.y);
		for (auto& row : v) {
			row.resize(windowSize.x);
		}
	}
	//right and left shift keys
	if (key == 3681 || key == 3680) {
		shiftDown = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	//right and left shift keys
	if (key == 3681 || key == 3680) {
		shiftDown = false;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (shiftDown) {
		int clampY = std::clamp(y / unitSize, 0, (int)v.size() - 1);
		int clampX = std::clamp(x / unitSize, 0, (int)v[0].size() - 1);
		if (v[clampY][clampX] != NULL) {
			v[clampY][clampX]->destroy = true;
		}
		
		return;
	}
	placeParticle(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (shiftDown) {
		int clampY = std::clamp(y / unitSize, 0, (int)v.size() - 1);
		int clampX = std::clamp(x / unitSize, 0, (int)v[0].size() - 1);
		if (v[clampY][clampX] != NULL) {
			v[clampY][clampX]->destroy = true;
		}
		return;
	}
	placeParticle(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	resizeVector();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::resizeVector() {
	windowSize = floor(ofGetWindowSize() / unitSize); //get the window size divided by how many pixels the cells should be
	ofSetWindowShape(windowSize.x * unitSize, windowSize.y * unitSize); //round the window size to snap to be pixel perfect

	v.resize(windowSize.y);

	for (auto& row : v) {
		row.resize(windowSize.x);
	}
}

void ofApp::placeParticle(int x, int y, int button) {
	int clampY = std::clamp(y / unitSize, 0, (int)v.size() - 1);
	int clampX = std::clamp(x / unitSize, 0, (int)v[0].size() - 1);

	switch (button)
	{
	case 0:
		v[clampY][clampX] = std::make_unique<Sand>(glm::ivec2(clampX, clampY), unitSize);
		break;
	case 1:
		v[clampY][clampX] = std::make_unique<BaseParticle>(glm::ivec2(clampX, clampY), unitSize);
		break;
	case 2:
		v[clampY][clampX] = std::make_unique<Water>(glm::ivec2(clampX, clampY), unitSize);
		break;
	default:
		break;
	}

}

void ofApp::gatherNeighbours(int x, int y) {
	vector<vector<std::shared_ptr<BaseParticle>>> temp;
	temp.resize(3);
	for (auto& row : temp) {
		row.resize(3);
	}
	
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (y + i < 0 || y + i > v.size() - 1) {
				temp[i + 1][j + 1] = std::make_unique<BaseParticle>(glm::ivec2(x, y), unitSize);
				continue;
			}
			if (x + j < 0 || x + j > v[0].size() - 1) {
				temp[i + 1][j + 1] = std::make_unique<BaseParticle>(glm::ivec2(x, y), unitSize);
				continue;
			}

			if (v[y + i][x + j] != NULL) {
				temp[i + 1][j + 1] = v[y+i][x+j];
			}
		}
	}

	v[y][x]->setNeighbours(temp);

}