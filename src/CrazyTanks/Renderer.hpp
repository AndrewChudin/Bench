#include "stdafx.h"
#include "Field.hpp"
#include "DrawStrategy.hpp"

class Renderer {
public:
	void Init(short size_x, short size_y);
	void SetShape(DrawStrategy* shape);
	void Draw(const std::vector<Tank>& tanks);
	void Draw(const std::vector<Wall>& walls);
	void Draw(const std::vector<Bullet>& bullets);
	void Draw(COORD cordinates);
	void DrawCharacter(Tank tank);
	void RefreshIndicators(Field &field, std::chrono::time_point<std::chrono::steady_clock> start_time);
	void ClearField();
	void Write(std::string str, COORD coord, WORD attributes);
protected:
	DrawStrategy* current_shape;
	short field_heght_;
	short field_width_;
	HANDLE std_out_;
};

