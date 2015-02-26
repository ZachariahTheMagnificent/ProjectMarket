#pragma once

#include "Character.h"
#include "DrawOrder.h"

class WizardLv1 :
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
	//viariables to check whether the character arms are rotating upward
	bool ArmsRotateUp;
public:
	WizardLv1(void);
	~WizardLv1(void);
	
	void Init();
	void Render();
	void Update(const double dt);
	void Exit();
	void Reset();
	void Set(Vector3 TempPos);
	void DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg);
};