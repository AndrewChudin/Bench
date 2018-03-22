
#include "stdafx.h"
#include "Wall.hpp"
Wall::Wall(COORD coordinates) {
	coordinates_ = coordinates;
}
bool Wall::GetDamage() {
	strength_--;
	return strength_ <= 1;
}

bool Wall::IsDamaged()  const {
	return strength_ != 2;
}

COORD Wall::GetCoord()  const {
	return coordinates_;
}

