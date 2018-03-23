#include "stdafx.h"
#include "DrawableWall.hpp"


void DrawableWall::draw(HANDLE std_out, COORD coordinates, Direction direction, bool is_enemy, bool is_damaged)
{
	if(is_damaged)
		write(std_out,"#", coordinates, FOREGROUND_RED | FOREGROUND_GREEN);
	else
		write(std_out, " ", coordinates, BACKGROUND_RED | BACKGROUND_GREEN);
}

