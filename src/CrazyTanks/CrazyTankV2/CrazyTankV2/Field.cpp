#include "stdafx.h"
#include "Field.hpp"

#define ROTATION_CHANCE 60 
#define SHOT_CHANCE	20 

Field::Field(int field_height, int field_width) {
	field_height_ = field_height;
	field_width_ = field_width;
	gold_ = { (short)field_width_ / 2, (short)field_height_ - 1 };
	character_ = Tank(D_UP, { (short)field_width/2, (short)field_height - 3 });
	std_in_ = GetStdHandle(STD_INPUT_HANDLE);
	std_out_ = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(std_out_, &cursorInfo);
}

void Field::CreateField() {
	CreateTanks();
	CreateWalls();
}

void Field::TanksStep() {
	int a = (int)&tanks_;
	int b = (int)&walls_;
	for (Tank &tank : tanks_) {
		if (!TankShot(tank)) {
			if (rand() % 100 < ROTATION_CHANCE)
				tank.ChangeDirection(static_cast<Direction>(rand() % 4 + 1));
			if (CheckCollision(tank.GetNextCoord()))
				tank.Move();
		}
	}
}

void Field::BulletsStep() {
	COORD next_coord;
	int bullets_amount = bullets_.size();
	for (int i = 0; i < bullets_amount; i++) {
		next_coord = bullets_[i].GetNextCoord();


		if (next_coord.X == 0 || next_coord.X == field_width_ || next_coord.Y == 0 || next_coord.Y == field_height_)
		{
			bullets_.erase(bullets_.begin() + i);
			i--;
			bullets_amount = bullets_.size();
			continue;
		}


		int number_of_tank = FindByCoords(next_coord, tanks_);
		if (number_of_tank != -1)
		{
			if (!bullets_[i].IsEnemy()) {
				tanks_.erase(tanks_.begin() + number_of_tank);
				score_++;
			}
			bullets_.erase(bullets_.begin() + i);
			i--;
			bullets_amount = bullets_.size();
			continue;
		}

		int number_of_wall = FindByCoords(next_coord, walls_);
		if ( number_of_wall != -1)
		{
			if(walls_.at(number_of_wall).GetDamage())
				walls_.erase(walls_.begin() + number_of_wall);
			bullets_.erase(bullets_.begin() + i);
			i--;
			bullets_amount = bullets_.size();
			continue;
		}
		if (next_coord.X == character_.GetCoord().X &&
			next_coord.Y == character_.GetCoord().Y &&
			bullets_[i].IsEnemy())
		{
			bullets_.erase(bullets_.begin() + i);
			i--;
			lives_--;
			bullets_amount = bullets_.size();
			continue;
		}
		bullets_[i].Move();

	}
}

bool Field::CheckCollision(COORD coordinates) {
	if (FindByCoords(coordinates, walls_) != -1)//
		return false;
	if (FindByCoords(coordinates, tanks_) != -1)
		return false;
	if (coordinates.X == character_.GetCoord().X && coordinates.Y == character_.GetCoord().Y)
		return false;
	if (coordinates.X == 0 || coordinates.Y == 0 ||
		coordinates.X == field_width_ || coordinates.Y == field_height_)
		return false;
	if (coordinates.X == gold_.X && coordinates.Y == gold_.Y)
		return false;
	return true;
}

void Field::PlayerStep() {
	INPUT_RECORD input;
	DWORD nr;
	WORD key = 0;

	PeekConsoleInput(std_in_, &input, 1, &nr);
	if (nr > 0) {
		if (input.EventType == KEY_EVENT)
			if (input.Event.KeyEvent.bKeyDown)
				key = input.Event.KeyEvent.wVirtualKeyCode;

		FlushConsoleInputBuffer(std_in_);
	}
	switch (key)
	{
	case(VK_LEFT): character_.ChangeDirection(D_LEFT); break;
	case(VK_RIGHT): character_.ChangeDirection(D_RIGHT); break;
	case(VK_UP): character_.ChangeDirection(D_UP); break;
	case(VK_DOWN): character_.ChangeDirection(D_DOWN); break;
	case(VK_SPACE): PlayerShot(); 
		return; break;
	default: return;
	}
	if (CheckCollision(character_.GetNextCoord()))
		character_.Move();
}
const std::vector<Tank>& Field::GetTanks() {
	return tanks_;
}

const std::vector<Wall>& Field::GetWalls() {
	return walls_;
}

const std::vector<Bullet>& Field::GetBullets() {
	return bullets_;
}

Tank Field::GetCharacter() {
	return character_;
}

COORD Field::GetGoldCoord() {
	return gold_;
}
bool Field::EndGameCheck() {
	return  FindByCoords(gold_, bullets_) != -1 || lives_ <= 0 || tanks_.size() == 0;
}

