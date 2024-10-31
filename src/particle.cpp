#include "particle.hpp"

void BaseParticle::render() {
	ofSetColor(200, 200, 200);
	ofRect(0,0, scale, scale);
}
glm::ivec2 BaseParticle::rules() {
	return(glm::ivec2(0, 0));
}

void BaseParticle::setNeighbours(vector<vector<std::shared_ptr<BaseParticle>>> v) {
	neighbours = v;
}

void Sand::render() {
	ofSetColor(212, 179, 102);
	ofRect(0, 0, scale, scale);
}

glm::ivec2 Sand::rules() {
	if (neighbours[2][1] == NULL) {
		return glm::ivec2(0, 1);
	}

	if (neighbours[2][0] == NULL) {
		return glm::ivec2(-1, 1);
	}

	if (neighbours[2][2] == NULL) {
		return glm::ivec2(1, 1);
	}
	return(glm::ivec2(0, 0));
}

void Water::render() {
	ofSetColor(69, 120, 186);
	ofRect(0,0, scale, scale);
}