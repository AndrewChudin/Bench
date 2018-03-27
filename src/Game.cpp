#include "stdafx.h"
#include "Field.hpp"
#include "Renderer.hpp"
#include "ControlListener.hpp"
#include "Game.hpp"
#include "Constants.h"

Game::Game(): field_(FIELD_HEIGHT, FIELD_WIDTH)
{
	srand(time(NULL));

}

void Game::mainCycle()
{
	auto start = std::chrono::high_resolution_clock::now();
	do {
		field_.createField();
		renderer_.init(field_);
		while (!field_.endGameCheck()) {
			field_.tanksStep();
			field_.bulletsStep();
			field_.playerStep(controlListener.getLastPushedKey());
			renderer_.redrawField(field_);
			renderer_.refreshIndicators(field_, start);
			Sleep(WAITING_TIME);
		}
	} while (MessageBoxA(0, MSG_TEXT.c_str(), (field_.getTanks().size() == 0 ? MSG_VICTORY : MSG_DEFEAT).c_str(), MB_YESNO) == IDYES);

}


Game::~Game()
{
}
