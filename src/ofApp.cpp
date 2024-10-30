#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	windowSize = floor(ofGetWindowSize()/ unitSize);
	resizeVector();

	

}

//--------------------------------------------------------------
void ofApp::update(){
	for (size_t y = 0; y < v.size(); y++)
	{
		for (size_t x = 0; x < v[0].size(); x++)
		{
			if (v[y][x] != NULL) {
				v[y][x]->rules();
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
		cout << v.size();
		cout << v[0].size();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	placeParticle(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
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
		v[clampY][clampX] = std::make_unique<Sand>(glm::vec2(clampX, clampY), unitSize);
		break;
	case 2:
		v[clampY][clampX] = std::make_unique<Water>(glm::vec2(clampX, clampY), unitSize);
		break;
	default:
		break;
	}
}