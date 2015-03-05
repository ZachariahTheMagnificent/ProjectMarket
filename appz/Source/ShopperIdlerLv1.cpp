#include "ShopperIdlerLv1.h"


ShopperIdler::ShopperIdler(void)
{
	distanceMovedInOneDir = 0;
	charBodyAngleRotate = 0;
	charArmRotate = 30;
	leftArmRotateUp = true;

	int pointNo = 0;
	for(int disDiffZ = 0; disDiffZ <= 17; disDiffZ += 17 )
	{
		points[pointNo] = Vector3(5,5,-37.5-disDiffZ);
		++pointNo;
	}
	idling = true;
	walking = false;
	timeIdling = 0;
	timeWalking = 0;
}


ShopperIdler::~ShopperIdler(void)
{
}

void ShopperIdler::SetPosition(int No)
{
	characterBody->transform.translate = points[No];
		characterBody->transform.rotate.y = 270;
	defaultPoint = points[No];
	defaultCharBodyAngleRotate = characterBody->transform.rotate.y;
}

void ShopperIdler::Update(const double dt)
{
	if(idling == true)
	{
		characterBody->transform.rotate.y=270;
		characterLeftArm->selfTransform.rotate.x = -5;
		characterRightArm->selfTransform.rotate.x = -5;
		charArmRotate = 30;
		characterLeftLeg->selfTransform.rotate.x = 0;
		characterRightLeg->selfTransform.rotate.x = 0;
		timeIdling += dt;
		if(timeIdling > 2)
		{
			timeIdling = 0;
			int temp = rand() % 2;
			//continue walking
			if(temp==0)
			{
			if(characterBody->transform.translate.z >= points[0].z-1)
			{
				characterBody->transform.rotate.y=180;
			}
			else if(characterBody->transform.translate.z <= points[1].z+1)
			{
				characterBody->transform.rotate.y=0;
			}
				idling=false;
				walking=true;
			}
			//if temp=1,continue idling.
		}
	}
	else
	{
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
		characterBody->transform.translate += characterBody->transform.rotate.MatrixY() * Vector3(0, 0, dt * 5);
		distanceMovedInOneDir += dt*5;
		if(distanceMovedInOneDir>17)
		{
			walking=false;
			idling=true;
			distanceMovedInOneDir=0;
		}
	}
}

void ShopperIdler::Reset()
{
	idling = true;
	walking = false;
	timeIdling = 0;
	timeWalking = 0;
	//timeWalking = 0;
	distanceMovedInOneDir = 0;
	charBodyAngleRotate = 0;
	characterLeftArm->selfTransform.rotate.x = -5;
	characterRightArm->selfTransform.rotate.x = -5;
	charArmRotate = 30;
	characterLeftLeg->selfTransform.rotate.x = 0;
	characterRightLeg->selfTransform.rotate.x = 0;
	leftArmRotateUp = true;
	characterBody->transform.translate = defaultPoint;
	characterBody->transform.rotate.y = defaultCharBodyAngleRotate;
}

void ShopperIdler::DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg)
{
	characterBody = &TempCharacterBody;
	characterLeftArm = &TempCharacterLeftArm;
	characterRightArm = &TempCharacterRightArm;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
}
