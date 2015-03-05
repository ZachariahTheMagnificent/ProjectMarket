#pragma once

class Trolley
{
public:
	Trolley(void);
	~Trolley(void);
	void SetBoolPos(int itemPos, bool taken); 
	bool GetBoolPos(int itemPos); 
	void Reset(); 
private:
	bool PutItemPos[3];
};