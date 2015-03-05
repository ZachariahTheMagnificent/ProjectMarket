#pragma once

#include "Shopper.h"
#include "DrawOrder.h"

class ShopperPayerLv1 :
	public Shopper
{
private:
	//drawOrder Pointer to character body, arms and legs
	drawOrder* characterBody;
	drawOrder* characterLeftLeg;
	drawOrder* characterRightLeg;
	drawOrder* item1;
	drawOrder* cabinet;
	drawOrder* cashierTable;
	//viariables to store distance need to move in one direction
	float distanceNeedToMoveInOneDir;
	//viariables to store rotation of character body
	float charBodyAngleRotate;
	//viariables to store rotation of character legs
	float charLegRotate;
	//viariables to check whether the character right leg is rotating upward
	bool rightLegRotateUp;
	//Vector3 to store position checkpoint
	Vector3 points[7];
	//Vector3 to store position to go
	Vector3 targetPosition;
	//int to store position number to go
	int targetPosNo;
	//bool to check whether if character took item
	bool tookItems;
	//bool to check whether if character paid
	bool paid;
	//viariable to store distance tthe item to get paid
	float payingdistance;
	//bool to check moving forward
	bool walkingForward;
	//Default position
	int defaultPoint;



public:
	ShopperPayerLv1(void);
	~ShopperPayerLv1(void);
	
		enum state
	{
		WALKING,
		TAKING,
		PAYING,
	};
	state currentState;
	void SetPosition(int No);
	void Update(const double dt);
	void Reset();
	void CheckDisAndTargetPos(int No);
	void takingItems();
	void returnItems();
	void paying(const double dt);
	void putItemOntable();
	void DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg, drawOrder& TempItems, drawOrder& TempCabinet, drawOrder& TempCashierTable);
};