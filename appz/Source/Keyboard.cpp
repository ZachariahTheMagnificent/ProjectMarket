#include "Keyboard.h"
#include <iostream>

Keyboard::Keyboard()
{
}

Keyboard::~Keyboard()
{
}

bool Keyboard::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

bool Keyboard::isKeyHold(unsigned short key)
{
	return keyishold[key];
}

bool Keyboard::getkey(unsigned short key)
{
	return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

void Keyboard::updateinput()
{
	keyboardbuffer.clear();
	for(int index = 0; index < 256; index++)
	{
		if(keyAlreadyPressed[index] && !getkey(index))
		{
			keyAlreadyPressed[index] = false;
			keyispressed[index] = false;
			keyishold[index] = false;
		}
		else if(!keyAlreadyPressed[index] && getkey(index))
		{
			keyAlreadyPressed[index] = true;
			keyispressed[index] = true;
			keyishold[index] = true;
		}
		else if(keyAlreadyPressed[index] && getkey(index))
		{
			keyispressed[index] = false;
			keyishold[index] = true;
		}
		else
		{
			keyispressed[index] = false;
			keyishold[index] = false;
		}
	}
	for(int index = ' '; index < '~'; index++)
	{
		if(isKeyPressed(index))
		{
			keyboardbuffer.push_back((char)index);
		}
	}
}

bool Keyboard::isKeyPressed(unsigned short key)
{
	return keyispressed[key];
}

char Keyboard::getkeyboardbuffer()
{
	if(keyboardbuffer.empty())
	{
		return 0;
	}
	else
	{
		char letter = keyboardbuffer.back();
		keyboardbuffer.pop_back();
		return letter;
	}
}

bool Keyboard::isKeyReleased(unsigned short key)
{
	return !(isKeyHold(key));
}