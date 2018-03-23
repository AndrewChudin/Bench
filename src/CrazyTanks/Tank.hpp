#pragma once
#include "stdafx.h"

class tank {
public:
	tank::tank();
	tank(Direction direction, COORD coords);
	void move();
	void changeDirection(Direction direction);
	Direction getDirection() const;
	COORD getCoord() const;
	COORD getNextCoord() const;
private:
	Direction direction_;
	COORD coordinates_;
};
