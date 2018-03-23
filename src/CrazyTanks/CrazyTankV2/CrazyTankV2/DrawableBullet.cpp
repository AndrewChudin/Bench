#include "stdafx.h"
#include "DrawableBullet.hpp"


void DrawableBullet::draw(HANDLE std_out, COORD coordinates, Direction direction, bool is_enemy, bool is_damaged)
{
	switch (direction)
	{
	case(D_UP):
	case(D_DOWN):
		write(std_out, "|", coordinates, FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	case(D_LEFT):
	case(D_RIGHT):
		write(std_out, "-", coordinates, FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	default:
		write(std_out, " ", coordinates, BACKGROUND_RED);
		break;
	}
}
