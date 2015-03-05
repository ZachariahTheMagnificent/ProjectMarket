#include "ShopperWandererLv2.h"


ShopperWandererLv2::ShopperWandererLv2(void)
{
	// initialise all variables
	distanceMovedInOneDir = 0;
	charBodyAngleRotate = 0;
	charArmRotate = 30;
	leftArmRotateUp = true;
	
	int pointNo = 0;
	for(int disDiffX = 0; disDiffX <= 15; disDiffX += 15)
	{
		for(int disDiffZ = 0; disDiffZ <= 60; disDiffZ +=  15)
		{
			points[pointNo] = Vector3(-8.5+disDiffX,15,-37.5-disDiffZ);
			++pointNo;
		}
	}
	idling = false;
	walking = true;
	timeIdling = 0;
	timeWalking = 0;
}


ShopperWandererLv2::~ShopperWandererLv2(void)
{
}

void ShopperWandererLv2::SetPosition(int No)
{
	characterBody->transform.translate = points[No];
	if(No == 0 || No == 5)
	{
		characterBody->transform.rotate.y = 180;
	}
	else
	{
		characterBody->transform.rotate.y = 0;
	}
	defaultPoint = points[No];
	defaultCharBodyAngleRotate = characterBody->transform.rotate.y;
}

void ShopperWandererLv2::Update(const double dt)
{
	if(idling == true)
	{
		characterLeftArm->selfTransform.rotate.x = -5;
		characterRightArm->selfTransform.rotate.x = -5;
		charArmRotate = 30;
		characterLeftLeg->selfTransform.rotate.x = 0;
		characterRightLeg->selfTransform.rotate.x = 0;
		timeIdling += dt;
		if(timeIdling > 5)
		{
			timeIdling = 0;
			idling = false;
			walking = true;
		}
	}
	else
	{
		//If distance less than 15, character walking
		if(distanceMovedInOneDir < 15)
		{
			characterBody->transform.translate += characterBody->transform.rotate.MatrixY() * Vector3(0, 0, dt * 2);
			distanceMovedInOneDir += dt * 2;
			if(charArmRotate > 60)
				leftArmRotateUp = false;
			else if(charArmRotate < 0)
				leftArmRotateUp = true;
			if(leftArmRotateUp == true)
			{
				characterLeftArm->selfTransform.rotate.x -= dt * 80;
				characterRightArm->selfTransform.rotate.x += dt * 80;
				charArmRotate += dt * 80;
				characterLeftLeg->selfTransform.rotate.x += dt * 40;
				characterRightLeg->selfTransform.rotate.x -= dt * 40;
			}
			else
			{
				characterLeftArm->selfTransform.rotate.x += dt * 80;
				characterRightArm->selfTransform.rotate.x -= dt * 80;
				charArmRotate -= dt * 80;
				characterLeftLeg->selfTransform.rotate.x -= dt * 40;
				characterRightLeg->selfTransform.rotate.x += dt * 40;
			}
		}
		timeWalking += dt;
		if(timeWalking > 10)
		{
			timeWalking = 0;
			if(rand() % 2 == 0)
			{
				idling = false;
				walking = true;
			}
			else
			{
				idling = true;
				walking = false;
			}
		}
	}
}

void ShopperWandererLv2::Reset()
{
	characterBody->transform.translate = defaultPoint;
	characterBody->transform.rotate.y = defaultCharBodyAngleRotate;
	idling = false;
	walking = true;
	timeIdling = 0;
	timeWalking = 0;
	distanceMovedInOneDir = 0;
	charBodyAngleRotate = 0;
	characterLeftArm->selfTransform.rotate.x = -5;
	characterRightArm->selfTransform.rotate.x = -5;
	charArmRotate = 30;
	characterLeftLeg->selfTransform.rotate.x = 0;
	characterRightLeg->selfTransform.rotate.x = 0;
	leftArmRotateUp = true;
}

void ShopperWandererLv2::DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg)
{
	characterBody = &TempCharacterBody;
	characterLeftArm = &TempCharacterLeftArm;
	characterRightArm = &TempCharacterRightArm;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
}

