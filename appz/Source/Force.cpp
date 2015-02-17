#include "force.h"
#include "DrawOrder.h"

Force::Force(const unsigned boundX, const unsigned boundY, const unsigned boundZ, bool attract)
{
	this->boundX = boundX;
	this->boundY = boundY;
	this->boundZ = boundZ;
	this->attract = attract;
}

Force::~Force()
{
}

Vector3 Force::ReturnUpdatedAt(float deltaTime)
{
	if(isDead())
	{
		return Vector3();
	}
	lifespan -= deltaTime;
	if(lifespan == 0)
	{
		lifespan--;
	}
	return force;
}

void Force::SetLifespanTo(float time)
{
	lifespan = time;
}

bool Force::isDead()
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

void Force::SetBoundsTo(const unsigned boundX, const unsigned boundY, const unsigned boundZ)
{
	this->boundX = boundX;
	this->boundY = boundY;
	this->boundZ = boundZ;
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

bool Force::WillAffect(drawOrder& draw)
{
	//Calculating the bounds of the force in world space.
	int boundXLeft = position.x - boundX/2;
	int boundXRight = position.x + boundX/2;
	int boundYDown = position.y - boundY/2;
	int boundYUp = position.y + boundY/2;
	int boundZBack = position.z - boundZ/2;
	int boundZFront = position.z + boundZ/2;
	if((draw.transform.translate.x > boundXLeft && draw.transform.translate.x < boundXRight) &&
		(draw.transform.translate.y > boundYDown && draw.transform.translate.y < boundYUp) &&
		(draw.transform.translate.z > boundZBack && draw.transform.translate.z < boundZFront))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Force::ApplyTo(drawOrder* draw)
{
	draw->AddForce(force);
}