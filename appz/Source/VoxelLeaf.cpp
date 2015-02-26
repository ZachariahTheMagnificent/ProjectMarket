#include "VoxelLeaf.h"

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
	voxels.resize(8, NULL);
}

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

void VoxelLeaf::AddVoxel(Voxel& voxel)
{
	unsigned index = GetIndex(voxel.GetPosition());
	//if there is already a voxel there and we can still subdivide
	if(voxels[index] && fullRangeX.Length() > 2)
	{
		Subdivide();
		std::vector<Voxel*>::iterator ourVoxel = voxels.begin(), end = voxels.end();
		for(std::vector<VoxelLeaf*>::iterator leaf = leaves.begin(); ourVoxel != end; ++leaf, ++ourVoxel)
		{
			if(*ourVoxel)
			{
				(*leaf)->AddVoxel(**ourVoxel);
			}
			*ourVoxel = NULL;
		}
		leaves[index]->AddVoxel(voxel);
	}
	else if(HasAlreadySubdivided())
	{
		leaves[index]->AddVoxel(voxel);
	}
	else
	{
		voxels[index] = &voxel;
	}
}

Voxel* VoxelLeaf::GetVoxel(const Vector3& position)
{
	Vector3 testposition((int)position.x, (int)position.y, (int)position.z);
	unsigned index = GetIndex(position);
	if(HasAlreadySubdivided())
	{
		return leaves[index]->GetVoxel(position);
	}
	for(std::vector<Voxel*>::iterator voxel = voxels.begin(), end = voxels.end(); voxel != end; ++voxel)
	{
		if(*voxel)
		{
			Vector3 voxelPosition((int)(*voxel)->GetPosition().x, (int)(*voxel)->GetPosition().y, (int)(*voxel)->GetPosition().z);
			if(voxelPosition == testposition)
			{
				return *voxel;
			}
		}
	}
	return NULL;
}

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

bool VoxelLeaf::HasAlreadySubdivided() const
{
	return leaves.front();
}

bool VoxelLeaf::IsEmpty() const
{
	if(!voxels.front() && !HasAlreadySubdivided())
	{
		return true;
	}
	return false;
}

unsigned VoxelLeaf::GetIndex(const Vector3& position)
{
	unsigned x,y,z;
	if(lowerRangeX.IsInRange(position.x))
	{
		x = 0;
	}
	else
	{
		x = 1;
	}
	if(lowerRangeY.IsInRange(position.y))
	{
		y = 0;
	}
	else
	{
		y = 1;
	}
	if(lowerRangeZ.IsInRange(position.z))
	{
		z = 0;
	}
	else
	{
		z = 1;
	}
	return x*4 + y*2 + z;
}