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
	ofRect(0,scale * (1- fullness), scale, scale*fullness);
}

glm::ivec2 Water::rules() {
	//
	//Make some way for the water to spawn itself on either side of itself (with 1/3 of the water)
	//the water should fall down, then move diagonally if it hits something
	// then the water should spread horizontally with the 1/3 technique
	// Water sould also be able to spread in one direction while only halfing itself
	//

	//check directly below, move directly below
	if (neighbours[2][1] == NULL || neighbours[2][1]->density() < density()) {
		//lifetime = 15;
		return glm::ivec2(0, 1);
	}

	//check bottom left and regular left, move bottom left
	if (neighbours[2][0] == NULL || neighbours[2][0]->density() < density()) {
		if (neighbours[1][0] == NULL || neighbours[1][0]->density() < density()) {
			//lifetime = 15;
			return glm::ivec2(-1, 1);
		}
	}

	//check bottom right and regular right, move bottom right
	if (neighbours[2][2] == NULL || neighbours[2][2]->density() < density()) {
		if (neighbours[1][2] == NULL || neighbours[1][2]->density() < density()) {
			//lifetime = 15;
			return glm::ivec2(1, 1);
		}
	}

	//if (lifetime <= 0) {
	//	shared_ptr<Water> water = dynamic_pointer_cast<Water>(neighbours[2][1]);
	//	if (water != NULL) {
	//		//water->lifetime = 5;
	//	}
	//	water = dynamic_pointer_cast<Water>(neighbours[0][0]);
	//	if (water != NULL) {
	//		//water->lifetime = 5;
	//	}
	//	water = dynamic_pointer_cast<Water>(neighbours[0][2]);
	//	if (water != NULL) {
	//		//water->lifetime = 5;
	//	}
	//	return(glm::ivec2(0, 0));
	//}

	if (left) {
		//check regular left, move left
		if (neighbours[1][0] == NULL || neighbours[1][0]->density() < density()) {
			
			lifetime--;
			if (ofRandom(1) > 0.5) {
				return glm::ivec2(-1, 0);	
			}
			else {
				return glm::ivec2(0, 0);;
			}

			
		}
		left = false;
		
	}

	if (!left) {
		//check regular right, move right
		if (neighbours[1][2] == NULL || neighbours[1][2]->density() < density()) {
			
			lifetime--;
			if (ofRandom(1) > 0.5) {
				return glm::ivec2(1, 0);
			}
			else {
				return glm::ivec2(0, 0);;
			}
			
		}
		left = true;
		
	}

	return(glm::ivec2(0, 0));
}

vector<vector<std::shared_ptr<BaseParticle>>> Water::spread(vector<vector<std::shared_ptr<BaseParticle>>> v) {

	
		//bottom neighbour water
		shared_ptr<Water> water = dynamic_pointer_cast<Water>(neighbours[2][1]);
		if (water != NULL) {
			if (water->fullness < 1) {
				water->fullness += fullness;
				destroy = true;
			}
		}

		water = dynamic_pointer_cast<Water>(neighbours[1][2]);
		shared_ptr<Water> water2 = dynamic_pointer_cast<Water>(neighbours[1][0]);
		if (water != NULL && water2 != NULL) {
			float newFUll = (water->fullness + water2->fullness + fullness) / 3;
			water->fullness = newFUll;
			water2->fullness = newFUll;
			fullness = newFUll;
			return v;
		}

		//left neighbour is water
		water = dynamic_pointer_cast<Water>(neighbours[1][2]);
		if (water != NULL) {
			if (water->fullness < fullness) {
				float newFUll = (water->fullness + fullness) / 2;
				water->fullness = newFUll;
				fullness = newFUll;
				return v;
			}
		}
		//right neighbour is water
		water = dynamic_pointer_cast<Water>(neighbours[1][0]);
		if (water != NULL) {
			if (water->fullness < fullness) {
				float newFUll = (water->fullness + fullness) / 2;
				water->fullness = newFUll;
				fullness = newFUll;
				return v;
			}
		}

		if (fullness > 1) {
			if (neighbours[0][1] == NULL) {
				shared_ptr temp = std::make_shared<Water>(glm::vec2(position.x, position.y - 1), scale);
				temp->fullness = fullness - 1;
				fullness -= temp->fullness;
				v[position.y - 1][position.x] = temp;
				return v;
			}
			water = dynamic_pointer_cast<Water>(neighbours[0][1]);
			if (water != NULL) {
				water->fullness += fullness - 1;
				fullness = 1;
			}
		}

		if (fullness > 0.001f) {
		//both neighbour is empty
		if (neighbours[1][2] == NULL && neighbours[1][0] == NULL) {
			shared_ptr temp = std::make_shared<Water>(glm::vec2(position.x + 1, position.y), scale);
			shared_ptr temp2 = std::make_shared<Water>(glm::vec2(position.x - 1, position.y), scale);
			temp->fullness = fullness / 3;
			temp2->fullness = fullness / 3;
			fullness = fullness / 3;
			v[position.y][position.x + 1] = temp;
			v[position.y][position.x - 1] = temp2;
			return v;
		}

		//left neighbour is empty
		if (neighbours[1][2] == NULL) {
			shared_ptr temp = std::make_shared<Water>(glm::vec2(position.x + 1, position.y), scale);
			temp->fullness = fullness / 2;
			fullness = fullness / 2;
			v[position.y][position.x + 1] = temp;
			return v;
		}
		//right neighbour is empty
		if (neighbours[1][0] == NULL) {
			shared_ptr temp = std::make_shared<Water>(glm::vec2(position.x - 1, position.y), scale);
			temp->fullness = fullness / 2;
			fullness = fullness / 2;
			v[position.y][position.x - 1] = temp;
			return v;
		}



	}
		else {
			destroy = true;
		}



	return v;
}

float Water::density() const {
	return 0.2;
}