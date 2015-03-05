/******************************************************************************/
/*!
\file	PlayerHuman.cpp
\author Gregory Koh Wen Cong
\par	email: pyroflame11@gmail.com
\brief
Define PlayerHuman Class functions
*/
/******************************************************************************/
#include "PlayerHuman.h"


/******************************************************************************/
/*!
\brief
Constructor to initialise variables
*/
/******************************************************************************/
PlayerHuman::PlayerHuman(void)
{
	isHoldingTrolley = false;
	isHoldingItem = false;
	isHoldingChild = false;
	paying = false;
	pay = false;
}


/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
PlayerHuman::~PlayerHuman(void)
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
Vector3 PlayerHuman::MoveForward(Camera camera, double movingSpeed)
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
Vector3 PlayerHuman::MoveBackward(Camera camera, double movingSpeed)
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
Vector3 PlayerHuman::MoveRight(Camera camera, double movingSpeed)
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
Vector3 PlayerHuman::MoveLeft(Camera camera, double movingSpeed)
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
void PlayerHuman::TakingTrolley(const Camera& camera)
{
	if(isHoldingTrolley == false)
	{
		if(camera.IsLookingAt(trolley->GetGlobalPosition(), 20, 5))
		{
			trolley->SetParentAs(body);
			trolley->transform.rotate.Set(0,0,0);
			trolley->selfTransform.translate.Set(0,0,0);
			trolley->transform.translate.Set(2,0.61,0);
			isHoldingTrolley = true;
		}
	}
}

/******************************************************************************/
/*!
\brief
Release trolley
\param TrolleyCurrentPos - Point to trolley actual current postion
*/
/******************************************************************************/
void PlayerHuman::ReleaseTrolley(const Vector3& TrolleyCurrentPos)
{
	if(isHoldingTrolley == true)
	{
		trolley->SetParentAs(main);
		trolley->transform.rotate.Set(0,0,0);
		trolley->selfTransform.translate.Set(0,0,0);
		trolley->transform.translate.Set(0,0,0);
		trolley->transform.rotate.y = body->transform.rotate.y;
		trolley->transform.translate += TrolleyCurrentPos;

		isHoldingTrolley = false;
	}
}