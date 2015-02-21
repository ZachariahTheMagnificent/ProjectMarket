#pragma once
#include "DrawOrder.h"
#include "Contacts.h"

class VoxelOctree
{
public:
	VoxelOctree();
	~VoxelOctree();
	void SetUpFor(drawOrder* draw1, drawOrder* draw2);
	std::vector<Contact> GetAllContacts();
private:
	drawOrder* biggerDraw;
	drawOrder* smallerDraw;
	std::vector<Voxel*> tree;
	Vector3 displacement;
};