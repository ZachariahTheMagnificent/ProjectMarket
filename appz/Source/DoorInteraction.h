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

	void InteractWithDoors(void);

private:
	
	//drawOrder Pointer to doors
	drawOrder* OuterDoor1Left;
	drawOrder* OuterDoor1Right;
	drawOrder* OuterDoor2Left;
	drawOrder* OuterDoor2Right;
	drawOrder* InnerDoor1;
	drawOrder* InnerDoor2;
	drawOrder* LiftDoor1Left;
	drawOrder* InnerDoor1Right;
	drawOrder* LiftDoor2Left;
	drawOrder* InnerDoor2Right;

};