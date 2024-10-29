#pragma once

#include "ofMain.h"

class BaseParticle {
	public:
		BaseParticle(glm::vec2 pos, int s) {
			position = pos;
			scale = s;
		}
		
		void render();
		glm::vec2 position;
		int scale;
};
