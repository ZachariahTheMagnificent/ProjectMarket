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
}