#pragma once
#include "Contacts.h"
#include "LinkList.h"

class ContactSolver
{
public:
	ContactSolver();
	~ContactSolver();
	bool CheckThisCollision(Voxel* voxel1, Voxel* voxel2, const double deltaTime);
	void ResolveAllCollisionsAccordingTo(const double deltaTime);
private:
	LinkList<Contact> list;
};