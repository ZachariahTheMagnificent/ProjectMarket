/****************************************************************************/
/*!
\file Father.h
\author Tan Jie Rong
\par email: soupsf@hotmail.com
\brief
Class to update father
*/
/****************************************************************************/
#pragma once

#include "Character.h"
#include "DrawOrder.h"
#include "Camera.h"

/****************************************************************************/
/*!
Class Father:
\brief Defines father and its method
*/
/****************************************************************************/
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
public:
	Father(void);
	~Father(void);
	
	bool interacted;

	void Update(const double dt);
	bool checkInteract(const Camera& camera);
	void Set(Vector3 TempPos);
	void DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg);
};