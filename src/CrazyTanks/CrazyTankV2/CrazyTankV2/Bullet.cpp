
#include "stdafx.h"
#include "Bullet.hpp"
Bullet::Bullet(Direction direction, COORD coordinates, bool is_enemy) {
	direction_ = direction;
	coordinates_ = coordinates;
	is_enemy_ = is_enemy;
}

COORD Bullet::getCoord() const {
	return coordinates_;
}
Direction Bullet::getDirection() const {
	return direction_;
}
bool Bullet::isEnemy() const {
	return is_enemy_;
}
COORD Bullet::getNextCoord() const{
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

void Bullet::move() {
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
