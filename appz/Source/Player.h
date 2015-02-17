#pragma once

#include "character.h"
#include "Camera.h"

class Player :
	public Character
{
public:
	Player(void);
	~Player(void);
	
	virtual void Init();
	virtual Vector3 Update(Camera camera);
	virtual void Render();
	virtual void Exit();
	
	//movement
	virtual Vector3 MoveForward(Camera camera, double movingSpeed);
	virtual Vector3 MoveBackward(Camera camera, double movingSpeed);
	virtual Vector3 MoveRight(Camera camera, double movingSpeed);
	virtual Vector3 MoveLeft(Camera camera, double movingSpeed);
};

