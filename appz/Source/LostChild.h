#pragma once

#include "Character.h"
#include "DrawOrder.h"
#include "Range.h"

class LostChild :
	public Character
{

	public:
	LostChild(void);
	~LostChild(void);
	
	void Init();
	void Render();
	void SetPosition(int No);
	void Update(const double dt);
	void Exit();
	void Reset();
	void DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg);
	Vector3 GetPos();

	private:
	//drawOrder Pointer to character body, arms and legs
	drawOrder* characterBody;
	drawOrder* characterLeftArm;
	drawOrder* characterRightArm;
	drawOrder* characterLeftLeg;
	drawOrder* characterRightLeg;
	//Vector3 to store position checkpoint
	Vector3 points[5];
	//Default position
	Vector3 defaultPoint;
};