
#if !defined(_FIELD_H)
#define _FIELD_H
#include "stdafx.h"

#include "Tank.h"
#include "Wall.h"
#include "Bullet.h"
class Field {
public:
	Field();
	void CreateField();
	void TanksStep();
	void BulletsStep();
	void PlayerStep();
	bool EndGameCheck();
protected:
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
	const COORD gold_{24, 24};
	int lives_ = 3;
	int score_ = 0;
	const int field_height_ = 25;
	const int field_width_ = 50;
	HANDLE std_in_ = nullptr;

	friend class Renderer;
};

#endif  //_FIELD_H
