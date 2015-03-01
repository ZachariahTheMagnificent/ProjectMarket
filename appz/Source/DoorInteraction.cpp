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
	//OuterDoor1
	Range<int> OuterDoor1RangeX(-7,7);
	Range<int> OuterDoor1RangeY(0,5);
	Range<int> OuterDoor1RangeZ(-18,1.732);

	if(OuterDoor1RangeX.IsInRange(PlayerPos.x) && OuterDoor1RangeY.IsInRange(PlayerPos.y) && OuterDoor1RangeZ.IsInRange(PlayerPos.z))
	{
		if(OuterDoor1Left->transform.translate.x >= -6)
		{
			OuterDoor1Left-> transform.translate.x += -2.5 * dt;
			OuterDoor1Right-> transform.translate.x += 2.5 * dt;
		}
	}

	else
	{
		if(OuterDoor1Left->transform.translate.x < -2)
		{
			OuterDoor1Left-> transform.translate.x += 2.5 * dt;
			OuterDoor1Right-> transform.translate.x += -2.5 * dt;
		}
	}

	//InnderDoor 1
	Range<int> InnerDoor1RangeX(-18,-13);
	Range<int> InnerDoor1RangeY(0,5);
	Range<int> InnerDoor1RangeZ(-28,-10);

	if(InnerDoor1RangeX.IsInRange(PlayerPos.x) && InnerDoor1RangeY.IsInRange(PlayerPos.y) && InnerDoor1RangeZ.IsInRange(PlayerPos.z))
	{
		if(InnerDoor1->transform.translate.x <= -12.5)
		{
			InnerDoor1-> transform.translate.x += 2.5 * dt;
		}
	}

	else
	{
		if(InnerDoor1 -> transform.translate.x > -17.5)
		{
			InnerDoor1-> transform.translate.x += -2.5 * dt;
		}
	}

	//OuterDoor2
	Range<int> OuterDoor2RangeX(-14,-6);
	Range<int> OuterDoor2RangeY(0,5);
	Range<int> OuterDoor2RangeZ(-116,-93.7);

	if(OuterDoor2RangeX.IsInRange(PlayerPos.x) && OuterDoor2RangeY.IsInRange(PlayerPos.y) && OuterDoor2RangeZ.IsInRange(PlayerPos.z))
	{
		if(OuterDoor2Left->transform.translate.x >= -17.2)
		{
			OuterDoor2Left-> transform.translate.x += -2.5 * dt;
			OuterDoor2Right-> transform.translate.x += 2.5 * dt;
		}
	}

	else
	{
		if(OuterDoor2Left->transform.translate.x < -13)
		{
			OuterDoor2Left-> transform.translate.x += 2.5 * dt;
			OuterDoor2Right-> transform.translate.x += -2.5 * dt;
		}
	}
}

void DoorInteraction::InteractWithLifts(const double dt, const Vector3& PlayerPos)	
{
	//LiftDoor1
	Range<int> LiftDoor1RangeX(13,18);
	Range<int> LiftDoor1RangeY(0,5);
	Range<int> LiftDoor1RangeZ(-96,-93);

	if(LiftDoor1RangeX.IsInRange(PlayerPos.x) && LiftDoor1RangeY.IsInRange(PlayerPos.y) && LiftDoor1RangeZ.IsInRange(PlayerPos.z))
	{
		if(LiftDoor1Left->transform.translate.x >= 11)
		{
			LiftDoor1Left-> transform.translate.x += -2.5 * dt;
			LiftDoor1Right-> transform.translate.x += 2.5 * dt;
		}
	}

	else
	{
		if(LiftDoor1Left->transform.translate.x < 14)
		{
			LiftDoor1Left-> transform.translate.x += 2.5 * dt;
			LiftDoor1Right-> transform.translate.x += -2.5 * dt;
		}
	}
}