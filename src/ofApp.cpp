#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	windowSize = floor(ofGetWindowSize()/ unitSize);
	resizeVector();

	

}

//--------------------------------------------------------------
void ofApp::update(){
	//for (size_t y = 0; y < v.size(); y++)
	//{
	//	for (size_t x = 0; x < v[0].size(); x++)
	//	{
	//		if (v[y][x] != NULL) {
	//			v[y][x]->rules();
	//			if (y + 1 < v.size()) {
	//				swap(v[y][x], v[y+1][x]);
	//			}

	//		}
	//	}
	//}

	//for (size_t y = v.size()-1; y != -1; y--) //size_t is unsigned so I have to use a funky for loop
	//{
	//	for (size_t x = 0; x < v[0].size(); x++)
	//	{
	//		if (v[y][x] != NULL) {
	//			//v[y][x]->rules();
	//			if (y + 1 < v.size()) {
	//				if (v[y + 1][x] == NULL) {
	//					swap(v[y][x], v[y + 1][x]);
	//				}

	//				if (x + 1 < v[y].size()) {
	//					if (v[y + 1][x + 1] == NULL)
	//					swap(v[y][x], v[y + 1][x+1]);
	//				}

	//				if ((int)x - 1 >= 0) {//size_t is unsigned so I have to cast to int to check if it's greater than 0;
	//					if (v[y + 1][x - 1] == NULL) {
	//						swap(v[y][x], v[y + 1][x - 1]);
	//					}
	//				}

	//			}
	//		}
	//	}
	//}

	for (size_t y = v.size()-1; y != -1; y--) //size_t is unsigned so I have to use a funky for loop
	{
		for (size_t x = 0; x < v[0].size(); x++)
		{
			if (v[y][x] != NULL) {
				gatherNeighbours(x, y);
				glm::ivec2 delta = v[y][x].get()->rules();
				swap(v[y][x], v[y + delta.y][x + delta.x]);
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
		v[clampY][clampX] = NULL;
		return;
	}
	placeParticle(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (shiftDown) {
		int clampY = std::clamp(y / unitSize, 0, (int)v.size() - 1);
		int clampX = std::clamp(x / unitSize, 0, (int)v[0].size() - 1);
		v[clampY][clampX] = NULL;
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

	cout << windowSize << "\n";
	cout << v.size() << ", " << v[0].size() << "\n";

	//for (size_t y = v.size() - 1; y != -1; y--) //size_t is unsigned so I have to use a funky for loop
	//{
	//	for (size_t x = 0; x < v[0].size(); x++)
	//	{
	//		if (v[y][x] != NULL) {
	//			gatherNeighbours(x, y);
	//		}
	//	}
	//}

}

void ofApp::placeParticle(int x, int y, int button) {
	int clampY = std::clamp(y / unitSize, 0, (int)v.size() - 1);
	int clampX = std::clamp(x / unitSize, 0, (int)v[0].size() - 1);

	switch (button)
	{
	case 0:
		v[clampY][clampX] = std::make_unique<Sand>(glm::vec2(clampX, clampY), unitSize);
		break;
	case 2:
		v[clampY][clampX] = std::make_unique<Water>(glm::vec2(clampX, clampY), unitSize);
		break;
	default:
		break;
	}

	gatherNeighbours(clampX, clampY);

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
				temp[i + 1][j + 1] = std::make_unique<BaseParticle>(glm::vec2(x, y), unitSize);
				continue;
			}
			if (x + j < 0 || x + j > v[0].size() - 1) {
				temp[i + 1][j + 1] = std::make_unique<BaseParticle>(glm::vec2(x, y), unitSize);
				continue;
			}

			if (v[y + i][x + j] != NULL) {
				temp[i + 1][j + 1] = v[y+i][x+j];
			}
		}
	}

	v[y][x]->setNeighbours(temp);

}