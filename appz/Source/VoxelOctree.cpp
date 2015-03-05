#include "VoxelOctree.h"
#include "timer.h"

VoxelOctree::VoxelOctree(int diameter, Vector3 displacement)
{
}

VoxelOctree::~VoxelOctree()
{
}

void VoxelOctree::SetRangeTo(int diameter, Vector3 displacement)
{
	Range<int> fullRangeX(1,1);
	Range<int> fullRangeY(1,1);
	Range<int> fullRangeZ(1,1);
	while(fullRangeX.Length() <= diameter)
	{
		int newEnd = fullRangeX.End() * 2;
		fullRangeX.End(newEnd);
		fullRangeY.End(newEnd);
		fullRangeZ.End(newEnd);
	}
	fullRangeX.Set(fullRangeX.Start() + displacement.x - 1, fullRangeX.End() + displacement.x - 1);
	fullRangeY.Set(fullRangeY.Start() + displacement.y - 1, fullRangeY.End() + displacement.y - 1);
	fullRangeZ.Set(fullRangeZ.Start() + displacement.z - 1, fullRangeZ.End() + displacement.z - 1);
	mainLeaf.SetRangeTo(fullRangeX, fullRangeY, fullRangeZ);
}

int VoxelOctree::GetRadius() const
{
	return mainLeaf.GetRadius();
}

void VoxelOctree::AddVoxel(Voxel& voxel)
{
	mainLeaf.AddVoxel(voxel);
	voxels.push_back(mainLeaf.GetVoxel(voxel.GetPosition()));
	if(voxels.back() == NULL)
	{
		throw;
	}
}

std::vector<Voxel*>& VoxelOctree::GetVector()
{
	return voxels;
}

Voxel* VoxelOctree::GetVoxel(const Vector3& position)
{
	if(!mainLeaf.GetRangeX().IsInRange(position.x) || !mainLeaf.GetRangeY().IsInRange(position.y) || !mainLeaf.GetRangeZ().IsInRange(position.z))
	{
		return NULL;
	}
	return mainLeaf.GetVoxel(position);
}

bool VoxelOctree::DoCollisionWith(VoxelOctree* otherTree)
{
	return false;
}