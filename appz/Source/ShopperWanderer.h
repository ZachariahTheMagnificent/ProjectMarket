#pragma once

#include "Shopper.h"
#include "DrawOrder.h"

class ShopperWanderer :
	public Shopper
{
public:
	ShopperWanderer(void);
	~ShopperWanderer(void);
	
	void Init();
	void Render();
	void Update();
	void Exit();
	void DrawIsEqualTo(drawOrder& TempCharacterBody);

	drawOrder* characterBody;
};