#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <vector>
#include <Windows.h>

class Keyboard
{
public:
	Keyboard();
	~Keyboard();
	bool isKeyPressed(unsigned short key);
	bool isKeyReleased(unsigned short key);
	bool isKeyHold(unsigned short key);
	bool getkey(unsigned short key);
	char getkeyboardbuffer();
	void updateinput();
private:
	bool IsKeyPressed(unsigned short key);
	std::vector<char> keyboardbuffer;
	bool keyAlreadyPressed[256];
	bool keyispressed[256];
	bool keyishold[256];
};

#endif