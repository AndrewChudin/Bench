#pragma once
#include "stdafx.h"

class Bullet {
public:
	bool Bullet::isEnemy() const;
	Bullet(Direction direction, COORD coords, bool is_enemy);
	void move();
	Direction getDirection() const;
	COORD getCoord() const;
	COORD getNextCoord() const;
private:
	Direction direction_;
	bool is_enemy_;
	COORD coordinates_;
};

