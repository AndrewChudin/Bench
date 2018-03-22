#pragma once
#include "stdafx.h"

class Wall {
public:
	Wall(COORD coordinates);
	bool GetDamage();
	bool IsDamaged() const;
	COORD GetCoord() const;
private:
	char strength_ = 2;
	COORD coordinates_;
};

