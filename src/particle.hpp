#pragma once

#include "ofMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>

class BaseParticle {
	public:
		BaseParticle(glm::vec2 position, int scale) : position{ position }, scale{ scale } {};
		
		virtual ~BaseParticle() = default;

		virtual void render();
		glm::vec2 position;
		int scale;
};

class Sand : public BaseParticle {
	public:
		Sand(glm::vec2 position, int scale) : BaseParticle(position, scale) {};

		void render() override;
};

class Water : public BaseParticle {
public:
	Water(glm::vec2 position, int scale) : BaseParticle(position, scale) {};

	void render() override;
};