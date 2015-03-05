/******************************************************************************/
/*!
\file	WizardLv2.h
\author Gregory Koh Wen Cong
\par	email: pyroflame11@gmail.com
\brief
Class to store WizardLv2
*/
/******************************************************************************/
#pragma once

#include "Character.h"
#include "DrawOrder.h"
#include "Camera.h"

/******************************************************************************/
/*!
		Class WizardLv2:
\brief	Defines a WizardLv2 class
*/
/******************************************************************************/
class WizardLv2 :
	public Character
{
private:
	//drawOrder Pointer to character body, arms and legs
	drawOrder* characterBody;
	drawOrder* characterLeftArm;
	drawOrder* characterRightArm;
	drawOrder* characterLeftLeg;
	drawOrder* characterRightLeg;
	//viariables to store rotation of character arm
	float charArmRotate;
public:
	WizardLv2(void);
	~WizardLv2(void);
	
	bool casting;
	bool castingDone;
	
	void Update(const double dt);
	bool checkInteract(const Camera& camera);
	void Reset();
	void Set(Vector3 TempPos);
	void DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg);
};