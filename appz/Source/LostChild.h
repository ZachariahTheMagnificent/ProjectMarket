/****************************************************************************/
/*!
\file LostChild.h
\author Tan Jie Rong
\par email: soupsf@hotmail.com
\brief
Class to define the lostchild
*/
/****************************************************************************/
#pragma once

#include "Character.h"
#include "DrawOrder.h"
#include "Range.h"
#include "Camera.h"
#include "Player.h"
/****************************************************************************/
/*!
Class LostChild:
\brief Defines lostchild and its method
*/
/****************************************************************************/
class LostChild :
	public Character
{

	public:
	LostChild(void);
	~LostChild(void);
	
	void Update(const double dt);
	void Reset();
	void DrawIsEqualTo(drawOrder& TempMain, drawOrder& TempPlayerBody, drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg);
	void PlayerIsEqualTo(Player* TempPlayer);
	void PickUpChild(const Camera& camera);
	//Set random position
	void SetRandPos(void);

	private:
	//drawOrder Pointer to character body, arms and legs
	drawOrder* main;
	drawOrder* playerBody;
	drawOrder* characterBody;
	drawOrder* characterLeftArm;
	drawOrder* characterRightArm;
	drawOrder* characterLeftLeg;
	drawOrder* characterRightLeg;

	Player* player;
	//Vector3 to store position checkpoint
	Vector3 points[5];
	//Default position
	Vector3 defaultPoint;
	//check time
	float timeIdling;
	//check is child is taken
	bool ChildisTaken;
	

};