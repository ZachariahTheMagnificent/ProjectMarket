#include "Contacts.h"

Contact::Contact(Voxel* firstVoxel, Voxel* secondVoxel, const double timeOfImpact)
{
	Set(firstVoxel, secondVoxel, timeOfImpact);
}

Contact::~Contact()
{
}

bool Contact::IsStillValid()
{
	return true;
}

void Contact::Set(Voxel* firstVoxel, Voxel* secondVoxel, const double timeOfImpact)
{
	this->firstVoxel = firstVoxel;
	this->secondVoxel = secondVoxel;
	this->timeOfImpact = timeOfImpact;
}

void Contact::ResolveAccordingTo(const double deltaTime)
{
}

bool Contact::operator<(const Contact& contact) const
{
	if(timeOfImpact < contact.timeOfImpact)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Contact::operator>(const Contact& contact) const
{
	if(timeOfImpact > contact.timeOfImpact)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Contact::operator<=(const Contact& contact) const
{
	if(timeOfImpact <= contact.timeOfImpact)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Contact::operator>=(const Contact& contact) const
{
	if(timeOfImpact >= contact.timeOfImpact)
	{
		return true;
	}
	else
	{
		return false;
	}
}
