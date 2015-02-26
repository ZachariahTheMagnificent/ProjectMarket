#pragma once

#include "Shopper.h"
#include "DrawOrder.h"

class ShopperIdler :
	public Shopper
{
private:
	//drawOrder Pointer to character body, arms and legs
	drawOrder* characterBody;
	drawOrder* characterLeftArm;
	drawOrder* characterRightArm;
	drawOrder* characterLeftLeg;
	drawOrder* characterRightLeg;
	//viariables to store moving speed, distance moved
	float distanceSpeed;
	float distanceMovedInOneDir;
	//viariables to store rotation of character body
	float charBodyAngleRotate;
	//viariables to store rotation of character arm
	float charArmRotate;
	//viariables to check whether the character left arm is rotating upward
	bool leftArmRotateUp;
	Vector3 points[2];
public:
	ShopperIdler(void);
	~ShopperIdler(void);
	
	void Init();
	void Render();
	void SetPosition(int No);
	void Update(const double dt);
	void Exit();
	void DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg);
};