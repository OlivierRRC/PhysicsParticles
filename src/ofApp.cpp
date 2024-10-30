#include "ofApp.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>

//--------------------------------------------------------------
void ofApp::setup(){
	
	//vector<bool*> row(40);
	//vector<vector<bool*>> col(40, row);
	
	//vector<std::unique_ptr<BaseParticle>> row(40);
	//vector<vector<std::unique_ptr<BaseParticle>>> col(40, row);

	v = std::vector<std::vector<std::unique_ptr<BaseParticle>>>(40);

	for (auto& row : v) {
		row.resize(40);
	}

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	for (size_t y = 0; y < 40; y++)
	{
		for (size_t x = 0; x < 40; x++)
		{
			if (v[x][y] != NULL) {
				v[x][y]->render();
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
	//std::cout << x / 10 << ", " << y / 10 << "\n";
	
	//v1.emplace_back(std::make_unique<BaseParticle>(glm::vec2(x / 10, y / 10), 10));

	//v1[0] = std::make_unique<Sand>(glm::vec2(x / 10, y / 10), 10);

	int clampY = std::clamp(y/10, 0, (int)v.size()-1);
	int clampX = std::clamp(x/10, 0, (int)v[0].size()-1);

	//std::cout << clampX << ", " << clampY << "\n";

	switch (button)
	{
	case 0:
		v[clampX][clampY] = std::make_unique<Sand>(glm::vec2(clampX, clampY), 10);
		break;
	case 2:
		v[clampX][clampY] = std::make_unique<Water>(glm::vec2(clampX, clampY), 10);
		break;
	default:
		break;
	}

	
	//v[0][0] = std::make_unique<BaseParticle>(glm::vec2(x / 10, y / 10), 10);
	//v[x / 10][y / 10] = true;

	//for (int i = 0; i < v.size(); i++) {
	//	for (int j = 0; j < v[i].size(); j++)
	//		cout << v[i][j] << " ";
	//	cout << endl;
	//}
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
