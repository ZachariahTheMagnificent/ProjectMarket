#include "ItemInteraction.h"

ItemInteraction::ItemInteraction(void)
{
	taken = false;
}

ItemInteraction::~ItemInteraction(void)
{
}

void ItemInteraction::DrawIsEqualTo(drawOrder& TempItem, drawOrder& TempTrolley)
{
	item = &TempItem;
	trolley = &TempTrolley;
	defaultTranslation = item->transform.translate;
	defaultRotation = item->transform.rotate;
	taken = false;
}

void ItemInteraction::InteractWithItem(const Vector3& PlayerTargetPos)
{
	/*if(item->transform.translate.x - 2 <= PlayerTargetPos.x && item->transform.translate.x + 2 >= PlayerTargetPos.x && item->transform.translate.y - 2 <= PlayerTargetPos.y && item->transform.translate.y + 2 >= PlayerTargetPos.y && item->transform.translate.z - 2 <= PlayerTargetPos.z && item->transform.translate.z + 2 >= PlayerTargetPos.z)
	{
		if(taken == false)
		{*/
			item->SetParentAs(trolley);
			item->transform.rotate.Set(0,0,0);
			item->selfTransform.translate.Set(0,0,0);
			item->transform.translate.Set(0,5,0);
			taken = true;
		/*}
	}*/
}