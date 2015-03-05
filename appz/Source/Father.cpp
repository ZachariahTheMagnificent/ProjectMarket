/****************************************************************************/
/*!
\file Father.cpp
\author Tan Jie Rong
\par email: soupsf@hotmail.com
\brief
update father functions
*/
/****************************************************************************/
#include "Father.h"

/****************************************************************************/
/*!
\brief
default constructor of father 
*/
/****************************************************************************/
Father::Father(void)
{
	interacted = false;
}
/****************************************************************************/
/*!
\brief
default destructor of father 
*/
/****************************************************************************/
Father::~Father(void)
{
}
/****************************************************************************/
/*!
\brief
updating father 
\param dt
		to take in deltatime
*/
/****************************************************************************/
void Father::Update(const double dt)
{
}
/****************************************************************************/
/*!
\brief
to check if father has been interacted
\param camera
		take is camera for 'to look at'
\return
		boolean if interacted
*/
/****************************************************************************/
bool Father::checkInteract(const Camera& camera)
{
	if(camera.IsLookingAt(characterBody->GetGlobalPosition(), 20, 10)) // if player looking at the Father
	{
		return true;
	}
	else
	{
		return false;
	}
}
/****************************************************************************/
/*!
\brief
to take in body parts obj from main
\param darwOrder& (bodypart)
		to pass in draworder
*/
/****************************************************************************/
void Father::DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg)
{
	characterBody = &TempCharacterBody;
	characterLeftArm = &TempCharacterLeftArm;
	characterRightArm = &TempCharacterRightArm;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
}