#ifndef KEYBOARD_H
#define KEYBOARD_H
/****************************************************************************/
/*!
\file Keyboard.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class that handles keyboard input
*/
/****************************************************************************/
#include <vector>
#include <Windows.h>
/****************************************************************************/
/*!
Class Keyboard:
\brief
handles keyboard input
*/
/****************************************************************************/
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
	std::vector<char> keyboardbuffer;
	bool keyAlreadyPressed[256];
	bool keyispressed[256];
	bool keyishold[256];
};

#endif