#pragma once
/****************************************************************************/
/*!
\file VoxelLeaf.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A node in the voxelOctree
*/
/****************************************************************************/
#include <iostream>
#include <vector>
#include "Voxel.h"
#include "Range.h"
/****************************************************************************/
/*!
\brief
the default ranges of our leaf
*/
/****************************************************************************/
const int VoxelLeafMin = INT_MIN/16;
const int VoxelLeafMax = INT_MAX/16;
/****************************************************************************/
/*!
Class VoxelLeaf:
\brief
A node in the voxelOctree
*/
/****************************************************************************/
class VoxelLeaf
{
public:
	VoxelLeaf(const Range<int> rangeX = Range<int>(VoxelLeafMin, VoxelLeafMax), const Range<int> rangeY = Range<int>(VoxelLeafMin, VoxelLeafMax), const Range<int> rangeZ = Range<int>(VoxelLeafMin, VoxelLeafMax), VoxelLeaf *const parent = NULL);
	~VoxelLeaf();
	void SetRangeTo(const Range<int> rangeX, const Range<int> rangeY, const Range<int> rangeZ);
	const Range<int>& GetRangeX() const;
	const Range<int>& GetRangeY() const;
	const Range<int>& GetRangeZ() const;
	void AddVoxel(Voxel& voxel);
	void Subdivide();
	bool HasAlreadySubdivided() const;
	Voxel* GetVoxel(const Vector3& position);
	bool IsEmpty() const;
	int GetRadius() const;
private:
	unsigned GetIndex(const Vector3& position);
	Range<int> lowerRangeX;
	Range<int> upperRangeX;
	Range<int> fullRangeX;
	Range<int> lowerRangeY;
	Range<int> upperRangeY;
	Range<int> fullRangeY;
	Range<int> lowerRangeZ;
	Range<int> upperRangeZ;
	Range<int> fullRangeZ;
	std::vector<VoxelLeaf*> leaves;
	VoxelLeaf* parent;
	std::vector<Voxel> voxels;
};