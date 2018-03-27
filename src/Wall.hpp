#ifndef WALL_HPP
#define WALL_HPP

#include "stdafx.h"
#include "Constants.h"

class Wall {
public:
	Wall(COORD coordinates);
	bool getDamage();
	bool isDamaged() const;
	const COORD& getCoord() const;
private:
	int strength_ = WALL_STRENGTH;
	COORD coordinates_;
};

#endif