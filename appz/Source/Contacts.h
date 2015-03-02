#pragma once
#include "DrawOrder.h"
#include "Voxel.h"

class Contact
{
public:
	Contact(Voxel* firstVoxel = NULL, Voxel* secondVoxel = NULL, const double timeOfImpact = 0.0);
	~Contact();
	void Set(Voxel* firstVoxel, Voxel* secondVoxel, const double timeOfImpact);
	bool IsStillValid();
	void ResolveAccordingTo(const double deltaTime);
	bool operator<(const Contact& contact) const;
	bool operator>(const Contact& contact) const;
	bool operator<=(const Contact& contact) const;
	bool operator>=(const Contact& contact) const;
private:
	Voxel* firstVoxel;
	Voxel* secondVoxel;
	double timeOfImpact;
};