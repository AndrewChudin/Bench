#include "stdafx.h"
#include "Field.hpp"
#include "DrawStrategy.hpp"

class Renderer {
public:
	void init(short size_x, short size_y);
	void setShape(DrawStrategy* shape);
	void draw(const std::vector<tank>& tanks);
	void draw(const std::vector<Wall>& walls);
	void draw(const std::vector<Bullet>& bullets);
	void draw(COORD cordinates);
	void drawCharacter(tank tank);
	void refreshIndicators(Field &field, std::chrono::time_point<std::chrono::steady_clock> start_time);
	void clearField();
protected:
	void write(std::string str, COORD coord, WORD attributes);
	DrawStrategy* current_shape;
	short field_heght_;
	short field_width_;
	HANDLE std_out_;
};

