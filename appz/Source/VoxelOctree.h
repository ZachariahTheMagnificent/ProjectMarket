#pragma once
#include "VoxelLeaf.h"

class VoxelOctree
{
public:
	VoxelOctree();
	~VoxelOctree();
	void SetRangeTo(int diameter, Vector3 displacement);
	void AddVoxel(Voxel& voxel);
	int GetRadius() const;
private:
	VoxelLeaf mainLeaf;
};