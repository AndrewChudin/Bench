#include "stdafx.h"
#include "ControlListener.hpp"


ControlListener::ControlListener()
{
	std_in_ = GetStdHandle(STD_INPUT_HANDLE);
}

WORD& ControlListener::getLastPushedKey() {
	key_ = 0;
	PeekConsoleInput(std_in_, &input_, 1, &events_read_);
	if (events_read_ > 0) {
		if (input_.EventType == KEY_EVENT)
			if (input_.Event.KeyEvent.bKeyDown)
				key_ = input_.Event.KeyEvent.wVirtualKeyCode;

		FlushConsoleInputBuffer(std_in_);
	}
	return key_;
}
ControlListener::~ControlListener()
{
}
