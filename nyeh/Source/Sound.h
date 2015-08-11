#ifndef _SOUND_H
#define _SOUND_H
#define _USE_MATH_DEFINES
/****************************************************************************/
/*!
\file Sound.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class used for sound
*/
/****************************************************************************/
#include <Windows.h>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
/****************************************************************************/
/*!
Class Sound:
\brief
For sound
*/
/****************************************************************************/
class Sound
{
private:
	std::map<std::string, char*> soundData;

public:
	Sound();
	~Sound();
	void playSound(std::string key, bool async = true);
	void stopSound();
	bool loadWave(std::string key, char* filename);
};

#endif