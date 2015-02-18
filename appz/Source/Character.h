#pragma once

#include "Vector3.h"
#include "DrawOrder.h"

class Character
{
public:
	Character(void);
	~Character(void);
	
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;

	Transformation transform;
};