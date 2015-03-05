#include "Contacts.h"
#include "Custom Functions.h"
#include "CollisionBody.h"

Contact::Contact(CollisionBody* firstBody, CollisionBody* secondBody, Voxel* firstVoxel, Voxel* secondVoxel, const double timeOfImpact)
	:
firstBody(firstBody),
secondBody(secondBody),
firstVoxel(firstVoxel),
secondVoxel(secondVoxel)
{
}

Contact::~Contact()
{
}

bool Contact::IsStillValid()
{
	return true;
}

void Contact::Set(CollisionBody* firstBody, CollisionBody* secondBody, Voxel* firstVoxel, Voxel* secondVoxel, const double timeOfImpact)
{
	this->firstBody = firstBody;
	this->secondBody = secondBody;
	this->firstVoxel = firstVoxel;
	this->secondVoxel = secondVoxel;
	this->timeOfImpact = timeOfImpact;
}

void Contact::ResolveAccordingTo(const double deltaTime)
{
	Voxel FirstVoxelAtCollision = *firstVoxel;
	Voxel SecondVoxelAtCollision = *secondVoxel;
	FirstVoxelAtCollision.SetPositionTo(firstVoxel->GetPosition() + firstBody->GetVelocity() * timeOfImpact);
	SecondVoxelAtCollision.SetPositionTo(firstVoxel->GetPosition() + secondBody->GetVelocity() * timeOfImpact);

	const float firsts_MinX = FirstVoxelAtCollision.GetMinX();
	const float firsts_MinY = FirstVoxelAtCollision.GetMinY();
	const float firsts_MinZ = FirstVoxelAtCollision.GetMinZ();
	const float firsts_MaxX = FirstVoxelAtCollision.GetMaxX();
	const float firsts_MaxY = FirstVoxelAtCollision.GetMaxY();
	const float firsts_MaxZ = FirstVoxelAtCollision.GetMaxZ();

	const float seconds_MinX = SecondVoxelAtCollision.GetMinX();
	const float seconds_MinY = SecondVoxelAtCollision.GetMinY();
	const float seconds_MinZ = SecondVoxelAtCollision.GetMinZ();
	const float seconds_MaxX = SecondVoxelAtCollision.GetMaxX();
	const float seconds_MaxY = SecondVoxelAtCollision.GetMaxY();
	const float seconds_MaxZ = SecondVoxelAtCollision.GetMaxZ();

	float penetrationX;
	float penetrationY;
	float penetrationZ;

	if(FirstVoxelAtCollision.IsToTheRightOf(SecondVoxelAtCollision))
	{
		penetrationX = seconds_MaxX - firsts_MinX;
	}
	else
	{
		penetrationX = firsts_MaxX - seconds_MinX;
	}
	if(FirstVoxelAtCollision.IsAbove(SecondVoxelAtCollision))
	{
		penetrationY = seconds_MaxY - firsts_MinY;
	}
	else
	{
		penetrationY = firsts_MaxY - seconds_MinY;
	}
	if(FirstVoxelAtCollision.IsInFrontOf(SecondVoxelAtCollision))
	{
		penetrationZ = seconds_MaxZ - firsts_MinZ;
	}
	else
	{
		penetrationZ = firsts_MaxZ - seconds_MinZ;
	}

	Vector3 firsts_newVelocity = firstBody->GetVelocity();
	Vector3 seconds_newVelocity = secondBody->GetVelocity();
	Vector3 firsts_distanceTravelled = firstBody->GetVelocity() * timeOfImpact;
	Vector3 seconds_distanaceTravelled = secondBody->GetVelocity() * timeOfImpact;

	//Find the side where the collision happened and change the coresponding vector component(by transfering momentum) to prevent it
	if(penetrationX < penetrationY && penetrationX < penetrationZ)
	{
		if((FirstVoxelAtCollision.IsToTheLeftOf(SecondVoxelAtCollision) && !isNegative(firstBody->GetVelocity().x) && firstBody->GetVelocity().x != 0) ||
			(FirstVoxelAtCollision.IsToTheRightOf(SecondVoxelAtCollision) && isNegative(firstBody->GetVelocity().x) && firstBody->GetVelocity().x != 0))
		{
			firsts_newVelocity.y += abs(firstBody->GetVelocity().x) * deltaTime;
			firsts_newVelocity.x = firsts_distanceTravelled.x / deltaTime;
		}
		if((SecondVoxelAtCollision.IsToTheLeftOf(FirstVoxelAtCollision) && !isNegative(secondBody->GetVelocity().x) && secondBody->GetVelocity().x != 0) ||
			(SecondVoxelAtCollision.IsToTheRightOf(FirstVoxelAtCollision) && isNegative(secondBody->GetVelocity().x) && secondBody->GetVelocity().x != 0))
		{
			seconds_newVelocity.y += abs(secondBody->GetVelocity().x) * deltaTime;
			seconds_newVelocity.x = seconds_distanaceTravelled.x / deltaTime;
		}
		firstBody->SetVelocityTo(firsts_newVelocity);
		secondBody->SetVelocityTo(seconds_newVelocity);
	}
	else if(penetrationY < penetrationX && penetrationY < penetrationZ)
	{
		if((FirstVoxelAtCollision.IsBelow(SecondVoxelAtCollision) && !isNegative(firstBody->GetVelocity().y) && firstBody->GetVelocity().y != 0) ||
			(FirstVoxelAtCollision.IsAbove(SecondVoxelAtCollision) && isNegative(firstBody->GetVelocity().y) && firstBody->GetVelocity().y != 0))
		{
			firsts_newVelocity.y = firsts_distanceTravelled.y / deltaTime;
		}
		if((SecondVoxelAtCollision.IsBelow(FirstVoxelAtCollision) && !isNegative(secondBody->GetVelocity().y) && secondBody->GetVelocity().y != 0) ||
			(SecondVoxelAtCollision.IsAbove(FirstVoxelAtCollision) && isNegative(secondBody->GetVelocity().y) && secondBody->GetVelocity().y != 0))
		{
			seconds_newVelocity.y = seconds_distanaceTravelled.y / deltaTime;
		}
		firstBody->SetVelocityTo(firsts_newVelocity);
		secondBody->SetVelocityTo(seconds_newVelocity);
	}
	else
	{
		if((FirstVoxelAtCollision.IsBehind(SecondVoxelAtCollision) && !isNegative(firstBody->GetVelocity().z) && firstBody->GetVelocity().z != 0) ||
			(FirstVoxelAtCollision.IsInFrontOf(SecondVoxelAtCollision) && isNegative(firstBody->GetVelocity().z) && firstBody->GetVelocity().z != 0))
		{
			firsts_newVelocity.y += abs(firstBody->GetVelocity().z) * deltaTime;
			firsts_newVelocity.z = firsts_distanceTravelled.z / deltaTime;
		}
		if((SecondVoxelAtCollision.IsBehind(FirstVoxelAtCollision) && !isNegative(secondBody->GetVelocity().z) && secondBody->GetVelocity().z != 0) ||
			(SecondVoxelAtCollision.IsInFrontOf(FirstVoxelAtCollision) && isNegative(secondBody->GetVelocity().z) && secondBody->GetVelocity().z != 0))
		{
			seconds_newVelocity.y += abs(secondBody->GetVelocity().z) * deltaTime;
			seconds_newVelocity.z = seconds_distanaceTravelled.z / deltaTime;
		}
		firstBody->SetVelocityTo(firsts_newVelocity);
		secondBody->SetVelocityTo(seconds_newVelocity);
	}
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

bool Contact::operator==(const Contact& contact) const
{
	if(firstBody == contact.firstBody && secondBody == contact.secondBody)
	{
		return true;
	}
	else
	{
		return false;
	}
}