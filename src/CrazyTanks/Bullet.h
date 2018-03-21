
#if !defined(_BULLET_H)
#define _BULLET_H

#include "stdafx.h"

class Bullet {
public:
	bool Bullet::IsEnemy();
	Bullet(Direction direction, COORD coords, bool is_enemy);
	void Move();
	Direction GetDirection();
	COORD GetCoord();
	COORD GetNextCoord();
protected:
	Direction direction_;
	bool is_enemy_;
	COORD coordinates_;
};

#endif  //_BULLET_H
