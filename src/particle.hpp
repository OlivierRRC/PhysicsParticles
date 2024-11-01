#pragma once

#include "ofMain.h"

class BaseParticle {
	public:
		BaseParticle(glm::vec2 position, int scale) : position{ position }, scale{ scale } {};
		
		virtual ~BaseParticle() = default;

		virtual void render();
		virtual glm::ivec2 rules();
		void setNeighbours(vector<vector<std::shared_ptr<BaseParticle>>> v);

		glm::vec2 position;
		int scale;
		virtual float density() const;

		bool updated = false;
		
		vector<vector<std::shared_ptr<BaseParticle>>> neighbours;
};

class Sand : public BaseParticle {
	public:
		Sand(glm::vec2 position, int scale) : BaseParticle(position, scale) {};

		void render() override;
		glm::ivec2 rules() override;
		float density() const override;
};

class Water : public BaseParticle {
public:
	Water(glm::vec2 position, int scale) : BaseParticle(position, scale) {};

	void render() override;
	glm::ivec2 rules() override;
	float density() const override;

	bool left = true;

	int lifetime = 5;

};