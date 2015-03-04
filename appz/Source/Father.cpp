#include "Father.h"


Father::Father(void)
{
	charArmRotate = 0;
	casting = false;
	castingDone = false;
}


Father::~Father(void)
{
}

void Father::Init()
{
}

void Father::Render()
{
}

void Father::Update(const double dt)
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

bool Father::checkInteract(const Camera& camera)
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

void Father::Exit()
{
}

void Father::Reset()
{
	charArmRotate = 0;
	casting = false;
	characterLeftArm->selfTransform.rotate.Set(0,0,0);
	characterRightArm->selfTransform.rotate.Set(0,0,0);
}

void Father::DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg)
{
	characterBody = &TempCharacterBody;
	characterLeftArm = &TempCharacterLeftArm;
	characterRightArm = &TempCharacterRightArm;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
}