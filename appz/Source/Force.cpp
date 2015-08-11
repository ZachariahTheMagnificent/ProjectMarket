#include "force.h"
/****************************************************************************/
/*!
\file Force.cpp
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class used to store and handle force information
*/
/****************************************************************************/
Force::Force(const Vector3 force, bool attract)
	:
force(force),
attract(attract)
{
}

Force::~Force()
{
}

Vector3 Force::GetVector() const
{
	if(isDead())
	{
		return Vector3();
	}
	return force;
}

void Force::UpdateTo(const double deltaTime)
{
	if(lifespan != 0)
	{
		lifespan -= deltaTime;
	}
}

void Force::SetLifespanTo(float time)
{
	lifespan = time;
}

bool Force::isDead() const
{
	if(lifespan < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Force::SetVector(Vector3 vector)
{
	force = vector;
}

void Force::ToggleAttraction()
{
	attract = !attract;
}

void Force::SetToAttract()
{
	attract = true;
}

void Force::SetToRepel()
{
	attract = false;
}