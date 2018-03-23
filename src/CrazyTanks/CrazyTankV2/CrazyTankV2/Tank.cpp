
#include "stdafx.h"
#include "Tank.hpp"
tank::tank() {
	direction_ = D_NOTHING;
	coordinates_ = { 1,1 };
}
tank::tank(Direction direction, COORD coordinates) {
	direction_ = direction;
	coordinates_ = coordinates;
}
void tank::move() {

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
COORD tank::getNextCoord()  const {
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
void tank::changeDirection(Direction direction) {
	direction_ = direction;
}

Direction tank::getDirection() const {
	return direction_;
}

COORD tank::getCoord()const {
	return coordinates_;
}

