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

	Transformation transform;
};

