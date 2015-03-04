#pragma once

class Trolley
{
public:
	Trolley(void);
	~Trolley(void);
	void SetBoolPos(int itemPos, bool taken); 
	bool GetBoolPos(int itemPos); 
private:
	bool PutItemPos[3];
};