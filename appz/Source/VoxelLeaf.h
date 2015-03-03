#pragma once
#include <iostream>
#include <vector>
#include "Voxel.h"
#include "Range.h"

const int VoxelLeafMin = INT_MIN/16;
const int VoxelLeafMax = INT_MAX/16;
class VoxelLeaf
{
public:
	VoxelLeaf(const Range<int> rangeX = Range<int>(VoxelLeafMin, VoxelLeafMax), const Range<int> rangeY = Range<int>(VoxelLeafMin, VoxelLeafMax), const Range<int> rangeZ = Range<int>(VoxelLeafMin, VoxelLeafMax), VoxelLeaf *const parent = NULL);
	~VoxelLeaf();
	void SetRangeTo(const Range<int> rangeX, const Range<int> rangeY, const Range<int> rangeZ);
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