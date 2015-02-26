#include "VoxelOctree.h"
#include "timer.h"

VoxelOctree::VoxelOctree()
{
}

VoxelOctree::~VoxelOctree()
{
}

void VoxelOctree::AddVoxels(drawOrder& draw)
{
	for(std::vector<Voxel>::iterator voxel = draw.voxels.begin(), end = draw.voxels.end(); voxel != end; ++voxel)
	{
		AddVoxel(*voxel);
	}
}

void VoxelOctree::AddVoxel(Voxel& voxel)
{
	mainLeaf.AddVoxel(voxel);
}

void VoxelOctree::SolveCollisionFor(drawOrder& draw)
{
	for(std::vector<Voxel>::iterator voxel = draw.voxels.begin(), end = draw.voxels.end(); voxel != end; ++voxel)
	{
		if(mainLeaf.GetVoxel(voxel->GetPosition()))
		{
			draw.velocity.y = 0;
			return;
		}
	}
}

//void VoxelOctree::SetUpFor(drawOrder* draw1, drawOrder* draw2, const double deltaTime)
//{
//	if(draw1->boundRadius > draw2->boundRadius)
//	{
//		biggerDraw = draw1;
//		smallerDraw = draw2;
//	}
//	else
//	{
//		biggerDraw = draw2;
//		smallerDraw = draw1;
//	}
//
//	tree.resize(smallerDraw->voxels.size() * smallerDraw->voxels.size() * smallerDraw->voxels.size(), NULL);
//	//move the voxels to orgin to simplify the collision process
//	Vector3 originalTranslate = smallerDraw->transform.translate;
//	smallerDraw->transform.translate = Vector3(smallerDraw->boundRadius, smallerDraw->boundRadius, smallerDraw->boundRadius);
//	Mtx44 matrix = smallerDraw->GetMatrix();
//	smallerDraw->transform.translate = originalTranslate;
//
//	int Nx = smallerDraw->boundRadius;
//	int Nxy = smallerDraw->boundRadius * smallerDraw->boundRadius;
//	for(std::vector<Voxel>::iterator voxel = smallerDraw->voxels.begin(); voxel != smallerDraw->voxels.end(); ++voxel)
//	{
//		voxel->ApplyToMatrix(matrix);
//		int index = (int)voxel->GetPosition().x + (int)voxel->GetPosition().y * Nx + (int)voxel->GetPosition().z * Nxy;
//		tree[index] = &*voxel;
//	}
//
//	Vector3 smallerDrawDisplacement = smallerDraw->transform.translate - Vector3(smallerDraw->boundRadius, smallerDraw->boundRadius, smallerDraw->boundRadius) + smallerDraw->velocity * deltaTime;
//	Vector3 biggerDrawDisplacement = biggerDraw->transform.translate - Vector3(biggerDraw->boundRadius, biggerDraw->boundRadius, biggerDraw->boundRadius) + biggerDraw->velocity * deltaTime;
//	displacement = biggerDrawDisplacement - smallerDrawDisplacement;
//	this->deltaTime = deltaTime;
//}

//std::vector<Contact> VoxelOctree::GetAllContacts()
//{
//	std::vector<Contact> contactBuffer;
//	//set the orgin of the biggerdraw to the smallerdraw to better compare the former's voxels' position to the latter's voxels'
//	Vector3 originalTranslate = biggerDraw->transform.translate;
//	biggerDraw->transform.translate = displacement - Vector3(biggerDraw->boundRadius, biggerDraw->boundRadius, biggerDraw->boundRadius);
//	Mtx44 matrix = biggerDraw->GetMatrix();
//	biggerDraw->transform.translate = originalTranslate;
//	
//	double time = 0;
//	int Nx = smallerDraw->boundRadius;
//	int Nxy = smallerDraw->boundRadius * smallerDraw->boundRadius;
//	for(std::vector<Voxel>::iterator voxel = biggerDraw->voxels.begin(); voxel != biggerDraw->voxels.end(); ++voxel)
//	{
//		StopWatch timer;
//		timer.startTimer();
//		voxel->ApplyToMatrix(matrix);
//		time += timer.getElapsedTime();
//		int index = (int)voxel->GetPosition().x + (int)voxel->GetPosition().y * Nx + (int)voxel->GetPosition().z * Nxy;
//		if(index >= 0 && index < tree.size())
//		{
//			//if there is already a voxel there
//			if(tree[index])
//			{
//				contactBuffer.push_back(Contact(tree[index], &*voxel,deltaTime));
//			}
//		}
//	}
//	return contactBuffer;
//}