#pragma once

#include "Character.h"
#include "DrawOrder.h"
#include "Camera.h"

class Father :
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
	Father(void);
	~Father(void);
	
	bool casting;
	bool castingDone;
	
	void Init();
	void Render();
	void Update(const double dt);
	bool checkInteract(const Camera& camera);
	void Exit();
	void Reset();
	void Set(Vector3 TempPos);
	void DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg);
};