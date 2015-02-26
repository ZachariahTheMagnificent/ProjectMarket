#include "ShopperIdlerLv1.h"


ShopperIdler::ShopperIdler(void)
{
	distanceMovedInOneDir = 0;
	charBodyAngleRotate = 0;
	charArmRotate = 30;
	leftArmRotateUp = true;
	
	int pointNo = 0;
	for(int disDiffX = 0; disDiffX <=0 ; disDiffX += 0)
	{
		for(int disDiffZ = 0; disDiffZ <= 7; disDiffZ += 7 )
		{
			points[pointNo] = Vector3(-8.5+disDiffX,15,-37.5-disDiffZ);
			++pointNo;
		}
	}
	idling = true;
	walking = false;
	timeIdling = 0;
	timeWalking = 0;

}


ShopperIdler::~ShopperIdler(void)
{
}

void ShopperIdler::Init()
{
	characterBody->transform.rotate.y=270;
}

void ShopperIdler::Render()
{
}

void ShopperIdler::SetPosition(int No)
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

void ShopperIdler::Update(const double dt)
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
			int temp = rand() % 2;
			//continue walking
			if(temp =0)
			{
				idling=false;
				walking=true;
			}
			//if temp=1,continue idling.
		}
	}
	else
	{
			characterBody->transform.rotate.y=180;
			characterBody->transform.translate.z+=dt;

	}
}

void ShopperIdler::Exit()
{
}

void ShopperIdler::Reset()
{
	characterBody->transform.translate = defaultPoint;
	characterBody->transform.rotate.y = defaultCharBodyAngleRotate;
	idling = false;
	walking = true;
	timeIdling = 0;
	//timeWalking = 0;
	distanceMovedInOneDir = 0;
	charBodyAngleRotate = 0;
	characterLeftArm->selfTransform.rotate.x = -5;
	characterRightArm->selfTransform.rotate.x = -5;
	charArmRotate = 30;
	characterLeftLeg->selfTransform.rotate.x = 0;
	characterRightLeg->selfTransform.rotate.x = 0;
	leftArmRotateUp = true;
}

void ShopperIdler::DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg)
{
	characterBody = &TempCharacterBody;
	characterLeftArm = &TempCharacterLeftArm;
	characterRightArm = &TempCharacterRightArm;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
}