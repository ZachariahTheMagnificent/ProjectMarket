#include "Player.h"


Player::Player(void)
{
}


Player::~Player(void)
{
}

void Player::DrawIsEqualTo(drawOrder& TempLeftArm, drawOrder& TempRightArm, drawOrder& TempBody, drawOrder& TempTrolley)
{
	leftArm = &TempLeftArm;
	rightArm = &TempRightArm;
	body = &TempBody;
	trolley = &TempTrolley;
}