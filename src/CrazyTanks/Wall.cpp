
#include "stdafx.h"
#include "Wall.h"
Wall::Wall(COORD coordinates) {
	coordinates_ = coordinates;
}
bool Wall::GetDamage() {
	if (strength_ == 1)
		return true;
	strength_--;
	return false;
}

bool Wall::IsDamaged() {
	if (strength_ != 2)
		return true;
	else
		return false;
}

COORD Wall::GetCoord() {
	return coordinates_;
}

