#include "stdafx.h"
#include "DrawableWall.hpp"


void DrawableWall::Draw(HANDLE std_out, COORD coordinates, Direction direction, bool is_enemy, bool is_damaged)
{
	if(is_damaged)
		Write(std_out,"#", coordinates, FOREGROUND_RED | FOREGROUND_GREEN);
	else
		Write(std_out, " ", coordinates, BACKGROUND_RED | BACKGROUND_GREEN);
}

