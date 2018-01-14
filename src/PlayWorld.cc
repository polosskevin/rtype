#include "PlayWorld.h"

uint32_t PlayWorld::CreatePlayer(ge::Component const & component, Position const & position, Velocity const & velocities, Sprite const & sprite) {
	uint32_t id = GetEmptyIndex_();
	entities_[id] = component;
	positions_[id] = position;
	velocities_[id] = velocities;
	sprites_[id] = sprite;
	return id;
}

uint32_t PlayWorld::CreateCross(ge::Component const & component, Position const &position, Sprite const & sprite) {
	uint32_t id = GetEmptyIndex_();
	entities_[id] = component;
	positions_[id] = position;
	sprites_[id] = sprite;
	return id;
}

Sprite &PlayWorld::Sprites(uint32_t id) {
	return sprites_[id];
}

Position & PlayWorld::Positions(uint32_t id) {
	return positions_[id];
}

Velocity & PlayWorld::Velocities(uint32_t id) {
	return velocities_[id];
}