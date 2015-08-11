#include "Voxel.h"
#include "Custom Functions.h"
/****************************************************************************/
/*!
\file Voxel.cpp
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class used to store and handle voxel information
*/
/****************************************************************************/
Voxel::Voxel()
	:
solidness(0)
{
}

Voxel::~Voxel()
{
}

const char& Voxel::GetSolidness() const
{
	return solidness;
}

Color Voxel::GetColor() const
{
	return color;
}

Vector3 Voxel::GetPosition() const
{
	return position;
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

void Voxel::SetSolidityTo(const unsigned char solidity)
{
	solidness = solidity;
}