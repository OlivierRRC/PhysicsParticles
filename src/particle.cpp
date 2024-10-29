#include "particle.hpp"

void BaseParticle::render() {
	ofRect(position.x* scale, position.y* scale, scale, scale);
}