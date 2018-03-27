#ifndef TANK_HPP
#define TANK_HPP

#include "stdafx.h"
#include "Constants.h"

class Tank {
public:
	Tank();
	Tank(Direction direction, COORD coords);
	void move();
	void changeDirection(const Direction& direction);
	const Direction& getDirection() const;
	const COORD& getCoord() const;
	void setCoord(const COORD& coord);
	COORD getNextCoord() const;
private:
	Direction direction_;
	COORD coordinates_;
};

#endif