#include "LostChild.h"

LostChild::LostChild(void)
{
	distanceMovedInOneDir = 0;
	charBodyAngleRotate = 0;
	charArmRotate = 30;
	leftArmRotateUp = true;

	idling = false;
	walking = true;
	timeIdling = 0;
	timeWalking = 0;
}

LostChild::~LostChild(void)
{

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

}

void LostChild::DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg)
{
	characterBody = &TempCharacterBody;
	characterLeftArm = &TempCharacterLeftArm;
	characterRightArm = &TempCharacterRightArm;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
}

void LostChild::SetPosition(int No)
{

}

void LostChild::RotateChar(LostChild& OtherShopper)
{

}

Vector3 LostChild::GetPos()
{
	return characterBody->transform.translate;
}