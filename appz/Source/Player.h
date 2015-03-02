#pragma once

#include "character.h"
#include "Camera.h"
#include "drawOrder.h"

class Player :
	public Character
{
protected:
	drawOrder* leftArm;
	drawOrder* rightArm;
	drawOrder* body;
	drawOrder* trolley;
public:
	Player(void);
	~Player(void);

	bool isHoldingTrolley;
	
	virtual void Init() = 0;
	virtual Vector3 Update(Camera camera) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
	
	//movement
	virtual Vector3 MoveForward(Camera camera, double movingSpeed) = 0;
	virtual Vector3 MoveBackward(Camera camera, double movingSpeed) = 0;
	virtual Vector3 MoveRight(Camera camera, double movingSpeed) = 0;
	virtual Vector3 MoveLeft(Camera camera, double movingSpeed) = 0;
	void DrawIsEqualTo(drawOrder& TempLeftArm, drawOrder& TempRightArm, drawOrder& TempBody, drawOrder& TempTrolley);
	virtual void TakingTrolley(const Vector3& PlayerTargetPos) = 0;
};

