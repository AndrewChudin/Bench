#ifndef FIELD_HPP
#define FIELD_HPP

#include "stdafx.h"
#include "Tank.hpp"
#include "Wall.hpp"
#include "Bullet.hpp"
#include "Constants.h"

class Field {
public:
	Field(short field_height, short field_width);
	void createField();
	void tanksStep();
	void bulletsStep();
	void playerStep(WORD key);
	COORD getSize();
	const std::vector<Tank>& getTanks();
	const std::vector<Wall>& getWalls();
	const std::vector<Bullet>& getBullets();
	const Tank& getCharacter();
	const COORD& getGoldCoord();
	const int& getScore();
	const int& getLives();
	bool endGameCheck();
private:
	template <typename T>
	int findByCoords(COORD coordinates, std::vector<T> &vector);
	void playerShot();
	bool tankShot(Tank &tank);
	void createTanks();
	void createWalls();
	bool checkCollision(COORD coordinates);

	std::vector<Tank> tanks_;
	std::vector<Wall> walls_;
	std::vector<Bullet> bullets_;
	Tank character_;
	COORD gold_;
	int lives_ = MAX_LIVES;
	int score_ = 0;
	short field_height_;
	short field_width_;
	HANDLE std_out_ = nullptr;
};

#endif
