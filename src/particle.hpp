#pragma once

#include "ofMain.h"

class BaseParticle {
	public:
		BaseParticle(glm::vec2 position, int scale) : position{ position }, scale{ scale } 
		{

		};
		
		virtual ~BaseParticle() = default;

		virtual void render();
		virtual glm::ivec2 rules();
		void setNeighbours(vector<vector<std::shared_ptr<BaseParticle>>> v);

		glm::vec2 position;
		int scale;
		virtual float density() const;

		bool updated = false;
		bool destroy = false;
		
		vector<vector<std::shared_ptr<BaseParticle>>> neighbours;

		ofSoundPlayer spawnSound;
};

class Sand : public BaseParticle {
	public:
		Sand(glm::vec2 position, int scale) : BaseParticle(position, scale) 
		{
			spawnSound.load("C:/Users/oproulx/source/repos/of_v0.12.0/of_v0.12.0_vs_release/apps/myApps/PhysicsParticles/assets/PlaceSand.wav", false);
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
		spawnSound.load("C:/Users/oproulx/source/repos/of_v0.12.0/of_v0.12.0_vs_release/apps/myApps/PhysicsParticles/assets/PlaceWater.mp3", false);
		spawnSound.play();
	};

	void render() override;
	glm::ivec2 rules() override;
	float density() const override;

	bool left = true;

	int lifetime = 100;

};