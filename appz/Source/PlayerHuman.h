#pragma once

#include "player.h"

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
	
	//movement
	Vector3 MoveForward(Camera camera);
	Vector3 MoveBackward(Camera camera);
	Vector3 MoveRight(Camera camera);
	Vector3 MoveLeft(Camera camera);
};

