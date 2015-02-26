#pragma once
#include "DrawOrder.h"
#include "Contacts.h"
#include "VoxelLeaf.h"

class VoxelOctree
{
public:
	VoxelOctree();
	~VoxelOctree();
	void AddVoxels(drawOrder& draw);
	void AddVoxel(Voxel& voxel);
	void SolveCollisionFor(drawOrder& draw);
	//void SetUpFor(drawOrder* draw1, drawOrder* draw2, const double deltaTime);
	std::vector<Contact> GetAllContacts();
private:
	VoxelLeaf mainLeaf;
};