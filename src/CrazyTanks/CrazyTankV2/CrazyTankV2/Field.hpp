#pragma once
#include "stdafx.h"
#include "Tank.hpp"
#include "Wall.hpp"
#include "Bullet.hpp"

class Field {
public:
	Field(int field_height, int field_width);
	void CreateField();
	void TanksStep();
	void BulletsStep();
	void PlayerStep();
	const std::vector<Tank>& GetTanks();
	const std::vector<Wall>& GetWalls();
	const std::vector<Bullet>& GetBullets();
	Tank GetCharacter();
	COORD GetGoldCoord();
	bool EndGameCheck();
private:
	template <typename T>
	int FindByCoords(COORD coordinates, std::vector<T> &vector);
	void PlayerShot();
	bool TankShot(Tank &tank);
	void CreateTanks();
	void CreateWalls();
	bool CheckCollision(COORD coordinates);

	std::vector<Tank> tanks_;
	std::vector<Wall> walls_;
	std::vector<Bullet> bullets_;
	Tank character_;
	COORD gold_;
	int lives_ = 3;
	int score_ = 0;
	int field_height_;
	int field_width_;
	HANDLE std_in_ = nullptr;
	HANDLE std_out_ = nullptr;
	friend class Renderer;
};

