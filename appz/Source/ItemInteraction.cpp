#include "ItemInteraction.h"

ItemInteraction::ItemInteraction(void)
{
	taken = false;
}

ItemInteraction::~ItemInteraction(void)
{
}

void ItemInteraction::DrawIsEqualTo(drawOrder& TempItem, drawOrder& TempPlayer)
{
	item = &TempItem;
	player = &TempPlayer;
	defaultTranslation = item->transform.translate;
	defaultRotation = item->transform.rotate;
	taken = false;
}

void ItemInteraction::InteractWithItem(const Vector3& PlayerTargetPos)
{
	if(item->transform.translate.x - 100 <= PlayerTargetPos.x && item->transform.translate.x + 2 >= PlayerTargetPos.x && item->transform.translate.y - 2 <= PlayerTargetPos.y && item->transform.translate.y + 2 >= PlayerTargetPos.y && item->transform.translate.z - 2 <= PlayerTargetPos.z && item->transform.translate.z + 2 >= PlayerTargetPos.z)
	{
		if(taken == false)
		{
			item->SetParentAs(player);
			item->selfTransform.translate = Vector3(0,10,0);
			taken = true;
		}
	}
}