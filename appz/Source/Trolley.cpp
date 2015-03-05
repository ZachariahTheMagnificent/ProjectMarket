#include "Trolley.h"


Trolley::Trolley(void)
{
	for(int i = 0; i < 3; ++i)
	{
		PutItemPos[i] = false;
	}
}


Trolley::~Trolley(void)
{
}

void Trolley::SetBoolPos(int itemPos, bool taken)
{
	PutItemPos[itemPos] = taken;
}

bool Trolley::GetBoolPos(int itemPos)
{
	return PutItemPos[itemPos];
}

void Trolley::Reset()
{
	for(int i = 0; i < 3; ++i)
	{
		PutItemPos[i] = false;
	}
}