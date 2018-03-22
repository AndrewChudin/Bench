#pragma once
#include "DrawStrategy.hpp"
class DrawableWall :public DrawStrategy
{
public:
	void Draw(HANDLE std_out, COORD coordinates, Direction direction, bool is_enemy, bool is_damaged);
};

