#pragma once
#include "Voxel.h"

class CollisionBody;

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