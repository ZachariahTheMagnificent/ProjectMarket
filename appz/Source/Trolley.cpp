/******************************************************************************/
/*!
\file	Trolley.cpp
\author Gregory Koh Wen Cong
\par	email: pyroflame11@gmail.com
\brief
Define Trolley Class functions
*/
/******************************************************************************/
#include "Trolley.h"


/******************************************************************************/
/*!
\brief
Constructor to initialise variables
*/
/******************************************************************************/
Trolley::Trolley(void)
{
	for(int i = 0; i < 3; ++i)
	{
		PutItemPos[i] = false;
	}
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Trolley::~Trolley(void)
{
}

/******************************************************************************/
/*!
\brief
Set the position whether between taken or not
\param itemPos - Item Position in trolley
\param taken -  bool to set if taken or not
*/
/******************************************************************************/
void Trolley::SetBoolPos(int itemPos, bool taken)
{
	PutItemPos[itemPos] = taken;
}

/******************************************************************************/
/*!
\brief
Check the position whether between taken or not
\param itemPos - Item Position in trolley
*/
/******************************************************************************/
bool Trolley::GetBoolPos(int itemPos)
{
	return PutItemPos[itemPos];
}

/******************************************************************************/
/*!
\brief
Reset to all position not taken
*/
/******************************************************************************/
void Trolley::Reset()
{
	for(int i = 0; i < 3; ++i)
	{
		PutItemPos[i] = false;
	}
}