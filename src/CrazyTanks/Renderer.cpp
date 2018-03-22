


#include "stdafx.h"
#include "Renderer.hpp"
#include "Field.hpp"



void Renderer::Init(short size_x, short size_y) {
	field_width_ = size_x;
	field_heght_ = size_y;

	SetConsoleTitle("CrazyTanks");
	std_out_ = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(std_out_, &cursorInfo);

	for (short x = 0; x <= size_x; x++) {
		Write(" ", { x, size_y }, BACKGROUND_RED | BACKGROUND_GREEN);
		Write(" ", { x, 0 }, BACKGROUND_RED | BACKGROUND_GREEN);
	}
	for (short y = 1; y < size_y; y++) {
		Write(" ", { 0, y }, BACKGROUND_RED | BACKGROUND_GREEN);
		Write(" ", { size_x, y }, BACKGROUND_RED | BACKGROUND_GREEN);
	}

	Write("score: 0", { field_width_ + 2, 1 }, FOREGROUND_INTENSITY);
	Write("lives:", { field_width_ + 2, 2 }, FOREGROUND_INTENSITY);
	Write("Enemies:", { field_width_ + 2, 3 }, FOREGROUND_INTENSITY);
	Write("Time:", { field_width_ + 2, 4 }, FOREGROUND_INTENSITY);
}
void Renderer::Write(std::string str, COORD coord, WORD attributes)
{
	current_shape->Write(std_out_, str, coord, attributes);
}
void Renderer::SetShape(DrawStrategy* shape) 
{
	current_shape = shape;
}

void Renderer::Draw(const std::vector<Tank> &tanks) 
{
	for (const Tank &tank : tanks)
	{
		current_shape->Draw(std_out_, tank.GetCoord(), tank.GetDirection(), true, 0);
	}
}

void Renderer::Draw(const std::vector<Wall> &walls) {
	for (Wall wall : walls)
	{
		current_shape->Draw(std_out_, wall.GetCoord(), D_NOTHING, 0, wall.IsDamaged());
	}
}

void Renderer::Draw(const std::vector<Bullet> &bullets) 
{
	for (Bullet bullet : bullets)
	{
		current_shape->Draw(std_out_, bullet.GetCoord(), bullet.GetDirection(), 0, 0);
	}
}

void Renderer::DrawCharacter(Tank tank)
{
		current_shape->Draw(std_out_, tank.GetCoord(), tank.GetDirection(), false, 0);

}

void Renderer::Draw(COORD coordinates) {
		current_shape->Draw(std_out_, coordinates, D_NOTHING, 0, 0);
}

void Renderer::RefreshIndicators(Field &field, std::chrono::time_point<std::chrono::steady_clock> start_time) {
	//счет
	char score_str[3] = { 0 };
	_itoa(field.score_, score_str, 10);
	Write(score_str, { field_width_ + 9, 1 }, FOREGROUND_INTENSITY);
	// жизни
	Write("    ", { field_width_ + 8 , 2 }, FOREGROUND_RED);
	for(short i = 0; i < (short)field.lives_;i++)
	Write("\x03", { field_width_ + 8 + i, 2 }, FOREGROUND_RED);
	//враги
	Write("    ", { field_width_ + 11 , 3 }, FOREGROUND_RED);
	char enemies_str[3] = { 0 };
	_itoa(field.tanks_.size(), enemies_str, 10);
	Write(enemies_str, { field_width_ + 11, 3 }, FOREGROUND_INTENSITY);
	//время
	char time_str[6] = { 0 };
	std::chrono::seconds time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_time);
	_itoa(time.count(), time_str, 10);
	Write(time_str, { field_width_ + 8, 4 }, FOREGROUND_BLUE);
}

void Renderer::ClearField() {
	char *str = new char[field_width_ ] {0};
	for (short i = 0; i < (short)field_width_-1; i++)
		str[i] = ' ';
	for (short i = 1; i < (short)field_heght_; i++)
		Write(str, { 1, i }, 0);
}

