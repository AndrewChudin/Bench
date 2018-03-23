#pragma once
#include "stdafx.h"
class DrawStrategy {
public:
	virtual void draw(HANDLE std_out, COORD coordinates, Direction direction, bool is_enemy, bool is_damaged);
	void write(HANDLE std_out, std::string str, COORD coordinates, WORD attributes);
};