#include "ShopperPayerLv1.h"


ShopperPayerLv1::ShopperPayerLv1(void)
{
	distanceNeedToMoveInOneDir = 0;
	charBodyAngleRotate = 0;
	charLegRotate = 15;
	rightLegRotateUp = true;
	points[0] = Vector3(-17.5,5,-10);// Behind inner entrance door, inside entrance room
	points[1] = Vector3(-17.5,5,-51);// Position to rotate toward the two cabinets
	points[2] = Vector3(-7.5,5,-51);// Between two cabinets
	points[3] = Vector3(-17.5,5,-83);// Beside cashier table at side
	points[4] = Vector3(-17.5,5,-95);// Position to rotate around the cashier table
	points[5] = Vector3(-11.5,5,-95);// Position to rotate toward exit door
	points[6] = Vector3(-11.5,5,-110);// Behind outer exit door, outside
	targetPosNo = 1;
	defaultTookItems = false;
	targetPosition = points[targetPosNo];
	tookItems = false;
	walkingForward = true;
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
	defaultPoint = points[No];
	defaultCharBodyAngleRotate = characterBody->transform.rotate.y;
	if(No >= 2)
	{
		takenItems();
		defaultTookItems = true;
	}
}

void ShopperPayerLv1::Update(const double dt)
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
			takenItems();
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
	//if(idling == true)
	//{
	//	characterLeftArm->selfTransform.rotate.x = -5;
	//	characterRightArm->selfTransform.rotate.x = -5;
	//	charArmRotate = 30;
	//	characterLeftLeg->selfTransform.rotate.x = 0;
	//	characterRightLeg->selfTransform.rotate.x = 0;
	//	timeIdling += dt;
	//	if(timeIdling > 5)
	//	{
	//		timeIdling = 0;
	//		idling = false;
	//		walking = true;
	//	}
	//}
	//else
	//{
	//	//If distance less than 15, character walking
	//	if(distanceMovedInOneDir < 15)
	//	{
	//		characterBody->transform.translate += characterBody->transform.rotate.MatrixY() * Vector3(0, 0, dt * 2);
	//		distanceMovedInOneDir += dt * 2;
	//		if(charArmRotate > 60)
	//			leftArmRotateUp = false;
	//		else if(charArmRotate < 0)
	//			leftArmRotateUp = true;
	//		if(leftArmRotateUp == true)
	//		{
	//			characterLeftArm->selfTransform.rotate.x -= dt * 80;
	//			characterRightArm->selfTransform.rotate.x += dt * 80;
	//			charArmRotate += dt * 80;
	//			characterLeftLeg->selfTransform.rotate.x += dt * 40;
	//			characterRightLeg->selfTransform.rotate.x -= dt * 40;
	//		}
	//		else
	//		{
	//			characterLeftArm->selfTransform.rotate.x += dt * 80;
	//			characterRightArm->selfTransform.rotate.x -= dt * 80;
	//			charArmRotate -= dt * 80;
	//			characterLeftLeg->selfTransform.rotate.x -= dt * 40;
	//			characterRightLeg->selfTransform.rotate.x += dt * 40;
	//		}
	//	}
	//	timeWalking += dt;
	//	if(timeWalking > 10)
	//	{
	//		timeWalking = 0;
	//		if(rand() % 2 == 0)
	//		{
	//			idling = false;
	//			walking = true;
	//		}
	//		else
	//		{
	//			idling = true;
	//			walking = false;
	//		}
	//	}
	//}
}

void ShopperPayerLv1::Exit()
{
}

void ShopperPayerLv1::Reset()
{
	characterBody->transform.translate = defaultPoint;
	characterBody->transform.rotate.y = defaultCharBodyAngleRotate;
	distanceNeedToMoveInOneDir = 0;
	charBodyAngleRotate = 0;
	charLegRotate = 15;
	characterLeftLeg->selfTransform.rotate.x = 0;
	characterRightLeg->selfTransform.rotate.x = 0;
	rightLegRotateUp = true;
	if(defaultTookItems == true)
	{
		takenItems();
	}
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

void ShopperPayerLv1::takenItems()
{
	items->SetParentAs(characterBody);
	items->transform.translate = Vector3(0, -1.2, 4);
	tookItems = true;
}

void ShopperPayerLv1::returnItems()
{
	items->SetParentAs(main);
	items->transform.translate = Vector3(-3.5,2,-42);
	tookItems = false;
}


void ShopperPayerLv1::DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg, drawOrder& TempItems, drawOrder& TempMain)
{
	characterBody = &TempCharacterBody;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
	items = &TempItems;
	main = &TempMain;
}

