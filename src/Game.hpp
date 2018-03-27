#ifndef GAME_HPP
#define GAME_HPP

#include"stdafx.h"
#include "Field.hpp"
#include "Renderer.hpp"
#include "ControlListener.hpp"

class Game
{
public:
	Game();
	void mainCycle();
	~Game();
private:
	Field field_;
	Renderer renderer_;
	ControlListener controlListener;
};

#endif
