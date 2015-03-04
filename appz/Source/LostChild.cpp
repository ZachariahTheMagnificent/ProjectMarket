#include "LostChild.h"

LostChild::LostChild(void)
{
	points[0] = Vector3(3,2.9,-27);
	defaultPoint = points[0];

	points[1] = Vector3(2,2.9,-92.8);
	points[2] = Vector3(-0.7,12.9,-95.4);
	points[3] = Vector3(-18.3,12.9,-75);
	points[4] = Vector3(-19,12.9,-10);

	timeIdling = 0;
	ChildisTaken = false;
}

LostChild::~LostChild(void)
{

}

void LostChild::DrawIsEqualTo(drawOrder& TempMain, drawOrder& TempPlayerBody, drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg)
{
	main = &TempMain;
	playerBody = &TempPlayerBody;
	characterBody = &TempCharacterBody;
	characterLeftArm = &TempCharacterLeftArm;
	characterRightArm = &TempCharacterRightArm;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
}


void LostChild::SetRandPos(void)
{
	int tempPos = rand() % 5;

	if(tempPos == 0)
	{
		characterBody->transform.rotate.Set(0,0,0);
		characterBody->transform.rotate.Set(0,180,0);
		characterBody->transform.translate = defaultPoint;
	}

	else if(tempPos == 1)
	{
		characterBody->transform.rotate.Set(0,0,0);
		characterBody->transform.rotate.Set(0,180,0);
		characterBody->transform.translate = points[1];
	}

	else if(tempPos == 2)
	{
		characterBody->transform.rotate.Set(0,0,0);
		characterBody->transform.rotate.Set(0,180,0);
		characterBody->transform.translate = points[2];
	}

	else if(tempPos == 3)
	{
		characterBody->transform.rotate.Set(0,0,0);
		characterBody->transform.rotate.Set(0,90,0);
		characterBody->transform.translate = points[3];
	}

	else
	{
		characterBody->transform.rotate.Set(0,0,0);
		characterBody->transform.rotate.Set(0,90,0);
		characterBody->transform.translate = points[4];
	}
}

void LostChild::Init()
{

}

void LostChild::Render()
{

}

void LostChild::Exit()
{

}

void LostChild::Update(const double dt)
{
	timeIdling += dt;
	if(timeIdling >= 5 )
	{
		SetRandPos();
		timeIdling = 0;
	}
}

void LostChild::PlayerIsEqualTo(Player* TempPlayer)
{
	player = TempPlayer;
}

void LostChild::PickUpChild(const Camera& camera)
{
	if(camera.IsLookingAt(characterBody->GetGlobalPosition(), 50, 15)) // if player looking at the child
	{
		// player take item
		characterBody->SetParentAs(playerBody);
		characterBody->transform.rotate.Set(0,-90,0);
		characterBody->transform.translate.Set(0,0,0);
		characterBody->transform.translate.Set(2.5,0.5,0);
		
		ChildisTaken = true; // now being taken by player
	}

	if(ChildisTaken == true)
	{
		player->isHoldingChild = true;
	}
}

void LostChild::Reset()
{
	timeIdling = 0;
	ChildisTaken = false;
	player->isHoldingChild = false;
	characterBody->SetParentAs(main);
	characterBody->transform.rotate.Set(0,180,0);
	characterBody->transform.translate = defaultPoint;
}