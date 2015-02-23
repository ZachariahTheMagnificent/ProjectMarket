#include "Voxel.h"
#include "DrawOrder.h"

Voxel::Voxel()
{
	draw = NULL;
}

Voxel::~Voxel()
{
}

Voxel Voxel::At(const double time)
{
	Voxel temp = *this;
	temp.SetPositionTo(position + GetVelocity() * time);
	return temp;
}

Color Voxel::GetColor() const
{
	return color;
}

Mtx44 Voxel::GetRotationMatrix() const
{
	return draw->GetRotationMatrix();
}

void Voxel::ApplyCurrentMatrix()
{
	if(draw)
	{
		Mtx44 matrix = draw->GetMatrix();
		displacement = matrix * position - position;
	}
}


void Voxel::ApplyToMatrix(Mtx44 matrix)
{
	displacement = matrix * position - position;
}

void Voxel::ResetToOrgin()
{
	displacement.SetZero();
}

Vector3 Voxel::GetPosition() const
{
	return displacement + position;
}

float Voxel::GetSize()
{
	static const float size = 1;
	return size;
}

void Voxel::SetColorTo(const Color newColor)
{
	color = newColor;
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
	return GetPosition() - voxel.GetPosition();
}

float Voxel::GetMaxX() const
{
	return GetPosition().x + GetSize()/2;
}

float Voxel::GetMinX() const
{
	return GetPosition().x - GetSize()/2;
}

float Voxel::GetMaxY() const
{
	return GetPosition().y + GetSize()/2;
}

float Voxel::GetMinY() const
{
	return GetPosition().y - GetSize()/2;
}

float Voxel::GetMaxZ() const
{
	return GetPosition().z + GetSize()/2;
}

float Voxel::GetMinZ() const
{
	return GetPosition().z - GetSize()/2;
}

bool Voxel::operator==(const Voxel& voxel) const
{
	if(position == voxel.position)
	{
		return true;
	}
	return false;
}