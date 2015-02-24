#pragma once

#include "character.h"

class Shopper :
	public Character
{
public:
	Shopper(void);
	~Shopper(void);
	
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};
