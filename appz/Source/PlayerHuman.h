#pragma once

#include "player.h"
#include "Range.h"

class PlayerHuman :
	public Player
{
public:
	PlayerHuman(void);
	~PlayerHuman(void);
	
	void Init();
	Vector3 Update(Camera camera);
	void Render();
	void Exit();
	void takeItems();
	void returnItems();
	
	//movement
	Vector3 MoveForward(Camera camera, double movingSpeed);
	Vector3 MoveBackward(Camera camera, double movingSpeed);
	Vector3 MoveRight(Camera camera, double movingSpeed);
	Vector3 MoveLeft(Camera camera, double movingSpeed);
	void TakingTrolley(const Vector3& PlayerTargetPos);
	void ReleaseTrolley(const Vector3& TrolleyCurrentPos);
};

