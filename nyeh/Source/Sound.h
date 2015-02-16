#ifndef _SOUND_H
#define _SOUND_H
#define _USE_MATH_DEFINES

#include <Windows.h>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

class Sound
{
private:
	std::map<std::string, char*> soundData;

public:
	Sound();
	~Sound();
	void playSound(std::string key, bool async = true);
	bool loadWave(std::string key, char* filename);
};

#endif