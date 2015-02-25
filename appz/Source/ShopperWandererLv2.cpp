#include "ShopperWandererLv2.h"


ShopperWandererLv2::ShopperWandererLv2(void)
{
	distanceMovedInOneDir = 0;
	distanceSpeed = 0.2;
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
	idling = true;
	walking = true;
	timeIdling = 0;
	timeWalking = 0;
}


ShopperWandererLv2::~ShopperWandererLv2(void)
{
}

void ShopperWandererLv2::Init()
{
}

void ShopperWandererLv2::Render()
{
}

void ShopperWandererLv2::SetPosition(int No)
{
	characterBody->transform.translate = points[No];
}

void ShopperWandererLv2::Update(const double dt)
{
	if(idling == true)
	{
		characterLeftArm->selfTransform.rotate.x = -5;
		characterRightArm->selfTransform.rotate.x = -5;
		charArmRotate = 30;
		characterLeftLeg->selfTransform.rotate.x = -2.5;
		characterRightLeg->selfTransform.rotate.x = -2.5;
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
			characterBody->transform.translate += characterBody->transform.rotate.MatrixY() * Vector3(0, 0, distanceSpeed);
			distanceMovedInOneDir += distanceSpeed;
			if(charArmRotate > 60)
				leftArmRotateUp = false;
			else if(charArmRotate < 0)
				leftArmRotateUp = true;
			if(leftArmRotateUp == true)
			{
				characterLeftArm->selfTransform.rotate.x -= distanceSpeed * 50;
				characterRightArm->selfTransform.rotate.x += distanceSpeed * 50;
				charArmRotate += distanceSpeed * 50;
				characterLeftLeg->selfTransform.rotate.x += distanceSpeed * 25;
				characterRightLeg->selfTransform.rotate.x -= distanceSpeed * 25;
			}
			else
			{
				characterLeftArm->selfTransform.rotate.x += distanceSpeed * 50;
				characterRightArm->selfTransform.rotate.x -= distanceSpeed * 50;
				charArmRotate -= distanceSpeed * 50;
				characterLeftLeg->selfTransform.rotate.x -= distanceSpeed * 25;
				characterRightLeg->selfTransform.rotate.x += distanceSpeed * 25;
			}
		}
		//If distance less than 15, character rotate
		else
		{
			if(characterBody->transform.translate.x <= points[0].x + 1)
			{
				if(characterBody->transform.translate.z >= points[0].z - 1)
				{
					if(rand() % 2 == 0)
						charBodyAngleRotate = 180; // toward -z
					else
						charBodyAngleRotate = 90; // toward +x
				}
				else if(characterBody->transform.translate.z <= points[9].z + 1)
				{
					if(rand() % 2 == 0)
						charBodyAngleRotate = 0; // toward +z
					else
						charBodyAngleRotate = 90; // toward +x
				}
				else
				{
					int temp = rand() % 3;
					if(temp == 0)
						charBodyAngleRotate = 180; // toward -z
					else if(temp == 1)
						charBodyAngleRotate = 0; // toward +z
					else
						charBodyAngleRotate = 90; // toward +x
				}
			}
			else
			{
				if(characterBody->transform.translate.z >= points[0].z - 1)
				{
					if(rand() % 2 == 0)
						charBodyAngleRotate = 180; // toward -z
					else
						charBodyAngleRotate = 270; // toward -x
				}
				else if(characterBody->transform.translate.z <= points[9].z + 1)
				{
					if(rand() % 2 == 0)
						charBodyAngleRotate = 0; // toward +z
					else
						charBodyAngleRotate = 270; // toward -x
				}
				else
				{
					int temp = rand() % 3;
					if(temp == 0)
						charBodyAngleRotate = 180; // toward -z
					else if(temp == 1)
						charBodyAngleRotate = 0; // toward +z
					else
						charBodyAngleRotate = 270; // toward -x
				}
			}
			//rotate body
			characterBody->transform.rotate.y = charBodyAngleRotate;
			//reset disance moved in one direction
			distanceMovedInOneDir = 0;
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

void ShopperWandererLv2::Exit()
{
}

void ShopperWandererLv2::DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg)
{
	characterBody = &TempCharacterBody;
	characterLeftArm = &TempCharacterLeftArm;
	characterRightArm = &TempCharacterRightArm;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
}