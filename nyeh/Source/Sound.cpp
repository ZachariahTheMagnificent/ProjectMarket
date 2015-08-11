#include "sound.h"
#include <stdlib.h>
/****************************************************************************/
/*!
\file Sound.cpp
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class used for sound
*/
/****************************************************************************/

/****************************************************************************/
/*!
\brief
default constructor
*/
/****************************************************************************/
Sound::Sound()
{
	loadWave("stop", "Sound//Void.wav");
}
/****************************************************************************/
/*!
\brief
empty default destructer
*/
/****************************************************************************/
Sound::~Sound()
{
	playSound("stop", false);
    // free up memory used by the sound buffer
    for (std::map<std::string,char *>::iterator it = soundData.begin(); it != soundData.end(); ++it)
    {
        delete [] it->second;
    }

}
/****************************************************************************/
/*!
\brief
Plays a sound
\param key
		the name of the sound to be played
\param async
		a bool to whether or not the sound will be played asynchronously
*/
/****************************************************************************/
void Sound::playSound(std::string key, bool async)
{
    std::map<std::string, char*>::iterator it = soundData.find(key);
    if (it != soundData.end())
    {
        DWORD flag;
		if(async)
		{
			flag = SND_MEMORY | SND_ASYNC;
		}
		else
		{
			flag = SND_MEMORY;
		}
        PlaySoundA(it->second, NULL, flag );
    }
}
/****************************************************************************/
/*!
\brief
Load a *.wav file
\param key
		the name of the sound
\param filename
		the location of the *.wav file
*/
/****************************************************************************/
bool Sound::loadWave(std::string key, char* filename)
{
    std::ifstream waveFile(filename, std::ios::in | std::ios::binary | std::ios::ate);

    if (!waveFile.is_open())
    {
        return false;
    }

    std::streampos size = waveFile.tellg();
    char * memblock = new char [size];
    waveFile.seekg (0, std::ios::beg);
    waveFile.read (memblock, size);
  
    waveFile.close();
    soundData[key] = memblock;

    return true;
}
/****************************************************************************/
/*!
\brief
Stop the current sound
*/
/****************************************************************************/
void Sound::stopSound()
{
	playSound("stop");
}