/******************************************************************************/
/*!
\file	Player.cpp
\author Gregory Koh Wen Cong
\par	email: pyroflame11@gmail.com
\brief
Define Player Class functions
*/
/******************************************************************************/
#include "Player.h"



/******************************************************************************/
/*!
\brief
Constructor
*/
/******************************************************************************/
Player::Player(void)
{
}


/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Player::~Player(void)
{
}

/******************************************************************************/
/*!
\brief
Point pointer to some drawOrders
\parm rhs
   Point to drawOrder Character's Left Arm
   Point to drawOrder Character's Right Arm
   Point to drawOrder Character's Body
   Point to drawOrder main
   Point to drawOrder trolley
*/
/******************************************************************************/
void Player::DrawIsEqualTo(drawOrder& TempLeftArm, drawOrder& TempRightArm, drawOrder& TempBody, drawOrder& TempMain, drawOrder& TempTrolley)
{
	leftArm = &TempLeftArm;
	rightArm = &TempRightArm;
	body = &TempBody;
	main = &TempMain;
	trolley = &TempTrolley;
	defaultTrolleyPosition = trolley->GetGlobalPosition();
	defaultTrolleyRotation = trolley->transform.rotate;
}

/******************************************************************************/
/*!
\brief
Reset Trolley to original position and status
*/
/******************************************************************************/
void Player::ResetTrolley()
{
	isHoldingTrolley = false;
	isHoldingItem = false;
	tempNoItemNeedToPay = 0;
	noOfItemInTrolley = 0;
	trolley->SetParentAs(main);
	trolley->transform.rotate.Set(0,0,0);
	trolley->selfTransform.translate.Set(0,0,0);
	trolley->transform.translate.Set(0,0,0);
	trolley->transform.translate = defaultTrolleyPosition;
	trolley->transform.rotate = defaultTrolleyRotation;
}