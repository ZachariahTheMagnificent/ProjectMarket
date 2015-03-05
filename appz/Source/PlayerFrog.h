/******************************************************************************/
/*!
\file	PlayerFrog.h
\author Gregory Koh Wen Cong
\par	email: pyroflame11@gmail.com
\brief
Class to store frog player
*/
/******************************************************************************/
#pragma once

#include "player.h"

/******************************************************************************/
/*!
		Class PlayerFrog:
\brief	Defines a PlayerFrog class
*/
/******************************************************************************/
class PlayerFrog :
	public Player
{
public:
	PlayerFrog(void);
	~PlayerFrog(void);
	
	//movement
	Vector3 MoveForward(Camera camera, double movingSpeed);
	Vector3 MoveBackward(Camera camera, double movingSpeed);
	Vector3 MoveRight(Camera camera, double movingSpeed);
	Vector3 MoveLeft(Camera camera, double movingSpeed);
	virtual void TakingTrolley(const Camera& camera);
	virtual void ReleaseTrolley(const Vector3& TrolleyCurrentPos);
};

