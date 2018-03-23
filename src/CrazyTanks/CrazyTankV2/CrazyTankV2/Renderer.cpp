


#include "stdafx.h"
#include "Renderer.hpp"
#include "Field.hpp"



void Renderer::init(short size_x, short size_y) {
	field_width_ = size_x;
	field_heght_ = size_y;

	SetConsoleTitle("CrazyTanks");
	std_out_ = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(std_out_, &cursorInfo);

	for (short x = 0; x <= size_x; x++) {
		write(" ", { x, size_y }, BACKGROUND_RED | BACKGROUND_GREEN);
		write(" ", { x, 0 }, BACKGROUND_RED | BACKGROUND_GREEN);
	}
	for (short y = 1; y < size_y; y++) {
		write(" ", { 0, y }, BACKGROUND_RED | BACKGROUND_GREEN);
		write(" ", { size_x, y }, BACKGROUND_RED | BACKGROUND_GREEN);
	}

	write("score: 0", { field_width_ + 2, 1 }, FOREGROUND_INTENSITY);
	write("lives:", { field_width_ + 2, 2 }, FOREGROUND_INTENSITY);
	write("Enemies:", { field_width_ + 2, 3 }, FOREGROUND_INTENSITY);
	write("Time:", { field_width_ + 2, 4 }, FOREGROUND_INTENSITY);
}
void Renderer::write(std::string str, COORD coord, WORD attributes)
{
	current_shape->write(std_out_, str, coord, attributes);
}
void Renderer::setShape(DrawStrategy* shape) 
{
	current_shape = shape;
}

void Renderer::draw(const std::vector<tank> &tanks) 
{
	for (const tank &tank : tanks)
	{
		current_shape->draw(std_out_, tank.getCoord(), tank.getDirection(), true, 0);
	}
}

void Renderer::draw(const std::vector<Wall> &walls) {
	for (Wall wall : walls)
	{
		current_shape->draw(std_out_, wall.getCoord(), D_NOTHING, 0, wall.isDamaged());
	}
}

void Renderer::draw(const std::vector<Bullet>& bullets) 
{
	for (Bullet bullet : bullets)
	{
		current_shape->draw(std_out_, bullet.getCoord(), bullet.getDirection(), 0, 0);
	}
}

void Renderer::drawCharacter(tank tank)
{
		current_shape->draw(std_out_, tank.getCoord(), tank.getDirection(), false, 0);

}

void Renderer::draw(COORD coordinates) {
		current_shape->draw(std_out_, coordinates, D_NOTHING, 0, 0);
}

void Renderer::refreshIndicators(Field &field, std::chrono::time_point<std::chrono::steady_clock> start_time) {
	//счет
	char score_str[3] = { 0 };
	_itoa(field.getScore(), score_str, 10);
	write(score_str, { field_width_ + 9, 1 }, FOREGROUND_INTENSITY);
	// жизни
	write("    ", { field_width_ + 8 , 2 }, FOREGROUND_RED);
	for(short i = 0; i < (short)field.getLives();i++)
	write("\x03", { field_width_ + 8 + i, 2 }, FOREGROUND_RED);
	//враги
	write("    ", { field_width_ + 11 , 3 }, FOREGROUND_RED);
	char enemies_str[3] = { 0 };
	_itoa(field.getTanks().size(), enemies_str, 10);
	write(enemies_str, { field_width_ + 11, 3 }, FOREGROUND_INTENSITY);
	//время
	char time_str[6] = { 0 };
	std::chrono::seconds time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_time);
	_itoa(time.count(), time_str, 10);
	write(time_str, { field_width_ + 8, 4 }, FOREGROUND_BLUE);
}

void Renderer::clearField() {
	char *str = new char[field_width_ ] {0};
	for (short i = 0; i < (short)field_width_-1; i++)
		str[i] = ' ';
	for (short i = 1; i < (short)field_heght_; i++)
		write(str, { 1, i }, 0);       
}

