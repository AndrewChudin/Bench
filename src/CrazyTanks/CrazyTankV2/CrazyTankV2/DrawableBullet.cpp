#include "stdafx.h"
#include "DrawableBullet.hpp"


void DrawableBullet::Draw(HANDLE std_out, COORD coordinates, Direction direction, bool is_enemy, bool is_damaged)
{
	switch (direction)
	{
	case(D_UP):
	case(D_DOWN):
		Write(std_out, "|", coordinates, FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	case(D_LEFT):
	case(D_RIGHT):
		Write(std_out, "-", coordinates, FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	default:
		Write(std_out, " ", coordinates, BACKGROUND_RED);
		break;
	}
}
