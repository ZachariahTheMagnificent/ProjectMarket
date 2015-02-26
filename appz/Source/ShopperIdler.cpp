#include "ShopperIdler.h"


ShopperIdler::ShopperIdler(void)
{
	distanceMovedInOneDir = 0;
	distanceSpeed = 0.1;
	charBodyAngleRotate = 0;
	charArmRotate = 0;
	leftArmRotateUp = true;
	
	int pointNo = 0;
	for(int disDiffX = 0; disDiffX <= 12; disDiffX += 12)
	{
		for(int disDiffZ = 0; disDiffZ <= 60; disDiffZ +=  15)
		{
			points[pointNo] = Vector3(-6.5+disDiffX,15,-37.5-disDiffZ);
			++pointNo;
		}
	}
}


ShopperIdler::~ShopperIdler(void)
{
}

void ShopperIdler::Init()
{
}

void ShopperIdler::Render()
{
}

void ShopperIdler::SetPosition(int No)
{
	characterBody->transform.translate = points[No];
}

void ShopperIdler::Update(const double dt)
{
	//If distance less than 15, character walking
	if(distanceMovedInOneDir < 7)
	{
		characterBody->transform.translate += characterBody->transform.rotate.MatrixY() * Vector3(0, 0, distanceSpeed);
		distanceMovedInOneDir += distanceSpeed;
		if(charArmRotate > 60)
			leftArmRotateUp = false;
		else if(charArmRotate < 0)
			leftArmRotateUp = true;
		if(leftArmRotateUp == true)
		{
			characterLeftArm->selfTransform.rotate.x -= distanceSpeed * 10;
			characterRightArm->selfTransform.rotate.x += distanceSpeed * 10;
			charArmRotate += distanceSpeed * 10;
			characterLeftLeg->selfTransform.rotate.x += distanceSpeed * 5;
			characterRightLeg->selfTransform.rotate.x -= distanceSpeed * 5;
		}
		else
		{
			characterLeftArm->selfTransform.rotate.x += distanceSpeed * 10;
			characterRightArm->selfTransform.rotate.x -= distanceSpeed * 10;
			charArmRotate -= distanceSpeed * 10;
			characterLeftLeg->selfTransform.rotate.x -= distanceSpeed * 5;
			characterRightLeg->selfTransform.rotate.x += distanceSpeed * 5;
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
}

void ShopperIdler::Exit()
{
}

void ShopperIdler::DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg)
{
	characterBody = &TempCharacterBody;
	characterLeftArm = &TempCharacterLeftArm;
	characterRightArm = &TempCharacterRightArm;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
}