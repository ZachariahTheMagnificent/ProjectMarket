#pragma once

#include "Shopper.h"
#include "DrawOrder.h"

class ShopperPayerLv1 :
	public Shopper
{
private:
	//drawOrder Pointer to character body, arms and legs
	drawOrder* characterBody;
	drawOrder* characterLeftArm;
	drawOrder* characterRightArm;
	drawOrder* characterLeftLeg;
	drawOrder* characterRightLeg;
	//viariables to store distance need to move in one direction
	float distanceNeedToMoveInOneDir;
	//viariables to store rotation of character body
	float charBodyAngleRotate;
	//viariables to store rotation of character arm
	float charArmRotate;
	//viariables to check whether the character left arm is rotating upward
	bool leftArmRotateUp;
	//Vector3 to store position checkpoint
	Vector3 points[7];
	//Vector3 to store position to go
	Vector3 targetPosition;
	//int to store position number to go
	int targetPosNo;
	//bool to check whether if character took item
	bool tookItems;
	//bool to check moving forward
	bool walkingForward;
	//Walking state
	bool walking;
	//Default position
	Vector3 defaultPoint;
	float defaultCharBodyAngleRotate;
public:
	ShopperPayerLv1(void);
	~ShopperPayerLv1(void);
	
	void Init();
	void Render();
	void SetPosition(int No);
	void Update(const double dt);
	void Exit();
	void Reset();
	void CheckDisAndTargetPos(int No);
	void DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg);
	void RotateChar(ShopperPayerLv1& OtherShopper);
	Vector3 GetPos();
	bool IsBlocking(ShopperPayerLv1& OtherShopper, float toTurn);
};