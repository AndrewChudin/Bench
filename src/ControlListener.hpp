
#ifndef CONTROLLISTENER_H
#define CONTROLLISTENER_H

class ControlListener
{
public:
	ControlListener();
	WORD& getLastPushedKey();
	~ControlListener();
private:
	HANDLE std_in_ = nullptr;
	INPUT_RECORD input_;
	DWORD events_read_;
	WORD key_ = 0;
};

#endif