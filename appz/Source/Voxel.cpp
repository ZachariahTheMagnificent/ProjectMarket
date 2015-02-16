#include "Voxel.h"
#include "DrawOrder.h"

Voxel::Voxel()
{
	draw = NULL;
	sizeX = 1;
	sizeY = 1;
	sizeZ = 1;
}

Voxel::~Voxel()
{
}

Vector3 Voxel::GetPosition() const
{
	return position;
}

Vector3 Voxel::GetSize() const
{
	return Vector3(sizeX*2, sizeY*2, sizeZ*2);
}

void Voxel::SetSizeTo(const float x, const float y, const float z)
{
	sizeX = x/2;
	sizeY = y/2;
	sizeZ = z/2;
}

void Voxel::SetColorTo(const Color newColor)
{
	color = newColor;
}

void Voxel::UpdateTo(const double deltaTime)
{
	position += draw->velocity * deltaTime;
}

void Voxel::SetPositionTo(const Vector3 newPosition)
{
	position = newPosition;
}

void Voxel::AssignTo(drawOrder* newDraw)
{
	draw = newDraw;
}

bool Voxel::IsCollidingWith(const Voxel& voxel) const
{
	const float MinX = voxel.GetMinX();
	const float MinY = voxel.GetMinY();
	const float MinZ = voxel.GetMinZ();
	const float MaxX = voxel.GetMaxX();
	const float MaxY = voxel.GetMaxY();
	const float MaxZ = voxel.GetMaxZ();

	const float OurMinX = GetMinX();
	const float OurMinY = GetMinY();
	const float OurMinZ = GetMinZ();
	const float OurMaxX = GetMaxX();
	const float OurMaxY = GetMaxY();
	const float OurMaxZ = GetMaxZ();
	if((MinX < OurMaxX) && (MaxX > OurMinX) &&
		(MinY < OurMaxY) && (MaxY > OurMinY) &&
		(MinZ < OurMaxZ) && (MaxZ > OurMinZ))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Voxel::IsBehind(const Voxel& voxel) const
{
	if(isNegative(GetDistanceFrom(voxel).z))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Voxel::IsInFrontOf(const Voxel& voxel) const
{
	if(!isNegative(GetDistanceFrom(voxel).z))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Voxel::IsToTheLeftOf(const Voxel& voxel) const
{
	if(isNegative(GetDistanceFrom(voxel).x))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Voxel::IsToTheRightOf(const Voxel& voxel) const
{
	if(!isNegative(GetDistanceFrom(voxel).x))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Voxel::IsAbove(const Voxel& voxel) const
{
	if(!isNegative(GetDistanceFrom(voxel).y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Voxel::IsBelow(const Voxel& voxel) const
{
	if(isNegative(GetDistanceFrom(voxel).y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//bool Voxel::DoCollisionWith(Voxel* voxel, const double dt)
//{
//	if(IsCollidingWith(*voxel))
//	{
//		//we must apply friction first before transfering momentum
//		voxel->draw->velocity *= (1 - draw->kineticFriction);
//		draw->velocity *= (1 - voxel->draw->kineticFriction);
//
//		//transfer momentum
//		//Vector3 OldMomentum = voxel->draw->GetMomentum();
//		//Vector3 OurOldMomentum = draw->GetMomentum();
//		//Vector3 MomentumTransfer = voxel->draw->velocity * draw->mass;
//		//Vector3 OurMomentumTransfer = draw->velocity * voxel->draw->mass;
//		//Vector3 NewMomentum = OldMomentum - MomentumTransfer + OurMomentumTransfer;
//		//Vector3 OurNewMomentum = OurOldMomentum - OurMomentumTransfer + MomentumTransfer;
//		//voxel->draw->SetMomentum(NewMomentum);
//		//draw->SetMomentum(OurNewMomentum);
//
//		//stop the voxels from colliding
//		Vector3 changeInPosition;
//		Vector3 ourChangeInPosition;
//		
//		Vector3 PreviousPosition = voxel->draw->previousLocation;
//		Vector3 OurPreviousPosition = draw->previousLocation;
//		//velocity could already have been tempered with in previous collisions so this should give the original velocity of both voxels
//		Vector3 velocity = voxel->draw->transform.translate - PreviousPosition;
//		Vector3 ourVelocity = draw->transform.translate - OurPreviousPosition;
//		double timeOfImpact = 0;
//		double timestep = 0.001;
//		Voxel tempVox = *voxel, ourTempVox = *this;
//		tempVox.position -= velocity;
//		ourTempVox.position -= ourVelocity;
//		//find the exact timing of the collision by stepping forward in time in constant intervals
//		while(!ourTempVox.IsCollidingWith(tempVox))
//		{
//			tempVox.position = voxel->position - velocity + velocity * timeOfImpact;
//			ourTempVox.position = position - ourVelocity + ourVelocity * timeOfImpact;
//			timeOfImpact += timestep;
//		}
//
//		const float MinX = tempVox.position.x - tempVox.sizeX;
//		const float MinY = tempVox.position.y - tempVox.sizeY;
//		const float MinZ = tempVox.position.z - tempVox.sizeZ;
//		const float MaxX = tempVox.position.x + tempVox.sizeX;
//		const float MaxY = tempVox.position.y + tempVox.sizeY;
//		const float MaxZ = tempVox.position.z + tempVox.sizeZ;
//
//		const float OurMinX = ourTempVox.position.x - ourTempVox.sizeX;
//		const float OurMinY = ourTempVox.position.y - ourTempVox.sizeY;
//		const float OurMinZ = ourTempVox.position.z - ourTempVox.sizeZ;
//		const float OurMaxX = ourTempVox.position.x + ourTempVox.sizeX;
//		const float OurMaxY = ourTempVox.position.y + ourTempVox.sizeY;
//		const float OurMaxZ = ourTempVox.position.z + ourTempVox.sizeZ;
//
//		float penetrationX;
//		float penetrationY;
//		float penetrationZ;
//
//		//if we come are to the left of them, our right side is colliding with their left side
//		if(isNegative(ourTempVox.position.x - tempVox.position.x))
//		{
//			penetrationX = OurMaxX - MinX;
//		}
//		else
//		{
//			penetrationX = MaxX - OurMinX;
//		}
//		//if we come are at the bottom of them, our top side is colliding with their bottom side
//		if(isNegative(ourTempVox.position.y - tempVox.position.y))
//		{
//			penetrationY = OurMaxY - MinY;
//		}
//		else
//		{
//			penetrationY = MaxY - OurMinY;
//		}
//		//if we come are behind them, our front side is colliding with their back side
//		if(isNegative(ourTempVox.position.z - tempVox.position.z))
//		{
//			penetrationZ = OurMaxZ - MinZ;
//		}
//		else
//		{
//			penetrationZ = MaxZ - OurMinZ;
//		}
//
//		//Find the side where the collision happened and change the coresponding vector component such that the collision didn't happen
//		if(penetrationX < penetrationY && penetrationX < penetrationZ)
//		{
//			//since time of impact is the time where we collide, we step backwards to when we didn't collide
//			changeInPosition = Vector3(velocity.x - velocity.x * (timeOfImpact), 0, 0);
//			ourChangeInPosition = Vector3(ourVelocity.x - ourVelocity.x * (timeOfImpact), 0, 0);
//			
//			Vector3 momentumTransfer;
//			Vector3 ourMomentumTransfer;
//			if((isNegative(tempVox.position.x - ourTempVox.position.x) && !isNegative(velocity.x)) || (!isNegative(tempVox.position.x - ourTempVox.position.x) && isNegative(velocity.x)))
//			{
//				momentumTransfer.Set(voxel->draw->velocity.x * voxel->draw->mass, 0, 0);
//			}
//			if((isNegative(ourTempVox.position.x - tempVox.position.x) && !isNegative(ourVelocity.x)) || (!isNegative(ourTempVox.position.x - tempVox.position.x) && isNegative(ourVelocity.x)))
//			{
//				ourMomentumTransfer.Set(draw->velocity.x * draw->mass, 0, 0);
//			}
//			voxel->draw->SetMomentumTo(voxel->draw->GetMomentum() - momentumTransfer + ourMomentumTransfer);
//			draw->SetMomentumTo(draw->GetMomentum() - ourMomentumTransfer + momentumTransfer);
//		}
//		else if(penetrationY < penetrationX && penetrationY < penetrationZ)
//		{
//			changeInPosition = Vector3(0, velocity.y - velocity.y * (timeOfImpact), 0);
//			ourChangeInPosition = Vector3(0, ourVelocity.y - ourVelocity.y * (timeOfImpact), 0);
//			
//			Vector3 momentumTransfer;
//			Vector3 ourMomentumTransfer;
//			if((isNegative(tempVox.position.y - ourTempVox.position.y) && !isNegative(velocity.y)) || (!isNegative(tempVox.position.y - ourTempVox.position.y) && isNegative(velocity.y)))
//			{
//				momentumTransfer.Set(0, voxel->draw->velocity.y * voxel->draw->mass, 0);
//			}
//			if((isNegative(ourTempVox.position.y - tempVox.position.y) && !isNegative(ourVelocity.y)) || (!isNegative(ourTempVox.position.y - tempVox.position.y) && isNegative(ourVelocity.y)))
//			{
//				ourMomentumTransfer.Set(0, draw->velocity.y * draw->mass, 0);
//			}
//			voxel->draw->SetMomentumTo(voxel->draw->GetMomentum() - momentumTransfer + ourMomentumTransfer);
//			draw->SetMomentumTo(draw->GetMomentum() - ourMomentumTransfer + momentumTransfer);
//		}
//		else
//		{
//			changeInPosition = Vector3(0, 0, velocity.z - velocity.z * (timeOfImpact));
//			ourChangeInPosition = Vector3(0, 0, ourVelocity.z - ourVelocity.z * (timeOfImpact));
//
//			Vector3 momentumTransfer;
//			Vector3 ourMomentumTransfer;
//			if((isNegative(tempVox.position.z - ourTempVox.position.z) && !isNegative(velocity.z)) || (!isNegative(tempVox.position.z - ourTempVox.position.z) && isNegative(velocity.z)))
//			{
//				momentumTransfer.Set(0, 0, voxel->draw->velocity.z * voxel->draw->mass);
//			}
//			if((isNegative(ourTempVox.position.z - tempVox.position.z) && !isNegative(ourVelocity.z)) || (!isNegative(ourTempVox.position.z - tempVox.position.z) && isNegative(ourVelocity.z)))
//			{
//				ourMomentumTransfer.Set(0, 0, draw->velocity.z * draw->mass);
//			}
//			voxel->draw->SetMomentumTo(voxel->draw->GetMomentum() - momentumTransfer + ourMomentumTransfer);
//			draw->SetMomentumTo(draw->GetMomentum() - ourMomentumTransfer + momentumTransfer);
//		}
//		
//		//move our voxel such that it touches the surface of the voxel we're colliding with.
//		draw->transform.translate -= ourChangeInPosition;
//		for(std::vector<Voxel>::iterator vox = draw->voxels.begin(); vox != draw->voxels.end(); vox++)
//		{
//			vox->position -= ourChangeInPosition;
//		}
//		//move the voxel we're colliding with such that it touches the surface of our voxel.
//		voxel->draw->transform.translate -= changeInPosition;
//		for(std::vector<Voxel>::iterator vox = voxel->draw->voxels.begin(); vox != voxel->draw->voxels.end(); vox++)
//		{
//			vox->position -= changeInPosition;
//		}
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

Vector3 Voxel::GetVelocity() const
{
	return draw->velocity;
}

void Voxel::ChangeVelocityTo(const Vector3 newVelocity, Voxel* TransferMomentumToThisVoxel)
{
	if(TransferMomentumToThisVoxel)
	{
		Vector3 MomentumTransfer = (newVelocity - draw->velocity) * draw->mass;
		draw->LoseMomentumTo(TransferMomentumToThisVoxel->draw, MomentumTransfer);
	}
	else
	{
		draw->SetVelocityTo(newVelocity);
	}
}

Vector3 Voxel::GetDistanceFrom(const Voxel& voxel) const
{
	return position - voxel.position;
}

float Voxel::GetMaxX() const
{
	return position.x + sizeX;
}

float Voxel::GetMinX() const
{
	return position.x - sizeX;
}

float Voxel::GetMaxY() const
{
	return position.y + sizeY;
}

float Voxel::GetMinY() const
{
	return position.y - sizeY;
}

float Voxel::GetMaxZ() const
{
	return position.z + sizeZ;
}

float Voxel::GetMinZ() const
{
	return position.z - sizeZ;
}