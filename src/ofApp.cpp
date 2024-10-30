#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	windowSize = floor(ofGetWindowSize()/10);

	v = std::vector<std::vector<std::unique_ptr<BaseParticle>>>(windowSize.y);

	for (auto& row : v) {
		row.resize(windowSize.x);
	}

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	for (size_t y = 0; y < v.size(); y++)
	{
		for (size_t x = 0; x < v[0].size(); x++)
		{
			if (v[y][x] != NULL) {
				v[y][x]->render();
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

	int clampY = std::clamp(y/10, 0, (int)v.size()-1);
	int clampX = std::clamp(x/10, 0, (int)v[0].size()-1);

	switch (button)
	{
	case 0:
		v[clampY][clampX] = std::make_unique<Sand>(glm::vec2(clampX, clampY), 10);
		break;
	case 2:
		v[clampY][clampX] = std::make_unique<Water>(glm::vec2(clampX, clampY), 10);
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
	windowSize = floor(ofGetWindowSize() / 10); //get the window size divided by how many pixels the cells should be
	ofSetWindowShape(windowSize.x*10, windowSize.y*10); //round the window size to snap to be pixel perfect

	v.resize(windowSize.y);

	for (auto& row : v) {
		row.resize(windowSize.x);
	}
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
