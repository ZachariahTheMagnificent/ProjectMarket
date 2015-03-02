#include "VoxelOctree.h"
#include "timer.h"

VoxelOctree::VoxelOctree()
{
}

VoxelOctree::~VoxelOctree()
{
}

void VoxelOctree::SetRangeTo(int diameter, Vector3 displacement)
{
	Range<int> fullRangeX(0,2);
	Range<int> fullRangeY(0,2);
	Range<int> fullRangeZ(0,2);
	while(fullRangeX.Length() <= diameter)
	{
		int newEnd = fullRangeX.End() * 2;
		fullRangeX.End(newEnd);
		fullRangeY.End(newEnd);
		fullRangeZ.End(newEnd);
	}
	fullRangeX.Set(fullRangeX.Start() + displacement.x, fullRangeX.End() + displacement.x);
	fullRangeY.Set(fullRangeY.Start() + displacement.y, fullRangeY.End() + displacement.y);
	fullRangeZ.Set(fullRangeZ.Start() + displacement.z, fullRangeZ.End() + displacement.z);
}

int VoxelOctree::GetRadius() const
{
	return mainLeaf.GetRadius();
}

void VoxelOctree::AddVoxel(Voxel& voxel)
{
	mainLeaf.AddVoxel(voxel);
}