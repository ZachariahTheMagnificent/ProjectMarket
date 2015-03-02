#include "RobotCashier.h"

RobotCashier::RobotCashier(void)
{
	robotBodyAngleRotate = 0;
	robotArmRotate=180;
	rightArmRotateUp=true;
}

RobotCashier::~RobotCashier(void)
{
}

void RobotCashier::Init()
{
}

void RobotCashier::Render()
{
}

void RobotCashier::Update(const double dt)
{
	if(robotArmRotate >90)
			rightArmRotateUp = false;
		else if(robotArmRotate < 45)
			rightArmRotateUp = true;
		if(rightArmRotateUp == true)
		{
			robotLeftArm->selfTransform.rotate.x += dt * 80;

			robotArmRotate += dt * 80;
		}
		else
		{
			robotLeftArm->selfTransform.rotate.x -= dt * 80;
			robotArmRotate -= dt * 80;
		}
}
void RobotCashier::Exit()
{

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