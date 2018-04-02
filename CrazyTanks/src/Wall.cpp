
#include "stdafx.h"
#include "Wall.hpp"
Wall::Wall(COORD coordinates) {
	coordinates_ = coordinates;
}
bool Wall::getDamage() {
	strength_--;
	return strength_ <= 0;
}

bool Wall::isDamaged()  const {
	return strength_ != WALL_STRENGTH;
}

const COORD& Wall::getCoord()  const {
	return coordinates_;
}

