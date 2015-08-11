#pragma once
/****************************************************************************/
/*!
\file VoxelOctree.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
An octree made specifically for voxels
*/
/****************************************************************************/
#include "VoxelLeaf.h"
/****************************************************************************/
/*!
\brief
the default diameter of our voxelOctree
*/
/****************************************************************************/
const int defaultDiameter = pow(2.0, 24.0);
/****************************************************************************/
/*!
Class VoxelOctree:
\brief
An octree made specifically for voxels
*/
/****************************************************************************/
class VoxelOctree
{
public:
	VoxelOctree(int diameter = defaultDiameter, Vector3 displacement = Vector3());
	~VoxelOctree();
	void SetRangeTo(int diameter, Vector3 displacement);
	void AddVoxel(Voxel& voxel);
	Voxel* GetVoxel(const Vector3& position);
	std::vector<Voxel*>& GetVector();
	int GetRadius() const;
private:
	VoxelLeaf mainLeaf;
	std::vector<Voxel*> voxels;
};