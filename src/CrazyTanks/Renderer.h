
#if !defined(_RENDERER_H)
#define _RENDERER_H
#include "stdafx.h"

#include "Field.h"

class Renderer {
public:
	void Init(short size_x, short size_y);
	void DrawField(Field &field);
	void RefreshIndicators(Field &field, std::chrono::time_point<std::chrono::steady_clock> start_time);
protected:
	void Write(char* text, COORD coordinates, WORD attributes);
	void ClearField();

	short field_heght_;
	short field_width_;
	HANDLE std_out_;
};

#endif  //_RENDERER_H
