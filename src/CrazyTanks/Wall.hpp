#pragma once
#include "stdafx.h"

class Wall {
public:
	Wall(COORD coordinates);
	bool getDamage();
	bool isDamaged() const;
	COORD getCoord() const;
private:
	char strength_ = 2;
	COORD coordinates_;
};

