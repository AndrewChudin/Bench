
#if !defined(_TANK_H)
#define _TANK_H
#include "stdafx.h"


class Tank {
public:
	Tank::Tank();
	Tank(Direction direction, COORD coords);
	void Move();
	void ChangeDirection(Direction direction);
	Direction GetDirection();
	COORD GetCoord();
	COORD GetNextCoord();
protected:
	Direction direction_;
	COORD coordinates_;
};

#endif  //_TANK_H
