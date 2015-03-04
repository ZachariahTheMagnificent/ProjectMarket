#include "LostChild.h"

LostChild::LostChild(void)
{
	points[0] = Vector3(3,2.9,-27);
	defaultPoint = points[0];

	points[1] = Vector3(2,2.9,-92.8);
	points[2] = Vector3(-0.7,12.9,-95.4);
	points[3] = Vector3(-18.3,12.9,-75);
	points[4] = Vector3(-19,12.9,-10);

	timeIdling = 0;
}

LostChild::~LostChild(void)
{

}

void LostChild::DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg)
{
	characterBody = &TempCharacterBody;
	characterLeftArm = &TempCharacterLeftArm;
	characterRightArm = &TempCharacterRightArm;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
}


void LostChild::SetRandPos(void)
{
	int tempPos = rand() % 5;

	if(tempPos == 0)
	{
		characterBody->transform.rotate.Set(0,180,0);
		characterBody->transform.translate = defaultPoint;
	}

	else if(tempPos == 1)
	{
		characterBody->transform.rotate.Set(0,180,0);
		characterBody->transform.translate = points[1];
	}

	else if(tempPos == 2)
	{
		characterBody->transform.rotate.Set(0,180,0);
		characterBody->transform.translate = points[2];
	}

	else if(tempPos == 3)
	{
		characterBody->transform.rotate.Set(0,90,0);
		characterBody->transform.translate = points[3];
	}

	else
	{
		characterBody->transform.rotate.Set(0,90,0);
		characterBody->transform.translate = points[4];
	}
}

void LostChild::Init()
{

}

void LostChild::Render()
{

}

void LostChild::Exit()
{

}

void LostChild::Update(const double dt)
{
	timeIdling += dt;
	if(timeIdling >= 5 )
	{
		SetRandPos();
		timeIdling = 0;
	}
}

Vector3 LostChild::GetPos()
{
	return characterBody->transform.translate;
}