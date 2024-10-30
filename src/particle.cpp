#include "particle.hpp"

void BaseParticle::render() {
	ofSetColor(200, 200, 200);
	ofRect(position.x* scale, position.y* scale, scale, scale);
}

void Sand::render() {
	ofSetColor(212, 179, 102);
	ofRect(position.x * scale, position.y * scale, scale, scale);
}

void Water::render() {
	ofSetColor(69, 120, 186);
	ofRect(position.x * scale, position.y * scale, scale, scale);
}