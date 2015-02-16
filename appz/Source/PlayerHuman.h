#pragma once

#include "player.h"

class PlayerHuman :
	public Player
{
public:
	PlayerHuman(void);
	~PlayerHuman(void);
	
	virtual void Init() = 0;
	virtual bool Update(const double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;

	Transformation transform;
};

