#include "stdafx.h"
#include "DrawableGold.hpp"


void DrawableGold::draw(HANDLE std_out, COORD coordinates, Direction direction, bool is_enemy, bool is_damaged)
{
		write(std_out, "$", coordinates, FOREGROUND_RED | FOREGROUND_GREEN);
}
