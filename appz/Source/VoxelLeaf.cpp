#include "VoxelLeaf.h"
/****************************************************************************/
/*!
\file VoxelLeaf.cpp
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A node in the voxelOctree
*/
/****************************************************************************/

/****************************************************************************/
/*!
\brief
Default constructor
\param rangeX
		the x-range of the leaf
\param rangeY
		the y-range of the leaf
\param rangeZ
		the z-range of the leaf
\param parent
		a pointer to the leaf above it in the hierarachy
*/
/****************************************************************************/
VoxelLeaf::VoxelLeaf(const Range<int> rangeX, const Range<int> rangeY, const Range<int> rangeZ, VoxelLeaf *const parent)
	:
fullRangeX(rangeX),
fullRangeY(rangeY),
fullRangeZ(rangeZ),
parent(parent)
{
	lowerRangeX.Start(fullRangeX.Start());
	lowerRangeX.End(fullRangeX.MidPoint());
	upperRangeX.Start(fullRangeX.MidPoint() + 1);
	upperRangeX.End(fullRangeX.End());
	lowerRangeY.Start(fullRangeY.Start());
	lowerRangeY.End(fullRangeY.MidPoint());
	upperRangeY.Start(fullRangeY.MidPoint() + 1);
	upperRangeY.End(fullRangeY.End());
	lowerRangeZ.Start(fullRangeZ.Start());
	lowerRangeZ.End(fullRangeZ.MidPoint());
	upperRangeZ.Start(fullRangeZ.MidPoint() + 1);
	upperRangeZ.End(fullRangeZ.End());
	leaves.resize(8, NULL);
	voxels.resize(8);
}
/****************************************************************************/
/*!
\brief
Sets the range of the voxel if it has not been used yet
\param rangeX
		sets the x-range of the leaf
\param rangeY
		sets the y-range of the leaf
\param rangeZ
		sets the z-range of the leaf
*/
/****************************************************************************/
void VoxelLeaf::SetRangeTo(const Range<int> rangeX, const Range<int> rangeY, const Range<int> rangeZ)
{
	if(HasAlreadySubdivided() || parent)
	{
		throw;
	}
	fullRangeX = rangeX;
	fullRangeY = rangeY;
	fullRangeZ = rangeZ;
	lowerRangeX.Start(fullRangeX.Start());
	lowerRangeX.End(fullRangeX.MidPoint());
	upperRangeX.Start(fullRangeX.MidPoint() + 1);
	upperRangeX.End(fullRangeX.End());
	lowerRangeY.Start(fullRangeY.Start());
	lowerRangeY.End(fullRangeY.MidPoint());
	upperRangeY.Start(fullRangeY.MidPoint() + 1);
	upperRangeY.End(fullRangeY.End());
	lowerRangeZ.Start(fullRangeZ.Start());
	lowerRangeZ.End(fullRangeZ.MidPoint());
	upperRangeZ.Start(fullRangeZ.MidPoint() + 1);
	upperRangeZ.End(fullRangeZ.End());
}
/****************************************************************************/
/*!
\brief
Default destructor
*/
/****************************************************************************/
VoxelLeaf::~VoxelLeaf()
{
	for(std::vector<VoxelLeaf*>::iterator leaf = leaves.begin(), end = leaves.end(); leaf != end; ++leaf)
	{
		if(*leaf)
		{
			delete *leaf;
			*leaf = NULL;
		}
	}
}
/****************************************************************************/
/*!
\brief
Add a voxel to the leaf
*/
/****************************************************************************/
void VoxelLeaf::AddVoxel(Voxel& voxel)
{
	unsigned index = GetIndex(voxel.GetPosition());
	if(HasAlreadySubdivided())
	{
		leaves[index]->AddVoxel(voxel);
	}
	//if there is already a voxel there and we can still subdivide
	else if(voxels[index].GetSolidness() && fullRangeX.Length() > 2)
	{
		Subdivide();
		std::vector<Voxel>::iterator ourVoxel = voxels.begin(), end = voxels.end();
		for(std::vector<VoxelLeaf*>::iterator leaf = leaves.begin(); ourVoxel != end; ++leaf, ++ourVoxel)
		{
			if(ourVoxel->GetSolidness())
			{
				(*leaf)->AddVoxel(*ourVoxel);
			}
		}
		leaves[index]->AddVoxel(voxel);
		voxels.clear();
	}
	else
	{
		//if there is already a voxel there
		if(voxels[index].GetSolidness())
		{
			return;
		}
		voxels[index] = voxel;
	}
}
/****************************************************************************/
/*!
\brief
Returns the x-range of the leaf
*/
/****************************************************************************/
const Range<int>& VoxelLeaf::GetRangeX() const
{
	return fullRangeX;
}
/****************************************************************************/
/*!
\brief
Returns the y-range of the leaf
*/
/****************************************************************************/
const Range<int>& VoxelLeaf::GetRangeY() const
{
	return fullRangeY;
}
/****************************************************************************/
/*!
\brief
Returns the z-range of the leaf
*/
/****************************************************************************/
const Range<int>& VoxelLeaf::GetRangeZ() const
{
	return fullRangeZ;
}
/****************************************************************************/
/*!
\brief
Returns a voxel at the specified position
\param position
		the specified position of the voxel
*/
/****************************************************************************/
Voxel* VoxelLeaf::GetVoxel(const Vector3& position)
{
	if(HasAlreadySubdivided())
	{
		unsigned index = GetIndex(position);
		return leaves[index]->GetVoxel(position);
	}
	for(std::vector<Voxel>::iterator voxel = voxels.begin(), end = voxels.end(); voxel != end; ++voxel)
	{
		if(voxel->GetSolidness())
		{
			Vector3 testposition((int)position.x, (int)position.y, (int)position.z);
			Vector3 voxelPosition((int)voxel->GetPosition().x, (int)voxel->GetPosition().y, (int)voxel->GetPosition().z);
			if(voxelPosition == testposition)
			{
				return &*voxel;
			}
		}
	}
	return NULL;
}
/****************************************************************************/
/*!
\brief
Subdivides the leaf into more leaves
*/
/****************************************************************************/
void VoxelLeaf::Subdivide()
{
	std::vector<VoxelLeaf*>::iterator leaf = leaves.begin();
	*leaf = new VoxelLeaf(lowerRangeX, lowerRangeY, lowerRangeZ, this);
	++leaf;
	*leaf = new VoxelLeaf(lowerRangeX, lowerRangeY, upperRangeZ, this);
	++leaf;
	*leaf = new VoxelLeaf(lowerRangeX, upperRangeY, lowerRangeZ, this);
	++leaf;
	*leaf = new VoxelLeaf(lowerRangeX, upperRangeY, upperRangeZ, this);
	++leaf;
	*leaf = new VoxelLeaf(upperRangeX, lowerRangeY, lowerRangeZ, this);
	++leaf;
	*leaf = new VoxelLeaf(upperRangeX, lowerRangeY, upperRangeZ, this);
	++leaf;
	*leaf = new VoxelLeaf(upperRangeX, upperRangeY, lowerRangeZ, this);
	++leaf;
	*leaf = new VoxelLeaf(upperRangeX, upperRangeY, upperRangeZ, this);
	++leaf;
}
/****************************************************************************/
/*!
\brief
Returns a bool to whether or not the leaf has already subdivided
*/
/****************************************************************************/
bool VoxelLeaf::HasAlreadySubdivided() const
{
	if(leaves.front())
	{
		return true;
	}
	return false;
}
/****************************************************************************/
/*!
\brief
Returns a bool to whether or not the leaf is empty
*/
/****************************************************************************/
bool VoxelLeaf::IsEmpty() const
{
	if(voxels.front().GetSolidness() == 0 && !HasAlreadySubdivided())
	{
		return true;
	}
	return false;
}
/****************************************************************************/
/*!
\brief
Turns a position into an index
\param position
		the position used to get an index
*/
/****************************************************************************/
unsigned VoxelLeaf::GetIndex(const Vector3& position)
{
	unsigned x,y,z;
	if(lowerRangeX.IsInRange(position.x))
	{
		x = 0;
	}
	else if(upperRangeX.IsInRange(position.x))
	{
		x = 1;
	}
	else
	{
		throw;
	}

	if(lowerRangeY.IsInRange(position.y))
	{
		y = 0;
	}
	else if(upperRangeY.IsInRange(position.y))
	{
		y = 1;
	}
	else
	{
		throw;
	}

	if(lowerRangeZ.IsInRange(position.z))
	{
		z = 0;
	}
	else if(upperRangeZ.IsInRange(position.z))
	{
		z = 1;
	}
	else
	{
		throw;
	}

	return x*4 + y*2 + z;
}
/****************************************************************************/
/*!
\brief
returns the radius of the leaf
*/
/****************************************************************************/
int VoxelLeaf::GetRadius() const
{
	return lowerRangeX.Length();
}