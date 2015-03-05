/****************************************************************************/
/*!
\file RobotCashier.h
\author Lim Ting Yang
\par email: limtingyang@hotmail.com
\brief
Struct to define a 3D robot cashier AI
*/
/****************************************************************************/
#pragma once

#include "Shopper.h"
#include "DrawOrder.h"
/****************************************************************************/
/*!
Class RobotCashier:
\brief Defines a 3D robot cashier AI
*/
/****************************************************************************/
class RobotCashier :
	public Shopper
{
private:
	//drawOrder Pointer to character body, arms and legs
	drawOrder* robotBody;
	drawOrder* robotLeftArm;
	drawOrder* robotRightArm;
	//viariables to store rotation of character body
	float robotBodyAngleRotate;
	//viariables to store rotation of character legs
	float robotArmRotate;
	//viariables to check whether the character right leg is rotating upward
	bool rightArmRotateUp;
	float defaultrobotBodyAngleRotate;
public:
	RobotCashier(void);
	~RobotCashier(void);
	
	void Update(const double dt);
	void Reset();
	void CheckDisAndTargetPos(int No);
	void takenItems();
	void returnItems();
	void DrawIsEqualTo(drawOrder& TempRobotBody,drawOrder& TempRobotLeftArm,drawOrder& TempRobotRightArm);
	void RotateChar(RobotCashier& OtherShopper);
	Vector3 GetPos();
};