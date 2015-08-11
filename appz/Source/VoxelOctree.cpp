#include "VoxelOctree.h"
#include "timer.h"
/****************************************************************************/
/*!
\file VoxelOctree.cpp
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
An octree made specifically for voxels
*/
/****************************************************************************/

/****************************************************************************/
/*!
\brief
Default constructor
\param diameter
		the diameter of our tree
\param displacement
		the displacement of our tree in the world
*/
/****************************************************************************/
VoxelOctree::VoxelOctree(int diameter, Vector3 displacement)
{
}
/****************************************************************************/
/*!
\brief
Default destructor
*/
/****************************************************************************/
VoxelOctree::~VoxelOctree()
{
}
/****************************************************************************/
/*!
\brief
Sets the first leaf to this range if it has not been initialised yet
\param diameter
		the diameter of the first leaf
\param displacement
		the displacement of the leaf in the world
*/
/****************************************************************************/
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
/****************************************************************************/
/*!
\brief
Returns the radius of the tree
*/
/****************************************************************************/
int VoxelOctree::GetRadius() const
{
	return mainLeaf.GetRadius();
}
/****************************************************************************/
/*!
\brief
Add a voxel to the tree
\param voxel
		the voxel to be added
*/
/****************************************************************************/
void VoxelOctree::AddVoxel(Voxel& voxel)
{
	mainLeaf.AddVoxel(voxel);
	voxels.push_back(mainLeaf.GetVoxel(voxel.GetPosition()));
	if(voxels.back() == NULL)
	{
		throw;
	}
}
/****************************************************************************/
/*!
\brief
Returns the vector of voxels the tree contains
*/
/****************************************************************************/
std::vector<Voxel*>& VoxelOctree::GetVector()
{
	return voxels;
}
/****************************************************************************/
/*!
\brief
Returns the voxel at the specified position
\param position
		specifies the position of the voxel
*/
/****************************************************************************/
Voxel* VoxelOctree::GetVoxel(const Vector3& position)
{
	if(!mainLeaf.GetRangeX().IsInRange(position.x) || !mainLeaf.GetRangeY().IsInRange(position.y) || !mainLeaf.GetRangeZ().IsInRange(position.z))
	{
		return NULL;
	}
	return mainLeaf.GetVoxel(position);
}