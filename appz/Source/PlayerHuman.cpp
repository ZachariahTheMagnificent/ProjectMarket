#include "PlayerHuman.h"


PlayerHuman::PlayerHuman(void)
{
	isHoldingTrolley = false;
	isHoldingItem = false;
	isHoldingChild = false;
	paying = false;
	pay = false;
}


PlayerHuman::~PlayerHuman(void)
{
}

void PlayerHuman::Init()
{
}

Vector3 PlayerHuman::Update(Camera camera)
{
	Vector3 tempVector;
	tempVector.Set(0, 0, 0);
	return tempVector;
}

void PlayerHuman::Render()
{
}

void PlayerHuman::Exit()
{
}

Vector3 PlayerHuman::MoveForward(Camera camera, double movingSpeed)
{
	Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
	Vector3 tempVector;
	tempVector.Set(movingSpeed, 0, 0);
	tempVector = rotationMatrix * tempVector;
	return tempVector;
}

Vector3 PlayerHuman::MoveBackward(Camera camera, double movingSpeed)
{
	Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
	Vector3 tempVector;
	tempVector.Set(-movingSpeed, 0, 0);
	tempVector = rotationMatrix * tempVector;
	return tempVector;
}

Vector3 PlayerHuman::MoveRight(Camera camera, double movingSpeed)
{
	Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
	Vector3 tempVector;
	tempVector.Set(0, 0, movingSpeed);
	tempVector = rotationMatrix * tempVector;
	return tempVector;
}

Vector3 PlayerHuman::MoveLeft(Camera camera, double movingSpeed)
{
	Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
	Vector3 tempVector;
	tempVector.Set(0, 0, -movingSpeed);
	tempVector = rotationMatrix * tempVector;
	return tempVector;
}

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