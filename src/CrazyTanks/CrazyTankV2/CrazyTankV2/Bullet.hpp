#pragma once
#include "stdafx.h"

class Bullet {
public:
	bool Bullet::IsEnemy() const;
	Bullet(Direction direction, COORD coords, bool is_enemy);
	void Move();
	Direction GetDirection() const;
	COORD GetCoord() const;
	COORD GetNextCoord() const;
private:
	Direction direction_;
	bool is_enemy_;
	COORD coordinates_;
};

