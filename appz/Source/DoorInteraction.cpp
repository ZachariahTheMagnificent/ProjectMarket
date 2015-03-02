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
			OuterDoor1Left-> transform.translate.x += -3 * dt;
			OuterDoor1Right-> transform.translate.x += 3 * dt;
		}
	}

	else
	{
		if(OuterDoor1Left->transform.translate.x < -2)
		{
			OuterDoor1Left-> transform.translate.x += 3 * dt;
			OuterDoor1Right-> transform.translate.x += -3 * dt;
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
			InnerDoor1-> transform.translate.x += -3 * dt;
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
			OuterDoor2Left-> transform.translate.x += -3 * dt;
			OuterDoor2Right-> transform.translate.x += 3 * dt;
		}
	}

	else
	{
		if(OuterDoor2Left->transform.translate.x < -13)
		{
			OuterDoor2Left-> transform.translate.x += 3 * dt;
			OuterDoor2Right-> transform.translate.x += -3 * dt;
		}
	}
}

void DoorInteraction::InteractWithLifts(const double dt, Vector3& PlayerPos)	
{
	//LiftDoor1 > door interaction
	Range<int> LiftDoor1and2RangeX(13,18);
	Range<int> LiftDoor1RangeY(0,5);
	Range<int> LiftDoor2RangeY(10,15);
	Range<int> LiftDoor1and2RangeZ(-96,-93);

	if(LiftDoor1and2RangeX.IsInRange(PlayerPos.x) && LiftDoor1RangeY.IsInRange(PlayerPos.y) && LiftDoor1and2RangeZ.IsInRange(PlayerPos.z))
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

		if(LiftDoor1and2RangeX.IsInRange(PlayerPos.x) && LiftDoor2RangeY.IsInRange(PlayerPos.y) && LiftDoor1and2RangeZ.IsInRange(PlayerPos.z))
	{
		if(LiftDoor2Left->transform.translate.x >= 11)
		{
			LiftDoor2Left-> transform.translate.x += -2.5 * dt;
			LiftDoor2Right-> transform.translate.x += 2.5 * dt;
		}
	}

	else
	{
		if(LiftDoor2Left->transform.translate.x < 14)
		{
			LiftDoor2Left-> transform.translate.x += 2.5 * dt;
			LiftDoor2Right-> transform.translate.x += -2.5 * dt;
		}
	}
}

void DoorInteraction::TeleportWithLifts(const double dt, Vector3& PlayerPos)	
{
	//Lift > Lift translation
	Range<int> Lift0and1RangeX(12,18);
	Range<int> Lift0RangeY(0,5);
	Range<int> Lift1RangeY(10,15);
	Range<int> Lift0and1RangeZ(-105,-100);

	if(Lift0and1RangeX.IsInRange(PlayerPos.x) && Lift0RangeY.IsInRange(PlayerPos.y) && Lift0and1RangeZ.IsInRange(PlayerPos.z))
	{
		PlayerPos.y = 10.902;
	}	

	else if(Lift0and1RangeX.IsInRange(PlayerPos.x) && Lift1RangeY.IsInRange(PlayerPos.y) && Lift0and1RangeZ.IsInRange(PlayerPos.z))
	{
		PlayerPos.y = 0.931;
	}	
}

void DoorInteraction::InteractWithTravelator(const double dt, Vector3& PlayerPos)	
{
	Range<int> TravelatorRangeX(-14,10.716);
	Range<int> TravelatorRangeY(0,14);
	Range<int> TravelatorLeftUpRangeZ(-21.638,-20.788);
	Range<int> TravelatorRightDownRangeZ(-24.337,-23.234);

	if(TravelatorRangeX.IsInRange(PlayerPos.x) && TravelatorRangeY.IsInRange(PlayerPos.y) && TravelatorRightDownRangeZ.IsInRange(PlayerPos.z))
	{
		PlayerPos.x += 2.5 * dt;
		PlayerPos.y += -1 * dt;
	}

	if(TravelatorRangeX.IsInRange(PlayerPos.x) && TravelatorRangeY.IsInRange(PlayerPos.y) && TravelatorLeftUpRangeZ.IsInRange(PlayerPos.z))
	{
		PlayerPos.x += -2.5 * dt;
		PlayerPos.y += 1 * dt;
	}
}
