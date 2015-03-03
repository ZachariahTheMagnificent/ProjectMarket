#include "ItemInteraction.h"

ItemInteraction::ItemInteraction(void)
{
	
}

ItemInteraction::~ItemInteraction(void)
{
}

void ItemInteraction::AddItem(drawOrder& TempItem)
{
	item.push_back(&TempItem);
	defaultTranslation.push_back(item.back()->transform.translate);
	defaultRotation.push_back(item.back()->transform.rotate);
	taken.push_back(false);
	atTrolley.push_back(false);
	posTaking.push_back(-1);
}

void ItemInteraction::PlayerIsEqualTo(Player* TempPlayer)
{
	player = TempPlayer;
}


void ItemInteraction::TrolleyIsEqualTo(Trolley& TempTrolley)
{
	trolleypos = &TempTrolley;
}

void ItemInteraction::DrawIsEqualTo(drawOrder& TempTrolley, drawOrder& TempPlayerBody)
{
	trolley = TempTrolley;
	playerBody = &TempPlayerBody;
}

void ItemInteraction::InteractWithItem(const Vector3& PlayerTargetPos)
{
	for(int i = 0; i < item.size(); ++i)
	{
		if(taken.at(i) == false)
		{
			if(atTrolley.at(i) == true)
			{
				Range<float> ItemRangeX(item.at(i)->GetGlobalPosition().x - 0.25,item.at(i)->GetGlobalPosition().x + 0.25);
				Range<float> ItemRangeY(item.at(i)->GetGlobalPosition().y,item.at(i)->GetGlobalPosition().y + 2);
				Range<float> ItemRangeZ(item.at(i)->GetGlobalPosition().z - 0.25,item.at(i)->GetGlobalPosition().z + 0.25);

				if(ItemRangeX.IsInRange(PlayerTargetPos.x) && ItemRangeY.IsInRange(PlayerTargetPos.y) && ItemRangeZ.IsInRange(PlayerTargetPos.z))
				{
					item.at(i)->SetParentAs(playerBody);
					item.at(i)->transform.rotate.Set(0,0,0);
					item.at(i)->selfTransform.translate.Set(0,0,0);
					item.at(i)->transform.translate.Set(2.5,0.5,0);
					taken.at(i) = true;
					atTrolley.at(i) = false;
					if(posTaking.at(i) == 0)
						trolleypos->SetBoolPos(0,false);
					else if(posTaking.at(i) == 1)
						trolleypos->SetBoolPos(1,false);
					else
						trolleypos->SetBoolPos(2,false);
				}
				if(atTrolley.at(i) == false)
					--player->noOfItemInTrolley;
			}
			else
			{
				Range<float> ItemRangeX(item.at(i)->GetGlobalPosition().x - 0.25,item.at(i)->GetGlobalPosition().x + 0.25);
				Range<float> ItemRangeY(item.at(i)->GetGlobalPosition().y,item.at(i)->GetGlobalPosition().y + 2);
				Range<float> ItemRangeZ(item.at(i)->GetGlobalPosition().z - 0.25,item.at(i)->GetGlobalPosition().z + 0.25);

				if(ItemRangeX.IsInRange(PlayerTargetPos.x) && ItemRangeY.IsInRange(PlayerTargetPos.y) && ItemRangeZ.IsInRange(PlayerTargetPos.z))
				{
					item.at(i)->SetParentAs(playerBody);
					item.at(i)->transform.rotate.Set(0,0,0);
					item.at(i)->selfTransform.translate.Set(0,0,0);
					item.at(i)->transform.translate.Set(2.5,0.5,0);
					taken.at(i) = true;
					atTrolley.at(i) = false;
					if(posTaking.at(i) == 0)
						trolleypos->SetBoolPos(0,false);
					else if(posTaking.at(i) == 1)
						trolleypos->SetBoolPos(1,false);
					else
						trolleypos->SetBoolPos(2,false);
				}
			}
			if(taken.at(i) == true)
				player->isHoldingItem = true;
		}
	}
}

void ItemInteraction::PutItem(const Camera& camera, int noOfItemInTrolley)
{
	for(int i = 0; i < item.size(); ++i)
	{
		if(taken.at(i))
		{

			if(camera.IsLookingAt(trolley.GetGlobalPosition(), 10, 4))
			{
				item.at(i)->SetParentAs(&trolley);
				item.at(i)->transform.rotate.Set(0,0,0);
				item.at(i)->selfTransform.translate.Set(0,0,0);
				if(trolleypos->GetBoolPos(0) == false)
				{
					trolleypos->SetBoolPos(0,true);
					item.at(i)->transform.translate.Set(1.75,-2,-0.5);
					posTaking.at(i) = 0;
				}
				else if(trolleypos->GetBoolPos(1) == false)
				{
					trolleypos->SetBoolPos(1,true);
					item.at(i)->transform.translate.Set(1.75,-2,0.5);
					posTaking.at(i) = 1;
				}
				else
				{
					trolleypos->SetBoolPos(2,true);
					item.at(i)->transform.translate.Set(3.25,-2,0);
					posTaking.at(i) = 2;
				}
				taken.at(i) = false;
				atTrolley.at(i) = true;
			}
			if(taken.at(i) == false)
			{
				player->isHoldingItem = false;
				++player->noOfItemInTrolley;
			}
		}
	}
}