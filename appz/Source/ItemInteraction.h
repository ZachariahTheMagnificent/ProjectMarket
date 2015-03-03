#pragma once

#include "DrawOrder.h"
#include "Range.h"

class ItemInteraction
{
public:
	ItemInteraction(void);
	~ItemInteraction(void);

	void DrawIsEqualTo(drawOrder& TempItem, drawOrder& TempTrolley);
	void InteractWithItem(const Vector3& PlayerPos, const Vector3& itemPos);

	Vector3 defaultGlobalPosition;

private:
	
	bool taken;
	Vector3 defaultTranslation;
	Rotation defaultRotation;

	//drawOrder Pointer to item and trolley
	drawOrder* item;
	drawOrder* trolley;
};