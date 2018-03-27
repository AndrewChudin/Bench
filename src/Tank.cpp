
#include "stdafx.h"
#include "Tank.hpp"

Tank::Tank(Direction direction, COORD coordinates) {
	direction_ = direction;
	coordinates_ = coordinates;
}
void Tank::move() {

	switch (direction_)
	{
	case(D_UP):
		coordinates_.Y--;
	break;
	case(D_DOWN):
		coordinates_.Y++;
	break;
	case(D_LEFT):
		coordinates_.X--;
	break;
	case(D_RIGHT):
		coordinates_.X++;
	break;
	default:
		break;
	}
}
COORD Tank::getNextCoord()  const {
	switch (direction_)
	{
	case(D_UP):
		return { coordinates_.X, coordinates_.Y - 1 };
		break;
	case(D_DOWN):
		return { coordinates_.X, coordinates_.Y + 1 };
		break;
	case(D_LEFT):
		return { coordinates_.X - 1, coordinates_.Y };
		break;
	case(D_RIGHT):
		return { coordinates_.X + 1, coordinates_.Y };
		break;
	default: return { 0, 0 };
			 break;
	}
}
void Tank::changeDirection(const Direction& direction) {
	direction_ = direction;
}

const Direction& Tank::getDirection() const {
	return direction_;
}

const COORD& Tank::getCoord()const {
	return coordinates_;
}

void Tank::setCoord(const COORD & coord)
{
	coordinates_ = coord;
}

