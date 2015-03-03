#include "WizardLv2.h"


WizardLv2::WizardLv2(void)
{
	charArmRotate = 0;
	casting = false;
	castingDone = false;
}


WizardLv2::~WizardLv2(void)
{
}

void WizardLv2::Init()
{
}

void WizardLv2::Render()
{
}

void WizardLv2::Update(const double dt)
{
	if(casting == true)
	{
		if(charArmRotate < 150)
		{
			characterLeftArm->selfTransform.rotate.z = 20;
			characterRightArm->selfTransform.rotate.z = -20;
			characterLeftArm->selfTransform.rotate.x -= dt * 20;
			characterRightArm->selfTransform.rotate.x -= dt * 20;
			charArmRotate += dt * 20;
		}
		else
		{
			Reset();
			castingDone = true;
		}
	}
}

bool WizardLv2::checkInteract(const Camera& camera)
{
	
	if(camera.IsLookingAt(characterBody->GetGlobalPosition(), 20, 10)) // if player looking at the wizard
	{
		return true;
	}
	else
	{
		return false;
	}
}

void WizardLv2::Exit()
{
}

void WizardLv2::Reset()
{
	charArmRotate = 0;
	casting = false;
	characterLeftArm->selfTransform.rotate.Set(0,0,0);
	characterRightArm->selfTransform.rotate.Set(0,0,0);
}

void WizardLv2::DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg)
{
	characterBody = &TempCharacterBody;
	characterLeftArm = &TempCharacterLeftArm;
	characterRightArm = &TempCharacterRightArm;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
}