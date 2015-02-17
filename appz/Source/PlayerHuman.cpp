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
	tempVector.Set(0, -100, 0);
	return tempVector;
}

void PlayerHuman::Render()
{
}

void PlayerHuman::Exit()
{
}

Vector3 PlayerHuman::MoveForward(Camera camera)
{
	Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
	Vector3 tempVector;
	tempVector.Set(6000, 0, 0);
	tempVector = rotationMatrix * tempVector;
	return tempVector;
}

Vector3 PlayerHuman::MoveBackward(Camera camera)
{
	Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
	Vector3 tempVector;
	tempVector.Set(-6000, 0, 0);
	tempVector = rotationMatrix * tempVector;
	return tempVector;
}

Vector3 PlayerHuman::MoveRight(Camera camera)
{
	Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
	Vector3 tempVector;
	tempVector.Set(0, 0, 6000);
	tempVector = rotationMatrix * tempVector;
	return tempVector;
}

Vector3 PlayerHuman::MoveLeft(Camera camera)
{
	Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
	Vector3 tempVector;
	tempVector.Set(0, 0, -6000);
	tempVector = rotationMatrix * tempVector;
	return tempVector;
}