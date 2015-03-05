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
	//viariables to store distance moved
	float distanceMovedInOneDir;
	//viariables to store rotation of character body
	float charBodyAngleRotate;
	//viariables to store rotation of character arm
	float charArmRotate;
	//viariables to check whether the character left arm is rotating upward
	bool leftArmRotateUp;
	//Vector3 to store position checkpoint
	Vector3 points[2];
	//Walking state
	bool walking;
	//Time spent walking
	float timeWalking;
	//Idling state
	bool idling;
	bool startwalking;
	//Time spent idling
	float timeIdling;
	//Default position
	Vector3 defaultPoint;
	float defaultCharBodyAngleRotate;
public:
	ShopperIdler(void);
	~ShopperIdler(void);
	
	void SetPosition(int No);
	void Update(const double dt);
	void Reset();
	void DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg);
};