void ShopperPayerLv1::RotateChar(ShopperPayerLv1& OtherShopper)
{
//	//If distance more than 15, character rotate
//	if(distanceMovedInOneDir > 15)
//	{
//		if(characterBody->transform.translate.x <= points[0].x + 1)// Left side points
//		{
//			if(characterBody->transform.translate.z >= points[0].z - 1)// front point
//			{
//				int temp = rand() % 2;
//				if(temp == 0 && IsBlocking(OtherShopper,180) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 180; // toward -z
//				}
//				else if(temp == 1 && IsBlocking(OtherShopper,90) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 90; // toward +x
//				}
//				else
//				{
//					idling = true;
//					walking = false;
//					timeWalking = 0;
//				}
//			}
//			else if(characterBody->transform.translate.z <= points[9].z + 1)// back point
//			{
//				int temp = rand() % 2;
//				if(temp == 0 && IsBlocking(OtherShopper,0) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 0; // toward +z
//				}
//				else if(temp == 1 && IsBlocking(OtherShopper,90) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 90; // toward +x
//				}
//				else
//				{
//					idling = true;
//					walking = false;
//					timeWalking = 0;
//				}
//			}
//			else// middle points
//			{
//				int temp = rand() % 3;
//				if(temp == 0 && IsBlocking(OtherShopper,180) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 180; // toward -z
//				}
//				else if(temp == 1 && IsBlocking(OtherShopper,0) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 0; // toward +z
//				}
//				else if(temp == 2 && IsBlocking(OtherShopper,90) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 90; // toward +x
//				}
//				else
//				{
//					idling = true;
//					walking = false;
//					timeWalking = 0;
//				}
//			}
//		}
//		else
//		{
//			if(characterBody->transform.translate.z >= points[0].z - 1)// front point
//			{
//				int temp = rand() % 2;
//				if(temp == 0 && IsBlocking(OtherShopper,180) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 180; // toward -z
//				}
//				else if(temp == 1 && IsBlocking(OtherShopper,270) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 270; // toward -x
//				}
//				else
//				{
//					idling = true;
//					walking = false;
//					timeWalking = 0;
//				}
//			}
//			else if(characterBody->transform.translate.z <= points[9].z + 1)// back point
//			{
//				int temp = rand() % 2;
//				if(temp == 0 && IsBlocking(OtherShopper,0) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 0; // toward +z
//				}
//				else if(temp == 1 && IsBlocking(OtherShopper,270) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 270; // toward -x
//				}
//				else
//				{
//					idling = true;
//					walking = false;
//					timeWalking = 0;
//				}
//			}
//			else// middle points
//			{
//				int temp = rand() % 3;
//				if(temp == 0 && IsBlocking(OtherShopper,180) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 180; // toward -z
//				}
//				else if(temp == 1 && IsBlocking(OtherShopper,0) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 0; // toward +z
//				}
//				else if(temp == 2 && IsBlocking(OtherShopper,270) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 270; // toward -x
//				}
//				else
//				{
//					idling = true;
//					walking = false;
//					timeWalking = 0;
//				}
//			}
//		}
//		//rotate body
//		characterBody->transform.rotate.y = charBodyAngleRotate;
//	}
}

Vector3 ShopperPayerLv1::GetPos()
{
	return characterBody->transform.translate;
}

bool ShopperPayerLv1::IsBlocking(ShopperPayerLv1& OtherShopper, float toTurn)
{/*
	Vector3 target = characterBody->transform.translate;
	if(toTurn == 0)
		target += Vector3(0, 0, 15);
	else if(toTurn == 90)
		target += Vector3(15, 0, 0);
	else if(toTurn == 180)
		target += Vector3(0, 0, -15);
	else
		target += Vector3(-15, 0, 0);
	if(target.x < OtherShopper.GetPos().x + 15 && target.x > OtherShopper.GetPos().x - 15 && target.y == OtherShopper.GetPos().y && target.z < OtherShopper.GetPos().z + 15 && target.z > OtherShopper.GetPos().z - 15)
		return true;
	else*/
		return false;
}