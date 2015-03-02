#pragma once

#include "Character.h"
#include "DrawOrder.h"
#include "Range.h"

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
	
	void Init();
	void Render();
	void Update(const double dt);
	bool checkInteract(const Vector3& PlayerTargetPos);
	void Exit();
	void Reset();
	void Set(Vector3 TempPos);
	void DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg);
};