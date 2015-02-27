#pragma once

#include "DrawOrder.h"

class ItemInteraction
{
public:
	ItemInteraction(void);
	~ItemInteraction(void);

	void DrawIsEqualTo(drawOrder& TempItem, drawOrder& TempPlayer);
	void InteractWithItem(const Vector3& PlayerPos);

private:
	
	bool taken;
	Vector3 defaultTranslation;
	Rotation defaultRotation;

	//drawOrder Pointer to item and player
	drawOrder* item;
	drawOrder* player;
};