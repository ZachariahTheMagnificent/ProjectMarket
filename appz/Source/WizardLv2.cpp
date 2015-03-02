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

bool WizardLv2::checkInteract(const Vector3& PlayerTargetPos)
{
	
	Range<int> WizardRangeX(characterBody->GetGlobalPosition().x - 5,characterBody->GetGlobalPosition().x + 5);
	Range<int> WizardRangeY(characterBody->GetGlobalPosition().y - 5,characterBody->GetGlobalPosition().y + 5);
	Range<int> WizardRangeZ(characterBody->GetGlobalPosition().z - 5,characterBody->GetGlobalPosition().z + 5);

	if(WizardRangeX.IsInRange(PlayerTargetPos.x) && WizardRangeY.IsInRange(PlayerTargetPos.y) && WizardRangeZ.IsInRange(PlayerTargetPos.z))
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