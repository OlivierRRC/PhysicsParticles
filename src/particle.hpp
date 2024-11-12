#pragma once

#include "ofMain.h"

class BaseParticle {
	public:
		BaseParticle(glm::ivec2 position, int scale) : position{ position }, scale{ scale }{};
		
		virtual ~BaseParticle() = default;

		virtual void render();
		virtual glm::ivec2 rules();
		void setNeighbours(vector<vector<std::shared_ptr<BaseParticle>>> v);

		glm::ivec2 position;
		int scale;
		virtual float density() const;

		bool updated = true;
		bool destroy = false;
		
		vector<vector<std::shared_ptr<BaseParticle>>> neighbours;

		ofSoundPlayer spawnSound;
};

class Sand : public BaseParticle {
	public:
		Sand(glm::vec2 position, int scale) : BaseParticle(position, scale) 
		{
			spawnSound.load("PlaceSand.wav", false);
			spawnSound.play();
		};

		void render() override;
		glm::ivec2 rules() override;
		float density() const override;
};

class Water : public BaseParticle {
public:
	Water(glm::vec2 position, int scale) : BaseParticle(position, scale) 
	{
		spawnSound.load("PlaceWater.mp3", false);
		spawnSound.play();
	};

	void render() override;
	glm::ivec2 rules() override;
	vector<vector<std::shared_ptr<BaseParticle>>> spread(vector<vector<std::shared_ptr<BaseParticle>>> v);

	float density() const override;

	bool left = true;

	int lifetime = 100;

	float fullness = 1.0f;
};