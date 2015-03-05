/******************************************************************************/
/*!
\file	Trolley.h
\author Gregory Koh Wen Cong
\par	email: pyroflame11@gmail.com
\brief
Class to store Trolley
*/
/******************************************************************************/
#pragma once

/******************************************************************************/
/*!
		Class Trolley:
\brief	Defines a Trolley class
*/
/******************************************************************************/
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