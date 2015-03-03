#include "ShopperPayerLv1.h"


ShopperPayerLv1::ShopperPayerLv1(void)
{
	distanceNeedToMoveInOneDir = 0;
	charBodyAngleRotate = 0;
	charLegRotate = 15;
	rightLegRotateUp = true;
	points[0] = Vector3(-18,5,-10);// Behind inner entrance door, inside entrance room
	points[1] = Vector3(-18,5,-51);// Position to rotate toward the two cabinets
	points[2] = Vector3(-7.5,5,-51);// Between two cabinets
	points[3] = Vector3(-18,5,-83);// Beside cashier table at side
	points[4] = Vector3(-18,5,-95);// Position to rotate around the cashier table
	points[5] = Vector3(-11.5,5,-95);// Position to rotate toward exit door
	points[6] = Vector3(-11.5,5,-110);// Behind outer exit door, outside
	targetPosNo = 1;
	targetPosition = points[targetPosNo];
	tookItems = false;
	currentState = WALKING;
	walkingForward = true;
	paid = false;
	defaultPoint = 0;
	payingdistance = 0;
}


ShopperPayerLv1::~ShopperPayerLv1(void)
{
}

void ShopperPayerLv1::Init()
{
}

void ShopperPayerLv1::Render()
{
}

void ShopperPayerLv1::SetPosition(int No)
{
	if(No == 9)
		No = 0;
	characterBody->transform.translate = points[No];
	CheckDisAndTargetPos(No);
	defaultPoint = No;
	if(No >= 2)
	{
		takingItems();
	}
	if(No == 2)
		currentState = TAKING;
	else if(No == 3)
		currentState = PAYING;
	if(No >= 3)
		paid = true;
	else
		paid = false;
}

void ShopperPayerLv1::Update(const double dt)
{
	if(currentState == WALKING) // Walking
	{
		if(distanceNeedToMoveInOneDir > 0)
		{
			if(walkingForward == true)
				characterBody->transform.translate += characterBody->transform.rotate.MatrixY() * Vector3(0, 0, dt * 2);
			else
				characterBody->transform.translate += characterBody->transform.rotate.MatrixY() * Vector3(0, 0, -dt * 2);
			distanceNeedToMoveInOneDir -= dt * 2;
			if(charLegRotate > 30)
				rightLegRotateUp = false;
			else if(charLegRotate < 0)
				rightLegRotateUp = true;
			if(rightLegRotateUp == true)
			{
				characterLeftLeg->selfTransform.rotate.x += dt * 40;
				characterRightLeg->selfTransform.rotate.x -= dt * 40;
				charLegRotate += dt * 40;
			}
			else
			{
				characterLeftLeg->selfTransform.rotate.x -= dt * 40;
				characterRightLeg->selfTransform.rotate.x += dt * 40;
				charLegRotate -= dt * 40;
			}
		}
		else
		{
			if(targetPosNo == 2 && tookItems == false)
			{
				currentState = TAKING;
			}
			else if(targetPosNo == 3 && tookItems == true)
			{
				currentState = PAYING;
			}
			else
			{
				if(targetPosNo == 0)
				{
					SetPosition(0);
					returnItems();
				}
				else
					CheckDisAndTargetPos(targetPosNo);
			}
		}
	}
	else if(currentState == TAKING) //taking
	{
		takingItems();
	}
	else // Paying
	{
		if(tookItems == true)
			putItemOntable();
		paying(dt);
		if(paid == true)
			CheckDisAndTargetPos(3);
	}
}

void ShopperPayerLv1::Exit()
{
}

void ShopperPayerLv1::Reset()
{
	SetPosition(defaultPoint);
	distanceNeedToMoveInOneDir = 0;
	charBodyAngleRotate = 0;
	charLegRotate = 15;
	characterLeftLeg->selfTransform.rotate.x = 0;
	characterRightLeg->selfTransform.rotate.x = 0;
	rightLegRotateUp = true;
	payingdistance = 0;
}

void ShopperPayerLv1::CheckDisAndTargetPos(int No)
{
	//Facing
	if(No == 1 || No == 2 || No == 4)//Face right
	{
		if(walkingForward == false)
			characterBody->transform.rotate.y = 180;
		else
			characterBody->transform.rotate.y = 90;
	}
	else//Face front
		characterBody->transform.rotate.y = 180;
	charBodyAngleRotate = characterBody->transform.rotate.y;

	if(No == 2)//for moving back to previous point
	{
		targetPosNo = No - 1;
	}
	else if(No == 6)//Back to entrance
	{
		targetPosNo = 0;
	}
	else//moving toward next point
	{
		if(walkingForward == false)//Back from pos[2] at pos[1] to pos[4]
			targetPosNo = No + 2;
		else
			targetPosNo = No + 1;
	}
	targetPosition = points[targetPosNo];
	if(charBodyAngleRotate == 180) // forward
	{
		distanceNeedToMoveInOneDir =  characterBody->transform.translate.z - targetPosition.z;
		walkingForward = true;
	}
	else if(charBodyAngleRotate == 90)
	{
		if(No == 2 && targetPosNo == 1)//Leftward
		{
			distanceNeedToMoveInOneDir =  characterBody->transform.translate.x - targetPosition.x;
			walkingForward = false;
		}
		else//Rightward
		{
			distanceNeedToMoveInOneDir = targetPosition.x - characterBody->transform.translate.x;
			walkingForward = true;
		}
	}
}

void ShopperPayerLv1::takingItems()
{
	item1->SetParentAs(characterBody);
	item1->transform.translate = Vector3(0, -2.4, 4);
	tookItems = true;
	currentState = WALKING;
}

void ShopperPayerLv1::returnItems()
{
	item1->SetParentAs(cabinet);
	item1->transform.translate = Vector3(0,1.5,0);
	tookItems = false;
}

void ShopperPayerLv1::paying(const double dt)
{
	if(paid == false)
	{
		item1->transform.translate.z -= dt * 0.5;
		payingdistance += dt * 0.5;
		if(payingdistance > 6.5)
		{
			paid = true;
			payingdistance = 0;
		}
		else if(payingdistance > 2.75)
		{
			item1->transform.translate.y = 4;
		}
		else if(payingdistance > 2.25)
		{
			item1->transform.translate.y -= dt * 0.5;
		}
	}
	else
	{
		takingItems();
		currentState = WALKING;
	}
}

void ShopperPayerLv1::putItemOntable()
{
	tookItems = false;
	item1->SetParentAs(cashierTable);
	item1->transform.translate = Vector3(-4, 4.5, 0);
}

void ShopperPayerLv1::DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg, drawOrder& TempItem1, drawOrder& TempCabinet, drawOrder& TempCashierTable)
{
	characterBody = &TempCharacterBody;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
	item1 = &TempItem1;
	cabinet = &TempCabinet;
	cashierTable = &TempCashierTable;
}