#include "Father.h"


Father::Father(void)
{
	interacted = false;
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
}

bool Father::checkInteract(const Camera& camera)
{
	if(camera.IsLookingAt(characterBody->GetGlobalPosition(), 20, 10)) // if player looking at the Father
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
}

void Father::DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg)
{
	characterBody = &TempCharacterBody;
	characterLeftArm = &TempCharacterLeftArm;
	characterRightArm = &TempCharacterRightArm;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
}