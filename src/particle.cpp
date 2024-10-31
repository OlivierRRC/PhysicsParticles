#include "particle.hpp"

void BaseParticle::render() {
	ofSetColor(200, 200, 200);
	ofRect(0,0, scale, scale);
}
glm::ivec2 BaseParticle::rules() {
	return(glm::ivec2(0, 0));
}

float BaseParticle::density() const {
	return 1;
}

void BaseParticle::setNeighbours(vector<vector<std::shared_ptr<BaseParticle>>> v) {
	neighbours = v;
}

void Sand::render() {
	ofSetColor(212, 179, 102);
	ofRect(0, 0, scale, scale);
}

glm::ivec2 Sand::rules() {
	//check directly below, move directly below
	if (neighbours[2][1] == NULL || neighbours[2][1]->density() < density()) {
		return glm::ivec2(0, 1);
	}

	//check bottom left and regular left, move bottom left
	if (neighbours[2][0] == NULL || neighbours[2][0]->density() < density()) {
		if (neighbours[1][0] == NULL || neighbours[1][0]->density() < density()) {
			return glm::ivec2(-1, 1);
		}		
	}

	//check bottom right and regular right, move bottom right
	if (neighbours[2][2] == NULL || neighbours[2][2]->density() < density()) {
		if (neighbours[1][2] == NULL || neighbours[1][2]->density() < density()) {
			return glm::ivec2(1, 1);
		}
	}
	return(glm::ivec2(0, 0));
}

float Sand::density() const {
	return 0.5;
}

void Water::render() {
	ofSetColor(69, 120, 186);
	ofRect(0,0, scale, scale);
}

glm::ivec2 Water::rules() {

	//check directly below, move directly below
	if (neighbours[2][1] == NULL || neighbours[2][1]->density() < density()) {
		return glm::ivec2(0, 1);
	}

	if (left) {
		//check regular left, move left
		if (neighbours[1][0] == NULL || neighbours[1][0]->density() < density()) {
			return glm::ivec2(-1, 0);
		}
		left = false;
	}

	if (!left) {
		//check regular right, move right
		if (neighbours[1][2] == NULL || neighbours[1][2]->density() < density()) {
			return glm::ivec2(1, 0);
		}
		left = true;
	}


	return(glm::ivec2(0, 0));
}

float Water::density() const {
	return 0.2;
}