#pragma once
#include "DrawStrategy.hpp"
class DrawableTank :public DrawStrategy
{
public:
	void draw(HANDLE std_out, COORD coordinates, Direction direction, bool is_enemy, bool is_damaged);
};
