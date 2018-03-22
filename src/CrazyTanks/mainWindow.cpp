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
	field.CreateField();
	renderer.Init(field_width, field_height);
	auto start = std::chrono::high_resolution_clock::now();

	while (!field.EndGameCheck()) {
		field.BulletsStep();
		field.PlayerStep();
		field.TanksStep();
		renderer.ClearField();
		renderer.SetShape(new DrawableBullet);
		renderer.Draw(field.GetBullets());
		renderer.SetShape(new DrawableWall);
		renderer.Draw(field.GetWalls());
		renderer.SetShape(new DrawableTank);
		renderer.Draw(field.GetTanks());
		renderer.DrawCharacter(field.GetCharacter());
		renderer.SetShape(new DrawableGold);
		renderer.Draw(field.GetGoldCoord());
     	renderer.RefreshIndicators(field, start);
		Sleep(500);
	}
    return 0;
}

