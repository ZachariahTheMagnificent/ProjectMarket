#pragma once

#include "character.h"

class Player :
	public Character
{
public:
	Player(void);
	~Player(void);
	
	virtual void Init() = 0;
	virtual bool Update(const double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
	
	//movement
	virtual void MoveForward() = 0;
	virtual void MoveBackward() = 0;
	virtual void MoveRight() = 0;
	virtual void MoveLeft() = 0;

	Transformation transform;
};

