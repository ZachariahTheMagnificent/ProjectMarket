#include "PlayerHuman.h"


PlayerHuman::PlayerHuman(void)
{
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
	tempVector.Set(0, -50, 0);
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