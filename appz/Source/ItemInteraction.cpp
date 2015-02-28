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
	Range<int> ItemRangeX(item->GetGlobalPosition().x - 10,item->GetGlobalPosition().x + 10);
	Range<int> ItemRangeY(item->GetGlobalPosition().y - 10,item->GetGlobalPosition().y + 10);
	Range<int> ItemRangeZ(item->GetGlobalPosition().z - 10,item->GetGlobalPosition().z + 10);

	if(ItemRangeX.IsInRange(PlayerTargetPos.x) && ItemRangeX.IsInRange(PlayerTargetPos.y) && ItemRangeX.IsInRange(PlayerTargetPos.z))
	{
		if(taken == false)
		{
			item->SetParentAs(trolley);
			item->transform.rotate.Set(0,0,0);
			item->selfTransform.translate.Set(0,0,0);
			item->transform.translate.Set(0,5,0);
			taken = true;
		}
	}
}