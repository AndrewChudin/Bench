
#include "stdafx.h"
#include "Tank.h"
Tank::Tank() {
	direction_ = D_NOTHING;
	coordinates_ = { 1,1 };
}
Tank::Tank(Direction direction, COORD coordinates) {
	direction_ = direction;
	coordinates_ = coordinates;
}
void Tank::Move() {

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
COORD Tank::GetNextCoord() {
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
void Tank::ChangeDirection(Direction direction) {
	direction_ = direction;
}

Direction Tank::GetDirection() {
	return direction_;
}

COORD Tank::GetCoord() {
	return coordinates_;
}

