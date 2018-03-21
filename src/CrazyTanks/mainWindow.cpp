// CrazyTankV2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Field.h"
#include "Renderer.h"

int main()
{
	srand(time(NULL));
	Field field;
	Renderer renderer;
	field.CreateField();
	renderer.Init(49, 25);
	auto start = std::chrono::high_resolution_clock::now();
	while (!field.EndGameCheck()) {
		field.BulletsStep();
		field.PlayerStep();
		field.TanksStep();
		renderer.DrawField(field);
     		renderer.RefreshIndicators(field, start);
		Sleep(500);
	}
    return 0;
}

