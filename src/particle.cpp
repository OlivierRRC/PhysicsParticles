#include "particle.hpp"

void BaseParticle::render() {
	ofSetColor(200, 200, 200);
	ofRect(0,0, scale, scale);
}
void BaseParticle::rules() {

}

void Sand::render() {
	ofSetColor(212, 179, 102);
	ofRect(0, 0, scale, scale);
}

void Sand::rules() {
	//position.y += 1;
}

void Water::render() {
	ofSetColor(69, 120, 186);
	ofRect(0,0, scale, scale);
}