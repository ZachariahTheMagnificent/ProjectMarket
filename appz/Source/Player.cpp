#include "Player.h"


Player::Player(void)
{
}


Player::~Player(void)
{
}

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