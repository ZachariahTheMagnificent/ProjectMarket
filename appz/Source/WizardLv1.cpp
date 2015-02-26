#include "WizardLv1.h"


WizardLv1::WizardLv1(void)
{
	charArmRotate = 0;
	ArmsRotateUp = true;
}


WizardLv1::~WizardLv1(void)
{
}

void WizardLv1::Init()
{
}

void WizardLv1::Render()
{
}

void WizardLv1::Update(const double dt)
{
	if(ArmsRotateUp == true)
	{
		if(charArmRotate < 150)
		{
			characterLeftArm->selfTransform.rotate.z = 20;
			characterRightArm->selfTransform.rotate.z = -20;
			characterLeftArm->selfTransform.rotate.x -= dt * 20;
			characterRightArm->selfTransform.rotate.x -= dt * 20;
			charArmRotate += dt * 20;
		}
	}
}

void WizardLv1::Exit()
{
}

void WizardLv1::Reset()
{
	charArmRotate = 0;
	ArmsRotateUp = true;
	characterLeftArm->selfTransform.rotate.Set(0,0,0);
	characterRightArm->selfTransform.rotate.Set(0,0,0);
}

void WizardLv1::DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg)
{
	characterBody = &TempCharacterBody;
	characterLeftArm = &TempCharacterLeftArm;
	characterRightArm = &TempCharacterRightArm;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
}