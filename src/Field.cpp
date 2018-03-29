#include "stdafx.h"
#include "Field.hpp"

#define ROTATION_CHANCE 60 
#define SHOT_CHANCE	20 

Field::Field(short field_height, short field_width): character_(D_UP, { field_width / 2, field_height - 3 }) {
	field_height_ = field_height;
	field_width_ = field_width;
	gold_ = { (short)field_width_ / 2, (short)field_height_ - 1 };
	std_out_ = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(std_out_, &cursorInfo);
}

void Field::createField() {
	tanks_.clear();
	walls_.clear();
	bullets_.clear();
	character_.setCoord({ field_width_ / 2, field_height_ - 3 });
	createTanks();
	createWalls();
}

void Field::tanksStep() {
	int a = (int)&tanks_;
	int b = (int)&walls_;
	for (Tank &tank : tanks_) {
		if (!tankShot(tank)) {
			if (rand() % 100 < ROTATION_CHANCE)
				tank.changeDirection(static_cast<Direction>(rand() % 4 + 1));
			if (checkCollision(tank.getNextCoord()))
				tank.move();
		}
	}
}

void Field::bulletsStep() {
	COORD next_coord;
	int bullets_amount = bullets_.size();
	for (int i = 0; i < bullets_amount; i++) {
		next_coord = bullets_[i].getNextCoord();


		if (next_coord.X == 0 || next_coord.X == field_width_ || next_coord.Y == 0 || next_coord.Y == field_height_)
		{
			bullets_.erase(bullets_.begin() + i);
			i--;
			bullets_amount = bullets_.size();
			continue;
		}


		int number_of_tank = findByCoords(next_coord, tanks_);
		if (number_of_tank != -1)
		{
			if (!bullets_[i].isEnemy()) {
				tanks_.erase(tanks_.begin() + number_of_tank);
				score_++;
			}
			bullets_.erase(bullets_.begin() + i);
			i--;
			bullets_amount = bullets_.size();
			continue;
		}

		int number_of_wall = findByCoords(next_coord, walls_);
		if ( number_of_wall != -1)
		{
			if(walls_.at(number_of_wall).getDamage())
				walls_.erase(walls_.begin() + number_of_wall);
			bullets_.erase(bullets_.begin() + i);
			i--;
			bullets_amount = bullets_.size();
			continue;
		}
		if (next_coord.X == character_.getCoord().X &&
			next_coord.Y == character_.getCoord().Y &&
			bullets_[i].isEnemy())
		{
			bullets_.erase(bullets_.begin() + i);
			i--;
			lives_--;
			bullets_amount = bullets_.size();
			continue;
		}
		bullets_[i].move();

	}
}

bool Field::checkCollision(COORD coordinates) {
	if (findByCoords(coordinates, walls_) != -1)//
		return false;
	if (findByCoords(coordinates, tanks_) != -1)
		return false;
	if (coordinates.X == character_.getCoord().X && coordinates.Y == character_.getCoord().Y)
		return false;
	if (coordinates.X == 0 || coordinates.Y == 0 ||
		coordinates.X == field_width_ || coordinates.Y == field_height_)
		return false;
	if (coordinates.X == gold_.X && coordinates.Y == gold_.Y)
		return false;
	return true;
}

void Field::playerStep(WORD key) {

	switch (key)
	{
	case(VK_LEFT): character_.changeDirection(D_LEFT); break;
	case(VK_RIGHT): character_.changeDirection(D_RIGHT); break;
	case(VK_UP): character_.changeDirection(D_UP); break;
	case(VK_DOWN): character_.changeDirection(D_DOWN); break;
	case(VK_SPACE): playerShot(); 
		return; break;
	default: return;
	}
	if (checkCollision(character_.getNextCoord()))
		character_.move();
}
COORD Field::getSize()
{
	return { field_width_, field_height_ };
}
const std::vector<Tank>& Field::getTanks() {
	return tanks_;
}

const std::vector<Wall>& Field::getWalls() {
	return walls_;
}

const std::vector<Bullet>& Field::getBullets() {
	return bullets_;
}

const Tank& Field::getCharacter() {
	return character_;
}

const COORD& Field::getGoldCoord() {
	return gold_;
}

const int& Field::getScore() {
	return score_;
}

const int& Field::getLives() {
	return lives_;
}
bool Field::endGameCheck() {
	return  findByCoords(gold_, bullets_) != -1 || lives_ <= 0 || tanks_.size() == 0;
}

