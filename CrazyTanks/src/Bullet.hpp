#ifndef BULLET_HPP
#define BULLET_HPP
#include "stdafx.h"
#include "Constants.h"
class Bullet {
public:
	bool Bullet::isEnemy() const;
	Bullet(const Direction& direction, const COORD& coords, bool is_enemy);
	void move();
	const Direction& getDirection() const;
	const COORD& getCoord() const;
	COORD getNextCoord() const;
private:
	Direction direction_;
	bool is_enemy_;
	COORD coordinates_;
};
#endif

