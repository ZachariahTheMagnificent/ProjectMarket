#pragma once

#include "DrawOrder.h"
#include "Range.h"
#include "Trolley.h"
#include "Player.h"

class ItemInteraction
{
public:
	ItemInteraction(void);
	~ItemInteraction(void);
	
	void AddItem(drawOrder& TempItem);
	void PlayerIsEqualTo(Player* TempPlayer);
	void TrolleyIsEqualTo(Trolley& TempTrolley);
	void DrawIsEqualTo(drawOrder& TempTrolley, drawOrder& TempPlayerBody);
	void InteractWithItem(const Camera& camera);
	void PutItem(const Camera& camera);
	void PayItem();
	bool EatLollipop(const Camera& camera, const Vector3& lollipopPos);

	std::vector<bool> taken;
	std::vector<bool> atTrolley;

private:
	
	std::vector<Vector3> defaultTranslation;
	std::vector<Rotation> defaultRotation;
	std::vector<Vector3> defaultGlobalPosition;
	std::vector<drawOrder*> defaultParent;

	//drawOrder Pointer to item and trolley
	std::vector<drawOrder*>  item;
	drawOrder* trolley;
	drawOrder* playerBody;
	
	Player* player;
	Trolley* trolleypos;
	
	std::vector<int> posTaking;
	std::vector<bool> paid;
};