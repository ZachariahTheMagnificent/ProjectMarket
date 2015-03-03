#pragma once
#include "VoxelLeaf.h"

const int defaultDiameter = pow(2.0, 24.0);
class VoxelOctree
{
public:
	VoxelOctree(int diameter = defaultDiameter, Vector3 displacement = Vector3());
	~VoxelOctree();
	void SetRangeTo(int diameter, Vector3 displacement);
	void AddVoxel(Voxel& voxel);
	int GetRadius() const;
private:
	VoxelLeaf mainLeaf;
};