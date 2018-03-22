#pragma once
#include "stdafx.h"
class DrawStrategy {
public:
	virtual void Draw(HANDLE std_out, COORD coordinates, Direction direction, bool is_enemy, bool is_damaged);
	void Write(HANDLE std_out, std::string str, COORD coordinates, WORD attributes);
};