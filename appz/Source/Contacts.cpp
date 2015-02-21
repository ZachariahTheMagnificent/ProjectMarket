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
	if(firstVoxel->At(timeOfImpact).IsCollidingWith(secondVoxel->At(timeOfImpact)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Contact::Set(Voxel* firstVoxel, Voxel* secondVoxel, const double timeOfImpact)
{
	this->firstVoxel = firstVoxel;
	this->secondVoxel = secondVoxel;
	this->timeOfImpact = timeOfImpact;
}

void Contact::ResolveAccordingTo(const double deltaTime)
{
	Voxel FirstVoxelAtCollision = firstVoxel->At(timeOfImpact);
	Voxel SecondVoxelAtCollision = secondVoxel->At(timeOfImpact);

	Vector3 first_sVelocity = FirstVoxelAtCollision.GetDistanceFrom(SecondVoxelAtCollision);
	Vector3 second_sVelocity = SecondVoxelAtCollision.GetDistanceFrom(FirstVoxelAtCollision);
	//float penetration = Voxel::GetSize() - (first_sVelocity.Length() - Voxel::GetSize());
	//float pushRatio = FirstVoxelAtCollision.GetVelocity();

	//const float firsts_MinX = FirstVoxelAtCollision.GetMinX();
	//const float firsts_MinY = FirstVoxelAtCollision.GetMinY();
	//const float firsts_MinZ = FirstVoxelAtCollision.GetMinZ();
	//const float firsts_MaxX = FirstVoxelAtCollision.GetMaxX();
	//const float firsts_MaxY = FirstVoxelAtCollision.GetMaxY();
	//const float firsts_MaxZ = FirstVoxelAtCollision.GetMaxZ();

	//const float seconds_MinX = SecondVoxelAtCollision.GetMinX();
	//const float seconds_MinY = SecondVoxelAtCollision.GetMinY();
	//const float seconds_MinZ = SecondVoxelAtCollision.GetMinZ();
	//const float seconds_MaxX = SecondVoxelAtCollision.GetMaxX();
	//const float seconds_MaxY = SecondVoxelAtCollision.GetMaxY();
	//const float seconds_MaxZ = SecondVoxelAtCollision.GetMaxZ();

	//float penetrationX;
	//float penetrationY;
	//float penetrationZ;

	//if(FirstVoxelAtCollision.IsToTheRightOf(SecondVoxelAtCollision))
	//{
	//	penetrationX = seconds_MaxX - firsts_MinX;
	//}
	//else
	//{
	//	penetrationX = firsts_MaxX - seconds_MinX;
	//}
	//if(FirstVoxelAtCollision.IsAbove(SecondVoxelAtCollision))
	//{
	//	penetrationY = seconds_MaxY - firsts_MinY;
	//}
	//else
	//{
	//	penetrationY = firsts_MaxY - seconds_MinY;
	//}
	//if(FirstVoxelAtCollision.IsInFrontOf(SecondVoxelAtCollision))
	//{
	//	penetrationZ = seconds_MaxZ - firsts_MinZ;
	//}
	//else
	//{
	//	penetrationZ = firsts_MaxZ - seconds_MinZ;
	//}

	//Vector3 firsts_newVelocity = firstVoxel->GetVelocity();
	//Vector3 seconds_newVelocity = secondVoxel->GetVelocity();
	//Vector3 firsts_distanceTravelled = FirstVoxelAtCollision.GetDistanceFrom(*firstVoxel);
	//Vector3 seconds_distanaceTravelled = SecondVoxelAtCollision.GetDistanceFrom(*secondVoxel);

	////Find the side where the collision happened and change the coresponding vector component(by transfering momentum) to prevent it
	//if(penetrationX < penetrationY && penetrationX < penetrationZ)
	//{
	//	if((FirstVoxelAtCollision.IsToTheLeftOf(SecondVoxelAtCollision) && !isNegative(FirstVoxelAtCollision.GetVelocity().x) && FirstVoxelAtCollision.GetVelocity().x != 0) ||
	//		(FirstVoxelAtCollision.IsToTheRightOf(SecondVoxelAtCollision) && isNegative(FirstVoxelAtCollision.GetVelocity().x) && FirstVoxelAtCollision.GetVelocity().x != 0))
	//	{
	//		firsts_newVelocity.y += abs(FirstVoxelAtCollision.GetVelocity().x) * deltaTime;
	//		firsts_newVelocity.x = firsts_distanceTravelled.x / deltaTime;
	//	}
	//	if((SecondVoxelAtCollision.IsToTheLeftOf(FirstVoxelAtCollision) && !isNegative(SecondVoxelAtCollision.GetVelocity().x) && SecondVoxelAtCollision.GetVelocity().x != 0) ||
	//		(SecondVoxelAtCollision.IsToTheRightOf(FirstVoxelAtCollision) && isNegative(SecondVoxelAtCollision.GetVelocity().x) && SecondVoxelAtCollision.GetVelocity().x != 0))
	//	{
	//		seconds_newVelocity.y += abs(SecondVoxelAtCollision.GetVelocity().x) * deltaTime;
	//		seconds_newVelocity.x = seconds_distanaceTravelled.x / deltaTime;
	//	}
	//	firstVoxel->ChangeVelocityTo(firsts_newVelocity/*, secondVoxel*/);
	//	secondVoxel->ChangeVelocityTo(seconds_newVelocity/*, firstVoxel*/);
	//}
	//else if(penetrationY < penetrationX && penetrationY < penetrationZ)
	//{
	//	if((FirstVoxelAtCollision.IsBelow(SecondVoxelAtCollision) && !isNegative(FirstVoxelAtCollision.GetVelocity().y) && FirstVoxelAtCollision.GetVelocity().y != 0) ||
	//		(FirstVoxelAtCollision.IsAbove(SecondVoxelAtCollision) && isNegative(FirstVoxelAtCollision.GetVelocity().y) && FirstVoxelAtCollision.GetVelocity().y != 0))
	//	{
	//		firsts_newVelocity.y = firsts_distanceTravelled.y / deltaTime;
	//	}
	//	if((SecondVoxelAtCollision.IsBelow(FirstVoxelAtCollision) && !isNegative(SecondVoxelAtCollision.GetVelocity().y) && SecondVoxelAtCollision.GetVelocity().y != 0) ||
	//		(SecondVoxelAtCollision.IsAbove(FirstVoxelAtCollision) && isNegative(SecondVoxelAtCollision.GetVelocity().y) && SecondVoxelAtCollision.GetVelocity().y != 0))
	//	{
	//		seconds_newVelocity.y = seconds_distanaceTravelled.y / deltaTime;
	//	}
	//	firstVoxel->ChangeVelocityTo(firsts_newVelocity/*, secondVoxel*/);
	//	secondVoxel->ChangeVelocityTo(seconds_newVelocity/*, firstVoxel*/);
	//}
	//else
	//{
	//	if((FirstVoxelAtCollision.IsBehind(SecondVoxelAtCollision) && !isNegative(FirstVoxelAtCollision.GetVelocity().z) && FirstVoxelAtCollision.GetVelocity().z != 0) ||
	//		(FirstVoxelAtCollision.IsInFrontOf(SecondVoxelAtCollision) && isNegative(FirstVoxelAtCollision.GetVelocity().z) && FirstVoxelAtCollision.GetVelocity().z != 0))
	//	{
	//		firsts_newVelocity.y += abs(FirstVoxelAtCollision.GetVelocity().z) * deltaTime;
	//		firsts_newVelocity.z = firsts_distanceTravelled.z / deltaTime;
	//	}
	//	if((SecondVoxelAtCollision.IsBehind(FirstVoxelAtCollision) && !isNegative(SecondVoxelAtCollision.GetVelocity().z) && SecondVoxelAtCollision.GetVelocity().z != 0) ||
	//		(SecondVoxelAtCollision.IsInFrontOf(FirstVoxelAtCollision) && isNegative(SecondVoxelAtCollision.GetVelocity().z) && SecondVoxelAtCollision.GetVelocity().z != 0))
	//	{
	//		seconds_newVelocity.y += abs(SecondVoxelAtCollision.GetVelocity().z) * deltaTime;
	//		seconds_newVelocity.z = seconds_distanaceTravelled.z / deltaTime;
	//	}
	//	firstVoxel->ChangeVelocityTo(firsts_newVelocity/*, secondVoxel*/);
	//	secondVoxel->ChangeVelocityTo(seconds_newVelocity/*, firstVoxel*/);
	//}

	//Lastly, we create a friction force for each voxel
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
