#include "stdafx.h"
#include "DrawableTank.hpp"


void DrawableTank::draw(HANDLE std_out, COORD coordinates, Direction direction, bool is_enemy, bool is_damaged)
{
	WORD look = BACKGROUND_INTENSITY | (is_enemy ? FOREGROUND_RED : FOREGROUND_GREEN);
	switch (direction)
	{
	case(D_UP):
		write(std_out, "^", coordinates, look);
		break;
	case(D_DOWN):
		write(std_out, "v", coordinates, look);
		break;
	case(D_LEFT):
		write(std_out, "<", coordinates, look);
		break;
	case(D_RIGHT):
		write(std_out, ">", coordinates, look);
		break;
	default:		
		write(std_out, " ", coordinates, BACKGROUND_RED);
		break;
	}
}
