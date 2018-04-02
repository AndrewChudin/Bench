#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "stdafx.h"
#include "Field.hpp"

class Renderer {
public:
	void init(Field& field);
	
	void refreshIndicators(Field &field, std::chrono::time_point<std::chrono::steady_clock> start_time);
	void clearField();
	void redrawField(Field& field);
protected:
	void draw(const std::vector<Tank>& tanks);
	void draw(const std::vector<Wall>& walls);
	void draw(const std::vector<Bullet>& bullets);
	void drawGold(const COORD& cordinates);
	void drawCharacter(const Tank& tank);
	void write(std::string str, const COORD& coord, WORD attributes);
	short field_height_;
	short field_width_;
	HANDLE std_out_;
};

#endif