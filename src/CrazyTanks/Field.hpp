#pragma once
#include "stdafx.h"
#include "Tank.hpp"
#include "Wall.hpp"
#include "Bullet.hpp"

class Field {
public:
	Field(int field_height, int field_width);
	void createField();
	void tanksStep();
	void bulletsStep();
	void playerStep();
	const std::vector<tank>& getTanks();
	const std::vector<Wall>& getWalls();
	const std::vector<Bullet>& getBullets();
	const tank& getCharacter();
	COORD getGoldCoord();
	int getScore();
	int getLives();
	bool endGameCheck();
private:
	template <typename T>
	int findByCoords(COORD coordinates, std::vector<T> &vector);
	void playerShot();
	bool tankShot(tank &tank);
	void createTanks();
	void createWalls();
	bool checkCollision(COORD coordinates);

	std::vector<tank> tanks_;
	std::vector<Wall> walls_;
	std::vector<Bullet> bullets_;
	tank character_;
	COORD gold_;
	int lives_ = 3;
	int score_ = 0;
	int field_height_;
	int field_width_;
	HANDLE std_in_ = nullptr;
	HANDLE std_out_ = nullptr;
};

