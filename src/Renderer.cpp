
#include "stdafx.h"
#include "Renderer.hpp"
#include "Field.hpp"
#include "Constants.h"


void Renderer::init(Field& field) {
	field_width_ = field.getSize().X;
	field_height_ = field.getSize().Y;

	SetConsoleTitle("CrazyTanks");
	std_out_ = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(std_out_, &cursorInfo);

	for (short x = 0; x <= field_width_; x++) {
		write(" ", { x, field_height_ }, WALL_LOOK);
		write(" ", { x, 0 }, WALL_LOOK);
	}
	for (short y = 1; y < field_height_; y++) {
		write(" ", { 0, y }, WALL_LOOK);
		write(" ", { field_width_, y }, WALL_LOOK);
	}
	write("$", field.getGoldCoord(), GOLD_LOOK);
	write(MENU_SCORE,	{ field_width_ + 2, 1 }, FOREGROUND_INTENSITY);
	write(MENU_LIVES,		{ field_width_ + 2, 2 }, FOREGROUND_INTENSITY);
	write(MENU_ENEMIES,	{ field_width_ + 2, 3 }, FOREGROUND_INTENSITY);
	write(MENU_TIME,		{ field_width_ + 2, 4 }, FOREGROUND_INTENSITY);
}
void Renderer::write(std::string str, const COORD& coord, WORD attributes)
{
	DWORD nw;

	WriteConsoleOutputCharacter(std_out_, str.c_str(), str.size(), coord, &nw);
	FillConsoleOutputAttribute(std_out_, attributes, str.size(), coord, &nw);
}


void Renderer::draw(const std::vector<Tank> &tanks) 
{
	for (const Tank &tank : tanks)
	{
		switch (tank.getDirection())
		{
		case(D_UP):
			write("^", tank.getCoord(), ENEMY_LOOK);
			break;
		case(D_DOWN):
			write("v", tank.getCoord(), ENEMY_LOOK);
			break;
		case(D_LEFT):
			write("<", tank.getCoord(), ENEMY_LOOK);
			break;
		case(D_RIGHT):
			write(">", tank.getCoord(), ENEMY_LOOK);
			break;
		default:
			write(" ", tank.getCoord(), BACKGROUND_RED);
			break;
		}
	}
}

void Renderer::draw(const std::vector<Wall> &walls) {
	for (Wall wall : walls)
	{
		if (wall.isDamaged())
			write( "#", wall.getCoord(), BROKEN_WALL_LOOK);
		else
			write(" ", wall.getCoord(), WALL_LOOK);
	}
}

void Renderer::draw(const std::vector<Bullet>& bullets) 
{
	for (Bullet bullet : bullets)
	{
		switch (bullet.getDirection())
		{
		case(D_UP):
		case(D_DOWN):
			write("|", bullet.getCoord(), BULLET_LOOK);
			break;
		case(D_LEFT):
		case(D_RIGHT):
			write("-", bullet.getCoord(), BULLET_LOOK);
			break;
		default:
			write(" ", bullet.getCoord(), BACKGROUND_RED);
			break;
		}
	}
}

void Renderer::drawCharacter(const Tank& tank)
{
	switch (tank.getDirection())
	{
	case(D_UP):
		write("^", tank.getCoord(), CHARACTER_LOOK);
		break;
	case(D_DOWN):
		write("v", tank.getCoord(), CHARACTER_LOOK);
		break;
	case(D_LEFT):
		write("<", tank.getCoord(), CHARACTER_LOOK);
		break;
	case(D_RIGHT):
		write(">", tank.getCoord(), CHARACTER_LOOK);
		break;
	default:
		write(" ", tank.getCoord(), BACKGROUND_RED);
		break;
	}

}

void Renderer::drawGold(const COORD& coordinates) {
	write("$", coordinates, GOLD_LOOK);
}

void Renderer::refreshIndicators(Field &field, std::chrono::time_point<std::chrono::steady_clock> start_time) {
	//счет
	char score_str[3] = { 0 };
	_itoa(field.getScore(), score_str, 10);
	write(score_str, { field_width_ + 9, 1 }, FOREGROUND_INTENSITY);
	// жизни
	write("      ", { field_width_ + static_cast<short>(MENU_LIVES.size()) , 2 }, 0);
	for(short i = 0; i < (short)field.getLives();i++)
		write("\x03", { field_width_ + static_cast<short>(MENU_LIVES.size()) + INDENT + i, 2 }, FOREGROUND_RED);
	//враги
	write("      ", { field_width_ + static_cast<short>(MENU_ENEMIES.size()) + INDENT  , 3 }, FOREGROUND_RED);
	char enemies_str[3] = { 0 };
	_itoa(field.getTanks().size(), enemies_str, 10);
	write(enemies_str, { field_width_ + static_cast<short>(MENU_ENEMIES.size()) + INDENT , 3 }, FOREGROUND_INTENSITY);
	//время
	char time_str[6] = { 0 };
	std::chrono::seconds time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_time);
	_itoa(time.count(), time_str, 10);
	write(time_str, { field_width_ + static_cast<short>(MENU_TIME.size()) + INDENT , 4 }, FOREGROUND_BLUE);
}

void Renderer::clearField() {
	char *str = new char[field_width_ ] {0};
	for (short i = 0; i < (short)field_width_-1; i++)
		str[i] = ' ';
	for (short i = 1; i < (short)field_height_; i++)
		write(str, { 1, i }, 0);       
}

void Renderer::redrawField(Field& field)
{
	clearField();
	drawGold(field.getGoldCoord());
	draw(field.getWalls());
	drawCharacter(field.getCharacter());
	draw(field.getTanks());
	draw(field.getBullets());
}

