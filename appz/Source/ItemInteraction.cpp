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
	defaultParent.push_back(item.back()->GetParent());
	defaultTranslation.push_back(item.back()->transform.translate);
	defaultRotation.push_back(item.back()->transform.rotate);
	defaultGlobalPosition.push_back(item.back()->GetGlobalPosition());
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
	trolley = &TempTrolley;
	playerBody = &TempPlayerBody;
}

void ItemInteraction::InteractWithItem(const Camera& camera)
{
	for(int i = 0; i < item.size(); ++i)
	{
		if(taken[i] == false) // if not being taken by player
		{
			if(atTrolley[i] == true) // if item at trolley
			{
				if(camera.IsLookingAt(item[i]->GetGlobalPosition(), 5, 5)) // if player looking at the item
				{
					// player take item
					item[i]->SetParentAs(playerBody);
					item[i]->transform.rotate.Set(0,0,0);
					item[i]->selfTransform.translate.Set(0,0,0);
					item[i]->transform.translate.Set(2.5,0.5,0);
					taken[i] = true; // now being taken by player
					atTrolley[i] = false; // no longer at trolley
					--player->noOfItemInTrolley; // number of item in trolley decreases
					// check which position the item is taking previously and make that position available to other items
					if(posTaking[i] == 0)
						trolleypos->SetBoolPos(0,false);
					else if(posTaking[i] == 1)
						trolleypos->SetBoolPos(1,false);
					else
						trolleypos->SetBoolPos(2,false);
				}
			}
			else // else item at cabinet
			{
				if(camera.IsLookingAt(item[i]->GetGlobalPosition(), 5, 5)) // if player looking at the item
				{
					// player take item
					item[i]->SetParentAs(playerBody);
					item[i]->transform.rotate.Set(0,0,0);
					item[i]->selfTransform.translate.Set(0,0,0);
					item[i]->transform.translate.Set(2.5,0.5,0);
					taken[i] = true; // now being taken by player
				}
			}
			if(taken[i] == true)
			{
				player->isHoldingItem = true;
				break;
			}
		}
	}
}

void ItemInteraction::PutItem(const Camera& camera)
{
	for(int i = 0; i < item.size(); ++i)
	{
		if(taken[i]) // if item[i] is being taken, player holding
		{

			if(player->noOfItemInTrolley < 3 && camera.IsLookingAt(trolley->GetGlobalPosition(), 20, 5)) // if player looking at trolley
			{
				// place item at trolley
				item[i]->SetParentAs(trolley);
				item[i]->transform.rotate.Set(0,0,0);
				item[i]->selfTransform.translate.Set(0,0,0);
				if(trolleypos->GetBoolPos(0) == false) // check if position 0 at trolley is taken
				{
					// place item at position 0
					trolleypos->SetBoolPos(0,true);
					item[i]->transform.translate.Set(1.75,-2,-0.5);
					posTaking[i] = 0;
				}
				else if(trolleypos->GetBoolPos(1) == false)// check if position 1 at trolley is taken
				{
					// place item at position 1
					trolleypos->SetBoolPos(1,true);
					item[i]->transform.translate.Set(1.75,-2,0.5);
					posTaking[i] = 1;
				}
				else // else take last position
				{
					// place item at position 2
					trolleypos->SetBoolPos(2,true);
					item[i]->transform.translate.Set(3.25,-2,0);
					posTaking[i] = 2;
				}
				taken[i] = false; // taken by player became false
				player->isHoldingItem = false; // player not holding item
				atTrolley[i] = true; // at trolley became true
				++player->noOfItemInTrolley; // number of item in trolley increases
			}
			else if(camera.IsLookingAt(defaultGlobalPosition[i], 20, 5)) // if player looking at the item original position
			{
				// place item at back to 
				item[i]->SetParentAs(defaultParent[i]);
				item[i]->transform.translate = defaultTranslation[i];
				item[i]->transform.rotate = defaultRotation[i];
				taken[i] = false; // taken by player became false
				player->isHoldingItem = false; // player not holding item
			}
		}
	}
}

void ItemInteraction::PayItem()
{
}

bool ItemInteraction::EatLollipop(const Camera& camera, const Vector3& lollipopPos)
{
	if(camera.IsLookingAt(lollipopPos, 40, 5))
	{
		return true;
	}
	return false;
}