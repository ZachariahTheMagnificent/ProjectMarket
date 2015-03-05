/******************************************************************************/
/*!
\file	WizardLv2.cpp
\author Gregory Koh Wen Cong
\par	email: pyroflame11@gmail.com
\brief
Define WizardLv2 Class functions
*/
/******************************************************************************/
#include "WizardLv2.h"


/******************************************************************************/
/*!
\brief
Constructor to initialise variables
*/
/******************************************************************************/
WizardLv2::WizardLv2(void)
{
	charArmRotate = 0;
	casting = false;
	castingDone = false;
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
WizardLv2::~WizardLv2(void)
{
}

/******************************************************************************/
/*!
\brief
Update the wizard
\parm rhs
   double delta time
*/
/******************************************************************************/
void WizardLv2::Update(const double dt)
{
	if(casting == true) // Start casting
	{
		if(charArmRotate < 150)
		{
			//Continue casting
			characterLeftArm->selfTransform.rotate.z = 20;
			characterRightArm->selfTransform.rotate.z = -20;
			characterLeftArm->selfTransform.rotate.x -= dt * 20;
			characterRightArm->selfTransform.rotate.x -= dt * 20;
			charArmRotate += dt * 20;
		}
		else
		{
			// Finished casting
			Reset();
			castingDone = true;
		}
	}
}

/******************************************************************************/
/*!
\brief
Update the wizard
\parm rhs
   point to camera
\return
   bool check if interacted
*/
/******************************************************************************/
bool WizardLv2::checkInteract(const Camera& camera)
{
	//Check if player looking at wizard
	if(camera.IsLookingAt(characterBody->GetGlobalPosition(), 20, 10)) 
	{
		//player is looking at the wizard
		return true;
	}
	else
	{
		//player is not looking at the wizard
		return false;
	}
}

/******************************************************************************/
/*!
\brief
Reset the wizard
*/
/******************************************************************************/
void WizardLv2::Reset()
{
	// Reset wizard
	charArmRotate = 0;
	casting = false;
	characterLeftArm->selfTransform.rotate.Set(0,0,0);
	characterRightArm->selfTransform.rotate.Set(0,0,0);
}

/******************************************************************************/
/*!
\brief
Point drawOrder pointers to actual drawOrders
\parm rhs
   point to character body
   point to character left arm
   point to character right arm
   point to character left leg
   point to character right leg
*/
/******************************************************************************/
void WizardLv2::DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg)
{
	// point to actual draworders
	characterBody = &TempCharacterBody;
	characterLeftArm = &TempCharacterLeftArm;
	characterRightArm = &TempCharacterRightArm;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
}