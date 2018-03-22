#include "stdafx.h"
#include "DrawableGold.hpp"


void DrawableGold::Draw(HANDLE std_out, COORD coordinates, Direction direction, bool is_enemy, bool is_damaged)
{
		Write(std_out, "$", coordinates, FOREGROUND_RED | FOREGROUND_GREEN);
}
