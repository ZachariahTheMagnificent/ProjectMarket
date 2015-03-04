#include "LostChild.h"

LostChild::LostChild(void)
{
	points[0] = (3,2.9,-27);
	points[1] = (0,0,0);
	points[2] = (0,0,0);
	points[3] = (0,0,0);
	points[4] = (0,0,0);
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

Vector3 LostChild::GetPos()
{
	return characterBody->transform.translate;
}