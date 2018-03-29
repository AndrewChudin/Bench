
#ifndef CONTROLLISTENER_H
#define CONTROLLISTENER_H

#include "stdafx.h"
class ControlListener
{
public:
	ControlListener();
	WORD& getLastPushedKey();
	
	~ControlListener();
private:
	bool scanning = true;
	void scan();
	HANDLE std_in_;
	INPUT_RECORD input_;
	DWORD events_read_;
	std::thread listener_thread;
	WORD key_ = 0;
};

#endif