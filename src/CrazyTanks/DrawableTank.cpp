#include "stdafx.h"
#include "DrawableTank.hpp"


void DrawableTank::Draw(HANDLE std_out, COORD coordinates, Direction direction, bool is_enemy, bool is_damaged)
{
	WORD look = BACKGROUND_INTENSITY | (is_enemy ? FOREGROUND_RED : FOREGROUND_GREEN);
	switch (direction)
	{
	case(D_UP):
		Write(std_out, "^", coordinates, look);
		break;
	case(D_DOWN):
		Write(std_out, "v", coordinates, look);
		break;
	case(D_LEFT):
		Write(std_out, "<", coordinates, look);
		break;
	case(D_RIGHT):
		Write(std_out, ">", coordinates, look);
		break;
	default:		
		Write(std_out, " ", coordinates, BACKGROUND_RED);
		break;
	}
}
