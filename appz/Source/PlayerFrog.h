#pragma once

#include "player.h"

class PlayerFrog :
	public Player
{
public:
	PlayerFrog(void);
	~PlayerFrog(void);
	
	virtual void Init() = 0;
	virtual bool Update(const double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;

	Transformation transform;
};

