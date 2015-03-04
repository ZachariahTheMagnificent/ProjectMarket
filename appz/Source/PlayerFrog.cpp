#include "PlayerFrog.h"


PlayerFrog::PlayerFrog(void)
{
	isHoldingTrolley = false;
	isHoldingItem = false;
	paying = false;
}


PlayerFrog::~PlayerFrog(void)
{
}

void PlayerFrog::Init()
{
}

Vector3 PlayerFrog::Update(Camera camera)
{
	Vector3 tempVector;
	tempVector.Set(0, 0, 0);
	return tempVector;
}

void PlayerFrog::Render()
{
}

void PlayerFrog::Exit()
{
}

Vector3 PlayerFrog::MoveForward(Camera camera, double movingSpeed)
{
	Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
	Vector3 tempVector;
	tempVector.Set(movingSpeed, 0, 0);
	tempVector = rotationMatrix * tempVector;
	return tempVector;
}

Vector3 PlayerFrog::MoveBackward(Camera camera, double movingSpeed)
{
	Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
	Vector3 tempVector;
	tempVector.Set(-movingSpeed, 0, 0);
	tempVector = rotationMatrix * tempVector;
	return tempVector;
}

Vector3 PlayerFrog::MoveRight(Camera camera, double movingSpeed)
{
	Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
	Vector3 tempVector;
	tempVector.Set(0, 0, movingSpeed);
	tempVector = rotationMatrix * tempVector;
	return tempVector;
}

Vector3 PlayerFrog::MoveLeft(Camera camera, double movingSpeed)
{
	Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
	Vector3 tempVector;
	tempVector.Set(0, 0, -movingSpeed);
	tempVector = rotationMatrix * tempVector;
	return tempVector;
}

void PlayerFrog::TakingTrolley(const Camera& camera)
{
}

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