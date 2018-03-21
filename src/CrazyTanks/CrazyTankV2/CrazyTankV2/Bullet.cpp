
#include "stdafx.h"
#include "Bullet.h"
Bullet::Bullet(Direction direction, COORD coordinates, bool is_enemy) {
	direction_ = direction;
	coordinates_ = coordinates;
	is_enemy_ = is_enemy;
}

COORD Bullet::GetCoord() {
	return coordinates_;
}
Direction Bullet::GetDirection() {
	return direction_;
}
bool Bullet::IsEnemy() {
	return is_enemy_;
}
COORD Bullet::GetNextCoord() {
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
		return { coordinates_.X + 1, coordinates_.Y };;
	break;
	default: return { 0, 0 };
			 break;
	}
}

void Bullet::Move() {
	switch (direction_)
	{
	case(D_UP): coordinates_.Y--; break;
	case(D_DOWN): coordinates_.Y++; break;
	case(D_LEFT): coordinates_.X--; break;
	case(D_RIGHT): coordinates_.X++; break;
	default:
		break;
	}
}