template <typename T>
int Field::FindByCoords(COORD coordinates, std::vector<T> &vector) {
	for (int i = 0; i<vector.size();i++)
	{
		if (vector.at(i).GetCoord().X == coordinates.X && vector.at(i).GetCoord().Y == coordinates.Y)
			return i;
	}
	return -1;
}

void Field::CreateTanks() {
	COORD new_coord, exisiting_coord;
	bool suitable;
	for (int n = 0; n < 12; n++) {
		do {
			new_coord = { (short)(rand() % (field_width_ - 2) + 1),(short)(rand() % (field_height_ - 5) + 1 )};
			suitable = true;
			if (!CheckCollision(new_coord))
				suitable =	false;
			else
				for (Tank existing_tank : tanks_) {
					exisiting_coord = existing_tank.GetCoord();
					if (abs(exisiting_coord.X - new_coord.X) <= 2 && abs(exisiting_coord.X - new_coord.X) <= 2)
						suitable = false;
				}
		} while (!suitable);
		tanks_.push_back(Tank(static_cast<Direction>(rand() % 4 + 1), new_coord));
	}
	
}

void Field::CreateWalls() {
	COORD new_coord;
	for(short x = gold_.X -1; x<=gold_.X+1;x++)
		walls_.push_back(Wall({ x,gold_.Y-1 }));
	walls_.push_back(Wall({ gold_.X - 1,gold_.Y }));
	walls_.push_back(Wall({ gold_.X + 1,gold_.Y }));
	for (int n = 0; n < 15; n++) {
		do {
			new_coord = { (short)(rand() % (field_width_ - 2) + 1),(short)(rand() % (field_height_ - 2) + 1) };
		} while (!CheckCollision(new_coord));
		walls_.push_back(Wall(new_coord));
	}
}
void Field::PlayerShot() {
	COORD next_coord = character_.GetNextCoord();
	int number_of_tank = FindByCoords(next_coord, tanks_);// проверка есть ли вплотную танк
	if (number_of_tank != -1)
	{
		tanks_.erase(tanks_.begin() + number_of_tank);
		score_++;
		return;
	}
	int number_of_wall = FindByCoords(next_coord, walls_);
	if (number_of_wall != -1)
	{
		if(walls_.at(number_of_wall).GetDamage())
			walls_.erase(walls_.begin() + number_of_wall);
		return;
	}
	if (CheckCollision(next_coord))
		bullets_.push_back(Bullet(character_.GetDirection(), next_coord, false));
}

bool Field::TankShot(Tank &tank) {
	COORD next_coord = tank.GetNextCoord();
	if (rand() % 100 < SHOT_CHANCE)
	{
		COORD t_coord = tank.GetCoord();
		// В золото
		if (t_coord.X == gold_.X)//если на одной вертикали
		{
			if (t_coord.Y > gold_.Y)
				tank.ChangeDirection(D_UP);
			else
				tank.ChangeDirection(D_DOWN);
			if(CheckCollision(tank.GetNextCoord()))
				bullets_.push_back(Bullet(tank.GetDirection(), tank.GetNextCoord(), true));
			else 
				return false;
			return true;
		}
		if (t_coord.Y == gold_.Y)	 //если на одной горизонтали
		{
			if (t_coord.X > gold_.X)
				tank.ChangeDirection(D_LEFT);
			else
				tank.ChangeDirection(D_RIGHT);
			if (CheckCollision(tank.GetNextCoord()))
				bullets_.push_back(Bullet(tank.GetDirection(), tank.GetNextCoord(), true));
			else
				return false;
			return true;
		}
		// В игрока
		COORD c_coord = character_.GetCoord();
		if (t_coord.X == c_coord.X)//если на одной вертикали
		{
			if (t_coord.Y > c_coord.Y || t_coord.Y > gold_.Y)
				tank.ChangeDirection(D_UP);
			else	
				tank.ChangeDirection(D_DOWN);
			if (CheckCollision(tank.GetNextCoord()))
				bullets_.push_back(Bullet(tank.GetDirection(), tank.GetNextCoord(), true));
			else
				return false;
			return true;
		}
		if (t_coord.Y == c_coord.Y)	 //если на одной горизонтали
		{
			if (t_coord.X > c_coord.X || t_coord.X > gold_.X)
				tank.ChangeDirection(D_LEFT);
			else    
				tank.ChangeDirection(D_RIGHT);
			if (CheckCollision(tank.GetNextCoord()))
				bullets_.push_back(Bullet(tank.GetDirection(), tank.GetNextCoord(), true));
			else
				return false;
			return true;
		}
	}
	return false;
}
