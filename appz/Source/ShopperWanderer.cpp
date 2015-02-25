#include "ShopperWanderer.h"


ShopperWanderer::ShopperWanderer(void)
{
	distanceMovedInOneDir = 0;
	distanceSpeed = 0.1;
	charBodyAngleRotate = 0;
	charArmRotate = 0;
	leftArmRotateUp = true;
}


ShopperWanderer::~ShopperWanderer(void)
{
}

void ShopperWanderer::Init()
{
}

void ShopperWanderer::Render()
{
}

void ShopperWanderer::Update(const double dt)
{
	//If distance less than 10, character walking
	if(distanceMovedInOneDir < 50)
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
	//If distance less than 10, character rotate
	else
	{
		//rotate body
		charBodyAngleRotate += 90;
		characterBody->transform.rotate.y = charBodyAngleRotate;
		//reset disance moved in one direction
		distanceMovedInOneDir = 0;
	}
}

void ShopperWanderer::Exit()
{
}

void ShopperWanderer::DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg)
{
	characterBody = &TempCharacterBody;
	characterLeftArm = &TempCharacterLeftArm;
	characterRightArm = &TempCharacterRightArm;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
}