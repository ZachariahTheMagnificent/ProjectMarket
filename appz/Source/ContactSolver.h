#pragma once
#include "Contacts.h"
#include "LinkList.h"
#include "VoxelOctree.h"
#include "CollisionBody.h"
/****************************************************************************/
/*!
\file ContactSolver.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class used to solve and handle contacts
*/
/****************************************************************************/

/****************************************************************************/
/*!
Class ContactSolver:
\brief
Used to solve and handle contacts
*/
/****************************************************************************/
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