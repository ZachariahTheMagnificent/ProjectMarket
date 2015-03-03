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
	defaultGlobalPosition = item->GetGlobalPosition();
	defaultTranslation = item->transform.translate;
	defaultRotation = item->transform.rotate;
	taken = false;
}

void ItemInteraction::InteractWithItem(const Vector3& PlayerTargetPos, const Vector3& itemPos)
{
	if(taken == false)
	{
		Range<float> ItemRangeX(defaultGlobalPosition.x - 0.25,defaultGlobalPosition.x + 0.25);
		Range<float> ItemRangeY(defaultGlobalPosition.y,defaultGlobalPosition.y + 2);
		Range<float> ItemRangeZ(defaultGlobalPosition.z - 0.25,defaultGlobalPosition.z + 0.25);

		if(ItemRangeX.IsInRange(PlayerTargetPos.x) && ItemRangeY.IsInRange(PlayerTargetPos.y) && ItemRangeZ.IsInRange(PlayerTargetPos.z))
		{
			item->SetParentAs(trolley);
			item->transform.rotate.Set(0,0,0);
			item->selfTransform.translate.Set(0,0,0);
			item->transform.translate.Set(2,-1,0);
			taken = true;
		}
	}
}