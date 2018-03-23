#include "stdafx.h"
#include "DrawStrategy.hpp"
void DrawStrategy::draw(HANDLE std_out, COORD coordinates, Direction direction, bool is_enemy, bool is_damaged) {

}
void DrawStrategy::write(HANDLE std_out, std::string str, COORD coordinates, WORD attributes) {
	DWORD nw;
	
	WriteConsoleOutputCharacter(std_out, str.c_str(), str.size(), coordinates, &nw);
	FillConsoleOutputAttribute(std_out, attributes, str.size(), coordinates, &nw);
}