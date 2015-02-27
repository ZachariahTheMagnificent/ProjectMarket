#include "DoorInteraction.h"

DoorInteraction::DoorInteraction(void)
{
	 OuterDoor1isOpen = false;
	 OuterDoor2isOpen = false;
	 InnerDoor1isOpen = false;
	 InnerDoor2isOpen = false;
	 LiftDoor1isOpen = false;
	 LiftDoor2isOpen = false;
}

DoorInteraction::~DoorInteraction(void)
{
}

void DoorInteraction::DrawIsEqualTo(drawOrder& TempOuterDoor1Left, drawOrder& TempOuterDoor1Right, drawOrder& TempOuterDoor2Left, drawOrder& TempOuterDoor2Right, drawOrder& TempInnerDoor1, drawOrder& TempInnerDoor2, drawOrder& TempLiftDoor1Left, drawOrder& TempLiftDoor1Right, drawOrder& TempLiftDoor2Left, drawOrder& TempLiftDoor2Right)
{
	OuterDoor1Left = &TempOuterDoor1Left;
    OuterDoor1Right = &TempOuterDoor1Right;
	OuterDoor2Left = &TempOuterDoor2Left;
	OuterDoor2Right = &TempOuterDoor2Right;
	InnerDoor1 = &TempInnerDoor1;
	InnerDoor2 = &TempInnerDoor2;
	LiftDoor1Left = &TempLiftDoor1Left;
	LiftDoor1Right = &TempLiftDoor1Right;
	LiftDoor2Left = &TempLiftDoor2Left;
	LiftDoor2Right = &TempLiftDoor2Right;
}

void DoorInteraction::InteractWithDoors(const double dt, const Vector3& PlayerPos)
{
	
	Range<int> OuterDoor1RangeX(-50,50);
	Range<int> OuterDoor1RangeY(-300,300);
	Range<int> OuterDoor1RangeZ(-15,15);

	if(OuterDoor1RangeX.IsInRange(PlayerPos.x) && OuterDoor1RangeY.IsInRange(PlayerPos.y) && OuterDoor1RangeZ.IsInRange(PlayerPos.z))
	{
		//if(OuterDoor1Left->transform.translate.x <= 10)
		//{
			OuterDoor1Left-> transform.translate.x += -2 * dt;
		//}
	}

	else
	{

	}
}