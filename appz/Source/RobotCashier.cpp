
/****************************************************************************/
/*!
\file RobotCashier.cpp
\author Lim Ting Yang
\par email: limtingyang@homail.com
*/
/****************************************************************************/
#include "RobotCashier.h"
/****************************************************************************/
/*!
\brief
constructor(initialise all variables)
*/
/****************************************************************************/
RobotCashier::RobotCashier(void)
{
	robotBodyAngleRotate = 0;
	robotArmRotate=89;
	rightArmRotateUp=true;
}
/****************************************************************************/
/*!
\brief
destructor
*/
/****************************************************************************/
RobotCashier::~RobotCashier(void)
{
}
/****************************************************************************/
/*!
\brief
updating the arm rotation
\param rhs
double delta time

*/
/****************************************************************************/
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
/****************************************************************************/
/*!
\brief
resetting the angles of rotation
*/
/****************************************************************************/

void RobotCashier::Reset()
{
	robotBodyAngleRotate = 0;
	robotLeftArm->selfTransform.rotate.x = -5;
	robotRightArm->selfTransform.rotate.x = -5;
	robotArmRotate = 30;
	rightArmRotateUp = true;
}
/****************************************************************************/
/*!
\brief

\param rhs
point to robot body
point to robot arms
point to robot legs
*/
/****************************************************************************/
void RobotCashier::DrawIsEqualTo(drawOrder& TempRobotBody, drawOrder& TempRobotLeftArm, drawOrder& TempRobotRightArm)
{
	robotBody = &TempRobotBody;
	robotLeftArm = &TempRobotLeftArm;
	robotRightArm = &TempRobotRightArm;
}