#include "RobotCashier.h"

RobotCashier::RobotCashier(void)
{
	robotBodyAngleRotate = 0;
	robotArmRotate=89;
	rightArmRotateUp=true;
}

RobotCashier::~RobotCashier(void)
{
}

void RobotCashier::Update(const double dt)
{
	if(robotArmRotate >160)
		rightArmRotateUp = false;
	else if(robotArmRotate < 100)
		rightArmRotateUp = true;
	if(rightArmRotateUp == true)
	{
		robotLeftArm->selfTransform.rotate.x -= dt * 30;
		robotArmRotate += dt * 30;
	}
	else
	{
		robotLeftArm->selfTransform.rotate.x +=dt*30;
		robotArmRotate -= dt * 30;
	}
	
}


void RobotCashier::Reset()
{
	robotBodyAngleRotate = 0;
	robotLeftArm->selfTransform.rotate.x = -5;
	robotRightArm->selfTransform.rotate.x = -5;
	robotArmRotate = 30;
	rightArmRotateUp = true;
}

void RobotCashier::DrawIsEqualTo(drawOrder& TempRobotBody, drawOrder& TempRobotLeftArm, drawOrder& TempRobotRightArm)
{
	robotBody = &TempRobotBody;
	robotLeftArm = &TempRobotLeftArm;
	robotRightArm = &TempRobotRightArm;
}