#include "ShopperWanderer.h"


ShopperWanderer::ShopperWanderer(void)
{
}


ShopperWanderer::~ShopperWanderer(void)
{
}

void ShopperWanderer::Init()
{
}

void ShopperWanderer::Render()
{
}

void ShopperWanderer::Update()
{
	characterBody->transform.translate += Vector3(1,0,0);
}

void ShopperWanderer::Exit()
{
}

void ShopperWanderer::DrawIsEqualTo(drawOrder& TempCharacterBody)
{
	characterBody = &TempCharacterBody;
}