template <typename T>
int Field::findByCoords(COORD coordinates, std::vector<T> &vector) {
	for (int i = 0; i<vector.size();i++)
	{
		if (vector.at(i).getCoord().X == coordinates.X && vector.at(i).getCoord().Y == coordinates.Y)
			return i;
	}
	return -1;
}

void Field::createTanks() {
	COORD new_coord, exisiting_coord;
	bool suitable;
	for (int n = 0; n < ENEMIES_AMOUNT; n++) {
		do {
			new_coord = { (short)(rand() % (field_width_ - 2) + 1),(short)(rand() % (field_height_ - 5) + 1 )};
			suitable = true;
			if (!checkCollision(new_coord))
				suitable =	false;
			else
				for (Tank existing_tank : tanks_) {
					exisiting_coord = existing_tank.getCoord();
					if (abs(exisiting_coord.X - new_coord.X) <= 2 && abs(exisiting_coord.X - new_coord.X) <= 2)
						suitable = false;
				}
		} while (!suitable);
		tanks_.push_back(Tank(static_cast<Direction>(rand() % 4 + 1), new_coord));
	}
	
}

void Field::createWalls() {
	COORD new_coord;
	for(short x = gold_.X -1; x<=gold_.X+1;x++)
		walls_.push_back(Wall({ x,gold_.Y-1 }));
	walls_.push_back(Wall({ gold_.X - 1,gold_.Y }));
	walls_.push_back(Wall({ gold_.X + 1,gold_.Y }));
	for (int n = 0; n < WALLS_AMOUNT; n++) {
		do {
			new_coord = { (short)(rand() % (field_width_ - 2) + 1),(short)(rand() % (field_height_ - 2) + 1) };
		} while (!checkCollision(new_coord));
		walls_.push_back(Wall(new_coord));
	}
}
void Field::playerShot() {
	COORD next_coord = character_.getNextCoord();
	int number_of_tank = findByCoords(next_coord, tanks_);// �������� ���� �� �������� ����
	if (number_of_tank != -1)
	{
		tanks_.erase(tanks_.begin() + number_of_tank);
		score_++;
		return;
	}
	int number_of_wall = findByCoords(next_coord, walls_);
	if (number_of_wall != -1)
	{
		if(walls_.at(number_of_wall).getDamage())
			walls_.erase(walls_.begin() + number_of_wall);
		return;
	}
	if (checkCollision(next_coord))
		bullets_.push_back(Bullet(character_.getDirection(), next_coord, false));
}

bool Field::tankShot(Tank &tank) {
	COORD next_coord = tank.getNextCoord();
	if (rand() % 100 < SHOT_CHANCE)
	{
		COORD t_coord = tank.getCoord();
		// � ������
		if (t_coord.X == gold_.X)//���� �� ����� ���������
		{
			if (t_coord.Y > gold_.Y)
				tank.changeDirection(D_UP);
			else
				tank.changeDirection(D_DOWN);
			if(checkCollision(tank.getNextCoord()))
				bullets_.push_back(Bullet(tank.getDirection(), tank.getNextCoord(), true));
			else 
				return false;
			return true;
		}
		if (t_coord.Y == gold_.Y)	 //���� �� ����� �����������
		{
			if (t_coord.X > gold_.X)
				tank.changeDirection(D_LEFT);
			else
				tank.changeDirection(D_RIGHT);
			if (checkCollision(tank.getNextCoord()))
				bullets_.push_back(Bullet(tank.getDirection(), tank.getNextCoord(), true));
			else
				return false;
			return true;
		}
		// � ������
		COORD c_coord = character_.getCoord();
		if (t_coord.X == c_coord.X)//���� �� ����� ���������
		{
			if (t_coord.Y > c_coord.Y)
				tank.changeDirection(D_UP);
			else	
				tank.changeDirection(D_DOWN);
			if (checkCollision(tank.getNextCoord()))
				bullets_.push_back(Bullet(tank.getDirection(), tank.getNextCoord(), true));
			else
				return false;
			return true;
		}
		if (t_coord.Y == c_coord.Y)	 //���� �� ����� �����������
		{
			if (t_coord.X > c_coord.X)
				tank.changeDirection(D_LEFT);
			else    
				tank.changeDirection(D_RIGHT);
			if (checkCollision(tank.getNextCoord()))
				bullets_.push_back(Bullet(tank.getDirection(), tank.getNextCoord(), true));
			else
				return false;
			return true;
		}
	}
	return false;
}
