#include "particle.hpp"

void BaseParticle::render() {
	ofSetColor(200, 200, 200);
	ofRect(position.x* scale, position.y* scale, scale, scale);
}



	void Sand::render() {
		std::cout << "aaaa";
	}