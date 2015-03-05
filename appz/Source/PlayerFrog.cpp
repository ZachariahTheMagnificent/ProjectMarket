/******************************************************************************/
/*!
\file	PlayerFrog.cpp
\author Gregory Koh Wen Cong
\par	email: pyroflame11@gmail.com
\brief
Define PlayerFog Class functions
*/
/******************************************************************************/
#include "PlayerFrog.h"


/******************************************************************************/
/*!
\brief
Constructor to initialise variables
*/
/******************************************************************************/
PlayerFrog::PlayerFrog(void)
{
	isHoldingTrolley = false;
	isHoldingItem = false;
	paying = false;
	pay = false;
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
PlayerFrog::~PlayerFrog(void)
{
}

/******************************************************************************/
/*!
\brief
Move player forward
\param camera- Camera
\param movingSpeed- moving speed that store as double
\return Vector3 that will move the player
*/
/******************************************************************************/
Vector3 PlayerFrog::MoveForward(Camera camera, double movingSpeed)
{
	Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
	Vector3 tempVector;
	tempVector.Set(movingSpeed, 0, 0);
	tempVector = rotationMatrix * tempVector;
	return tempVector;
}

/******************************************************************************/
/*!
\brief
Move player backward
\param camera- Camera
\param movingSpeed- moving speed that store as double
\return Vector3 that will move the player
*/
/******************************************************************************/
Vector3 PlayerFrog::MoveBackward(Camera camera, double movingSpeed)
{
	Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
	Vector3 tempVector;
	tempVector.Set(-movingSpeed, 0, 0);
	tempVector = rotationMatrix * tempVector;
	return tempVector;
}

/******************************************************************************/
/*!
\brief
Move player to the right
\param camera- Camera
\param movingSpeed- moving speed that store as double
\return Vector3 that will move the player
*/
/******************************************************************************/
Vector3 PlayerFrog::MoveRight(Camera camera, double movingSpeed)
{
	Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
	Vector3 tempVector;
	tempVector.Set(0, 0, movingSpeed);
	tempVector = rotationMatrix * tempVector;
	return tempVector;
}

/******************************************************************************/
/*!
\brief
Move player to the left
\param camera- Camera
\param movingSpeed- moving speed that store as double
\return Vector3 that will move the player
*/
/******************************************************************************/
Vector3 PlayerFrog::MoveLeft(Camera camera, double movingSpeed)
{
	Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
	Vector3 tempVector;
	tempVector.Set(0, 0, -movingSpeed);
	tempVector = rotationMatrix * tempVector;
	return tempVector;
}

/******************************************************************************/
/*!
\brief
Take trolley
\param camera - Point to camera
*/
/******************************************************************************/
void PlayerFrog::TakingTrolley(const Camera& camera)
{
}

/******************************************************************************/
/*!
\brief
Release trolley
\param TrolleyCurrentPos - Point to trolley actual current postion
*/
/******************************************************************************/
void PlayerFrog::ReleaseTrolley(const Vector3& TrolleyCurrentPos)
{
	if(isHoldingTrolley == true)
	{
		trolley->SetParentAs(main);
		trolley->transform.rotate.Set(0,0,0);
		trolley->selfTransform.translate.Set(0,0,0);
		trolley->transform.translate.Set(0,0,0);
		trolley->transform.rotate.y = body->transform.rotate.y;
		trolley->transform.translate += TrolleyCurrentPos + body->transform.rotate.MatrixY() * Vector3(5,-3,0);
		isHoldingTrolley = false;
	}
}