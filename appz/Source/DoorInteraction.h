#pragma once

#include "Mesh.h"
#include "Mtx44.h"
#include "DrawOrder.h"
#include "MatrixStack.h"
#include <vector>
#include "GlobalList.h"
#include "Range.h"

class DoorInteraction
{
public:
	DoorInteraction(void);
	~DoorInteraction(void);

	void DrawIsEqualTo(drawOrder& TempOuterDoor1Left, drawOrder& TempOuterDoor1Right, drawOrder& TempOuterDoor2Left, drawOrder& TempOuterDoor2Right, drawOrder& TempInnerDoor1, drawOrder& TempInnerDoor2, drawOrder& TempLiftDoor1Left, drawOrder& TempLiftDoor1Right, drawOrder& TempLiftDoor2Left, drawOrder& TempLiftDoor2Right);
	void CheckWithinRange(Vector3 TempPosition);
	void InteractWithDoors(const double dt, const Vector3& PlayerPos);
	void InteractWithLifts(const double dt, Vector3& PlayerPos);
	void TeleportWithLifts(const double dt, Vector3& PlayerPos);
	void InteractWithTravelator(const double dt, Vector3& PlayerPos);

	bool GetTravelatorInRange (void);

private:
	
	bool LiftDoor1isOpen;
	bool LiftDoor2isOpen;
	bool TravelatorIsInrange;
	//drawOrder Pointer to doors
	drawOrder* OuterDoor1Left;
	drawOrder* OuterDoor1Right;
	drawOrder* OuterDoor2Left;
	drawOrder* OuterDoor2Right;
	drawOrder* InnerDoor1;
	drawOrder* InnerDoor2;
	drawOrder* LiftDoor1Left;
	drawOrder* LiftDoor1Right;
	drawOrder* LiftDoor2Left;
	drawOrder* LiftDoor2Right;

};