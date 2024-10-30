#pragma once

#include "ofMain.h"

class BaseParticle {
	public:
		BaseParticle(glm::vec2 position, int scale) : position{ position }, scale{ scale } {};
		
		virtual ~BaseParticle() = default;

		virtual void render();
		virtual void rules();
		glm::vec2 position;
		int scale;
};

class Sand : public BaseParticle {
	public:
		Sand(glm::vec2 position, int scale) : BaseParticle(position, scale) {};

		void render() override;
		void rules() override;
};

class Water : public BaseParticle {
public:
	Water(glm::vec2 position, int scale) : BaseParticle(position, scale) {};

	void render() override;
};