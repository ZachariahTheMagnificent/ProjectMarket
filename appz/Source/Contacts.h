#pragma once
#include "Voxel.h"
/****************************************************************************/
/*!
\file Contact.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class used handle contacts
*/
/****************************************************************************/
class CollisionBody;
/****************************************************************************/
/*!
Class Contact:
\brief
Used handle contacts
*/
/****************************************************************************/
class Contact
{
public:
	Contact(CollisionBody* firstBody = NULL, CollisionBody* secondBody = NULL, Voxel* firstVoxel = NULL, Voxel* secondVoxel = NULL, const double timeOfImpact = 0.0);
	~Contact();
	void Set(CollisionBody* firstBody, CollisionBody* secondBody, Voxel* firstVoxel, Voxel* secondVoxel, const double timeOfImpact);
	bool IsStillValid();
	void ResolveAccordingTo(const double deltaTime);
	bool operator<(const Contact& contact) const;
	bool operator>(const Contact& contact) const;
	bool operator<=(const Contact& contact) const;
	bool operator>=(const Contact& contact) const;
	bool operator==(const Contact& contact) const;
private:
	CollisionBody* firstBody;
	CollisionBody* secondBody;
	Voxel* firstVoxel;
	Voxel* secondVoxel;
	double timeOfImpact;
};