void ShopperWandererLv2::RotateChar(ShopperWandererLv2& OtherShopper)
{
	//If distance more than 15, character rotate
	if(distanceMovedInOneDir > 15)
	{
		if(characterBody->transform.translate.x <= points[0].x + 1)// Left side points
		{
			if(characterBody->transform.translate.z >= points[0].z - 1)// front point
			{
				int temp = rand() % 2;
				if(temp == 0 && IsBlocking(OtherShopper,180) == false)
				{
					//reset disance moved in one direction
					distanceMovedInOneDir = 0;
					charBodyAngleRotate = 180; // toward -z
				}
				else if(temp == 1 && IsBlocking(OtherShopper,90) == false)
				{
					//reset disance moved in one direction
					distanceMovedInOneDir = 0;
					charBodyAngleRotate = 90; // toward +x
				}
				else
				{
					idling = true;
					walking = false;
					timeWalking = 0;
				}
			}
			else if(characterBody->transform.translate.z <= points[9].z + 1)// back point
			{
				int temp = rand() % 2;
				if(temp == 0 && IsBlocking(OtherShopper,0) == false)
				{
					//reset disance moved in one direction
					distanceMovedInOneDir = 0;
					charBodyAngleRotate = 0; // toward +z
				}
				else if(temp == 1 && IsBlocking(OtherShopper,90) == false)
				{
					//reset disance moved in one direction
					distanceMovedInOneDir = 0;
					charBodyAngleRotate = 90; // toward +x
				}
				else
				{
					idling = true;
					walking = false;
					timeWalking = 0;
				}
			}
			else// middle points
			{
				int temp = rand() % 3;
				if(temp == 0 && IsBlocking(OtherShopper,180) == false)
				{
					//reset disance moved in one direction
					distanceMovedInOneDir = 0;
					charBodyAngleRotate = 180; // toward -z
				}
				else if(temp == 1 && IsBlocking(OtherShopper,0) == false)
				{
					//reset disance moved in one direction
					distanceMovedInOneDir = 0;
					charBodyAngleRotate = 0; // toward +z
				}
				else if(temp == 2 && IsBlocking(OtherShopper,90) == false)
				{
					//reset disance moved in one direction
					distanceMovedInOneDir = 0;
					charBodyAngleRotate = 90; // toward +x
				}
				else
				{
					idling = true;
					walking = false;
					timeWalking = 0;
				}
			}
		}
		else
		{
			if(characterBody->transform.translate.z >= points[0].z - 1)// front point
			{
				int temp = rand() % 2;
				if(temp == 0 && IsBlocking(OtherShopper,180) == false)
				{
					//reset disance moved in one direction
					distanceMovedInOneDir = 0;
					charBodyAngleRotate = 180; // toward -z
				}
				else if(temp == 1 && IsBlocking(OtherShopper,270) == false)
				{
					//reset disance moved in one direction
					distanceMovedInOneDir = 0;
					charBodyAngleRotate = 270; // toward -x
				}
				else
				{
					idling = true;
					walking = false;
					timeWalking = 0;
				}
			}
			else if(characterBody->transform.translate.z <= points[9].z + 1)// back point
			{
				int temp = rand() % 2;
				if(temp == 0 && IsBlocking(OtherShopper,0) == false)
				{
					//reset disance moved in one direction
					distanceMovedInOneDir = 0;
					charBodyAngleRotate = 0; // toward +z
				}
				else if(temp == 1 && IsBlocking(OtherShopper,270) == false)
				{
					//reset disance moved in one direction
					distanceMovedInOneDir = 0;
					charBodyAngleRotate = 270; // toward -x
				}
				else
				{
					idling = true;
					walking = false;
					timeWalking = 0;
				}
			}
			else// middle points
			{
				int temp = rand() % 3;
				if(temp == 0 && IsBlocking(OtherShopper,180) == false)
				{
					//reset disance moved in one direction
					distanceMovedInOneDir = 0;
					charBodyAngleRotate = 180; // toward -z
				}
				else if(temp == 1 && IsBlocking(OtherShopper,0) == false)
				{
					//reset disance moved in one direction
					distanceMovedInOneDir = 0;
					charBodyAngleRotate = 0; // toward +z
				}
				else if(temp == 2 && IsBlocking(OtherShopper,270) == false)
				{
					//reset disance moved in one direction
					distanceMovedInOneDir = 0;
					charBodyAngleRotate = 270; // toward -x
				}
				else
				{
					idling = true;
					walking = false;
					timeWalking = 0;
				}
			}
		}
		//rotate body
		characterBody->transform.rotate.y = charBodyAngleRotate;
	}
}

Vector3 ShopperWandererLv2::GetPos()
{
	return characterBody->transform.translate;
}

bool ShopperWandererLv2::IsBlocking(ShopperWandererLv2& OtherShopper, float toTurn)
{
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
	else
		return false;
}