#pragma once

#include "player.h"

class PlayerFrog :
	public Player
{
public:
	PlayerFrog(void);
	~PlayerFrog(void);
	
	Vector3 Update(Camera camera);
	
	//movement
	Vector3 MoveForward(Camera camera, double movingSpeed);
	Vector3 MoveBackward(Camera camera, double movingSpeed);
	Vector3 MoveRight(Camera camera, double movingSpeed);
	Vector3 MoveLeft(Camera camera, double movingSpeed);
	virtual void TakingTrolley(const Camera& camera);
	virtual void ReleaseTrolley(const Vector3& TrolleyCurrentPos);
};

