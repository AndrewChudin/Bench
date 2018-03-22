#pragma once
#include "stdafx.h"

class Tank {
public:
	Tank::Tank();
	Tank(Direction direction, COORD coords);
	void Move();
	void ChangeDirection(Direction direction);
	Direction GetDirection() const;
	COORD GetCoord() const;
	COORD GetNextCoord() const;
private:
	Direction direction_;
	COORD coordinates_;
};
