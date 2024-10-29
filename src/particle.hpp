#pragma once

#include "ofMain.h"

class BaseParticle {
	public:
		BaseParticle(glm::vec2 pos, int s) {
			position = pos;
			scale = s;
		}
		
		virtual void render();
		glm::vec2 position;
		int scale;
};

class Sand : BaseParticle {
	public:
		Sand(glm::vec2 position, int s) : BaseParticle(position, s) {};

		void render() override;
};