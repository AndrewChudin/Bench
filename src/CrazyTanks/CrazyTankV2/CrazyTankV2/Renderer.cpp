


#include "stdafx.h"
#include "Renderer.h"
#include "Field.h"



void Renderer::Init(short size_x, short size_y) {
	field_width_ = size_x;
	field_heght_ = size_y;
	SetConsoleTitle("CrazyTanks");
	std_out_ = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(std_out_, &cursorInfo);
	for (short x = 0; x <= size_x+1; x++) {
		Write(" ", { x, size_y }, BACKGROUND_RED | BACKGROUND_GREEN);
		Write(" ", { x, 0 }, BACKGROUND_RED | BACKGROUND_GREEN);
	}
	for (short y = 1; y < size_y; y++) {
		Write(" ", { 0, y }, BACKGROUND_RED | BACKGROUND_GREEN);
		Write(" ", { size_x+1, y }, BACKGROUND_RED | BACKGROUND_GREEN);
	}

	Write("score: 0", { 51, 1 }, FOREGROUND_INTENSITY);
	Write("lives:", { 51, 2 }, FOREGROUND_INTENSITY);
	Write("Enemies:", { 51, 3 }, FOREGROUND_INTENSITY);
	Write("Time:", { 51, 4 }, FOREGROUND_INTENSITY);
}


void Renderer::DrawField(Field &field) {
	ClearField();
	switch (field.character_.GetDirection())
	{
	case(D_UP):
		Write("^", field.character_.GetCoord(), BACKGROUND_INTENSITY | FOREGROUND_GREEN);
		break;
	case(D_DOWN):
		Write("v", field.character_.GetCoord(), BACKGROUND_INTENSITY | FOREGROUND_GREEN);
		break;
	case(D_LEFT):
		Write("<", field.character_.GetCoord(), BACKGROUND_INTENSITY | FOREGROUND_GREEN);
		break;
	case(D_RIGHT):
		Write(">", field.character_.GetCoord(), BACKGROUND_INTENSITY | FOREGROUND_GREEN);
		break;
	default:
		break;
	}

	for(Tank tank: field.tanks_)
		switch (tank.GetDirection())
		{
		case(D_UP):
			Write("^", tank.GetCoord(), BACKGROUND_INTENSITY | FOREGROUND_RED);
			break;
		case(D_DOWN):
			Write("v", tank.GetCoord(), BACKGROUND_INTENSITY | FOREGROUND_RED);
			break;
		case(D_LEFT):
			Write("<", tank.GetCoord(), BACKGROUND_INTENSITY | FOREGROUND_RED);
			break;
		case(D_RIGHT):
			Write(">", tank.GetCoord(), BACKGROUND_INTENSITY | FOREGROUND_RED);
			break;
		default:
			break;
		}

	for (Wall wall : field.walls_)
		if(wall.IsDamaged())
			Write("#", wall.GetCoord(), FOREGROUND_RED | FOREGROUND_GREEN);
		else
			Write(" ", wall.GetCoord(), BACKGROUND_RED | BACKGROUND_GREEN);

	for (Bullet bullet : field.bullets_)
		switch (bullet.GetDirection())
		{
		case(D_UP):
		case(D_DOWN):
			Write("|", bullet.GetCoord(), FOREGROUND_RED | FOREGROUND_GREEN);
			break;
		case(D_LEFT):
		case(D_RIGHT):
			Write("-", bullet.GetCoord(), FOREGROUND_RED | FOREGROUND_GREEN);
			break;
		default:
			break;
		}
	Write("$", { 24, 24 }, FOREGROUND_RED | FOREGROUND_GREEN);
}

void Renderer::Write(char* text, COORD coordinates, WORD attributes) {
	DWORD length = lstrlen(text);
	DWORD nw;

	WriteConsoleOutputCharacter(std_out_, text, length, coordinates, &nw);
	FillConsoleOutputAttribute(std_out_, attributes, length, coordinates, &nw);
}

void Renderer::RefreshIndicators(Field &field, std::chrono::time_point<std::chrono::steady_clock> start_time) {
	//счет
	char score_str[3] = { 0 };
	_itoa(field.score_, score_str, 10);
	Write(score_str, { 58, 1 }, FOREGROUND_INTENSITY);
	// жизни
	Write("    ", { 57 , 2 }, FOREGROUND_RED);
	for(short i = 0; i < (short)field.lives_;i++)
	Write("\x03", { 57 + i, 2 }, FOREGROUND_RED);
	//враги
	Write("    ", { 60 , 3 }, FOREGROUND_RED);
	char enemies_str[3] = { 0 };
	_itoa(field.tanks_.size(), enemies_str, 10);
	Write(enemies_str, { 60, 3 }, FOREGROUND_INTENSITY);
	//время
	char time_str[6] = { 0 };
	std::chrono::seconds time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_time);
	_itoa(time.count(), time_str, 10);
	Write(time_str, { 57, 4 }, FOREGROUND_BLUE);
}

void Renderer::ClearField() {
	char *str = new char[field_width_ + 1] {0};
	for (short i = 0; i < (short)field_width_; i++)
		str[i] = ' ';
	for (short i = 1; i < (short)field_heght_; i++)
		Write(str, { 1, i }, 0);
}

