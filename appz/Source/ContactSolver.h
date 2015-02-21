#pragma once
#include "Contacts.h"
#include "LinkList.h"
#include "VoxelOctree.h"

class ContactSolver
{
public:
	ContactSolver();
	~ContactSolver();
	bool CheckThisCollision(Voxel* voxel1, Voxel* voxel2, const double deltaTime);
	bool CheckThisCollision(drawOrder* draw1, drawOrder* draw2, const double deltaTime);
	void ResolveAllCollisionsAccordingTo(const double deltaTime);
private:
	LinkList<Contact> list;
};