
#ifndef CONSTS_H
#define CONSTS_H

#include  "stdafx.h"

typedef std::chrono::time_point<std::chrono::steady_clock> time_p;

const short FIELD_HEIGHT = 25;
const short FIELD_WIDTH = 49;

const int MAX_LIVES = 3;
const int WALL_STRENGTH = 2;
const int ENEMIES_AMOUNT = 10;
const int WALLS_AMOUNT = 10;
const int WAITING_TIME = 500;

const WORD ENEMY_LOOK = BACKGROUND_INTENSITY | FOREGROUND_RED;
const WORD CHARACTER_LOOK = BACKGROUND_INTENSITY | FOREGROUND_GREEN;
const WORD WALL_LOOK = BACKGROUND_RED | BACKGROUND_GREEN;
const WORD BROKEN_WALL_LOOK = FOREGROUND_RED | FOREGROUND_GREEN;
const WORD GOLD_LOOK = FOREGROUND_RED | FOREGROUND_GREEN;
const WORD BULLET_LOOK = FOREGROUND_RED | FOREGROUND_GREEN;

const std::string MSG_DEFEAT = "Поражение.";
const std::string MSG_VICTORY = "Победа!";
const std::string MSG_TEXT = "Сыграть еще раз?";
const std::string MENU_SCORE = "Score: ";
const std::string MENU_ENEMIES = "Enemies: ";
const std::string MENU_LIVES = "Lives: ";
const std::string MENU_TIME = "Time: ";
const short INDENT = 2;

enum Direction { D_NOTHING, D_UP, D_DOWN, D_LEFT, D_RIGHT };

#endif