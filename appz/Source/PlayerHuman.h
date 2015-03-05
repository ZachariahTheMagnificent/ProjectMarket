/******************************************************************************/
/*!
\file	PlayerHuman.h
\author Gregory Koh Wen Cong
\par	email: pyroflame11@gmail.com
\brief
Class to store Human player
*/
/******************************************************************************/
#pragma once

#include "player.h"
#include "Range.h"

/******************************************************************************/
/*!
		Class PlayerHuman:
\brief	Defines a PlayerHuman class
*/
/******************************************************************************/
class PlayerHuman :
	public Player
{
public:
	PlayerHuman(void);
	~PlayerHuman(void);
	
	void takeItems();
	void returnItems();
	
	//movement
	Vector3 MoveForward(Camera camera, double movingSpeed);
	Vector3 MoveBackward(Camera camera, double movingSpeed);
	Vector3 MoveRight(Camera camera, double movingSpeed);
	Vector3 MoveLeft(Camera camera, double movingSpeed);
	void TakingTrolley(const Camera& camera);
	void ReleaseTrolley(const Vector3& TrolleyCurrentPos);
};

