#pragma once
#include "Contacts.h"
#include "LinkList.h"
#include "VoxelOctree.h"
#include "CollisionBody.h"

class ContactSolver
{
public:
	ContactSolver();
	~ContactSolver();
	bool CheckThisCollision(Voxel* voxel1, Voxel* voxel2, const double deltaTime);
	bool CheckThisCollision(CollisionBody* body1, CollisionBody* body2, const double deltaTime);
	void ResolveAllCollisionsAccordingTo(const double deltaTime);
private:
	LinkList<Contact> list;
};