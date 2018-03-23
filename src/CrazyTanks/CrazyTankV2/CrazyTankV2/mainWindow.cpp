// CrazyTankV2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Field.hpp"
#include "Renderer.hpp"
#include "DrawableTank.hpp"
#include "DrawableBullet.hpp"
#include "DrawableWall.hpp"
#include "DrawableGold.hpp"
int main()
{
	const int field_height = 25;
	const int field_width = 49;
	Field field(field_height, field_width);
	Renderer renderer;
	srand(time(NULL));
	field.createField();
	renderer.init(field_width, field_height);
	auto start = std::chrono::high_resolution_clock::now();

	while (!field.endGameCheck()) {
		field.tanksStep();
		field.bulletsStep();
		field.playerStep();
		renderer.clearField();
		renderer.setShape(new DrawableWall);
		renderer.draw(field.getWalls());
		renderer.setShape(new DrawableTank);
		renderer.draw(field.getTanks());
		renderer.drawCharacter(field.getCharacter());
		renderer.setShape(new DrawableGold);
		renderer.draw(field.getGoldCoord());
		renderer.setShape(new DrawableBullet);
		renderer.draw(field.getBullets());
     	renderer.refreshIndicators(field, start);
		Sleep(500);
	}
    return 0;
}

