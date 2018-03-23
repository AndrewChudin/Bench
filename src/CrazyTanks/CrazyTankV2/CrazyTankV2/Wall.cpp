
#include "stdafx.h"
#include "Wall.hpp"
Wall::Wall(COORD coordinates) {
	coordinates_ = coordinates;
}
bool Wall::getDamage() {
	strength_--;
	return strength_ <= 1;
}

bool Wall::isDamaged()  const {
	return strength_ != 2;
}

COORD Wall::getCoord()  const {
	return coordinates_;
}

