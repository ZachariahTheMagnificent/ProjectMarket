#include "CollisionBody.h"
#include "Custom Functions.h"

CollisionBody::CollisionBody(std::wstring name, drawOrder* draw, float mass, float bounce, float staticFriction, float kineticFriction)
	:
name(name),
draw(draw),
mass(mass),
bounce(bounce),
staticFriction(staticFriction),
kineticFriction(kineticFriction)
{
}

CollisionBody::~CollisionBody()
{
}

void CollisionBody::SetTerminalVelocityTo(Vector3 vector)
{
	vector.x = abs(vector.x);
	vector.y = abs(vector.y);
	vector.z = abs(vector.z);
	terminalVelocity = vector;
}

float CollisionBody::GetMass() const
{
	return mass;
}

void CollisionBody::UpdateForcesTo(const double deltaTime)
{
	std::vector<Force>::iterator force = forces.begin();
	while(force != forces.end())
	{
		force->UpdateTo(deltaTime);
		if(force->isDead())
		{
			force = forces.erase(force);
		}
		else
		{
			++force;
		}
	}
}

void CollisionBody::UpdateVelocity(const double deltaTime)
{
	Vector3 acceleration = GetAcceleration();
	velocity += acceleration * deltaTime;
	CapVelocityToTerminal();
}

void CollisionBody::UpdateTo(const double deltaTime)
{
	draw->transform.translate += velocity * deltaTime;
	ApplyFriction();
}

void CollisionBody::ApplyFriction()
{
	velocity *= (1 - staticFriction);
}

void CollisionBody::GainMomentumFrom(CollisionBody* draw, Vector3 momentumGain)
{
	AddForce(momentumGain);
	draw->AddForce(-momentumGain);
	//velocity += momentumGain / mass;
	//draw->velocity -= momentumGain / mass;
}

const Vector3& CollisionBody::GetVelocity() const
{
	return velocity;
}

void CollisionBody::LoseMomentumTo(CollisionBody* draw, Vector3 momentumLost)
{
	AddForce(-momentumLost);
	draw->AddForce(momentumLost);
	//velocity -= momentumLost / mass;
	//draw->velocity += momentumLost / draw->mass;
}

void CollisionBody::AddForce(Vector3 force)
{
	Force actualForce;
	actualForce.SetLifespanTo(0);
	actualForce.SetVector(force);
	forces.push_back(actualForce);
}

void CollisionBody::AddForce(Force force)
{
	forces.push_back(force);
}

Vector3 CollisionBody::GetAcceleration()
{
	Vector3 acceleration;
	for(std::vector<Force>::iterator force = forces.begin(); force != forces.end(); force++)
	{
		if(mass)
		{
			acceleration += force->GetVector() / mass;
		}
	}
	return acceleration;
}

Vector3 CollisionBody::GetMomentum()
{
	return velocity * mass;
}

void CollisionBody::SetMomentumTo(Vector3 momentum)
{
	//if the object has zero mass, it is unaffected by force but can still be moved by it's velocity. Setting it's velocity to zero when colliding with other objects should stop it from going through them.
	if(mass == 0)
	{
		velocity.SetZero();
	}
	else
	{
		velocity = momentum / mass;
		CapVelocityToTerminal();
	}
}

void CollisionBody::CapVelocityToTerminal()
{
	if(abs(velocity.x) > terminalVelocity.x)
	{
		if(isNegative(velocity.x))
		{
			velocity.x = terminalVelocity.x * -1;
		}
		else
		{
			velocity.x = terminalVelocity.x;
		}
	}
	if(abs(velocity.y) > terminalVelocity.y)
	{
		if(isNegative(velocity.y))
		{
			velocity.y = terminalVelocity.y * -1;
		}
		else
		{
			velocity.y = terminalVelocity.y;
		}
	}
	if(abs(velocity.z) > terminalVelocity.z)
	{
		if(isNegative(velocity.z))
		{
			velocity.z = terminalVelocity.z * -1;
		}
		else
		{
			velocity.z = terminalVelocity.z;
		}
	}
}

void CollisionBody::SetMassTo(const float mass)
{
	this->mass = mass;
}

void CollisionBody::SetFrictionTo(const float staticz, const float kineticz)
{
	staticFriction = staticz;
	kineticFriction = kineticz;
}

void CollisionBody::GenerateVoxels()
{
	//if(geometry)
	//{
	//	voxels = geometry->GenerateVoxel();
	//}
}

std::wstring CollisionBody::GetName() const
{
	return name;
}

void CollisionBody::SetNameAs(const std::wstring name)
{
	this->name = name;
}

float CollisionBody::GetKinetic()
{
	return 0.5f * mass * velocity.Length() * velocity.Length();
}

float CollisionBody::GetMaxX() const
{
	return (draw->GetMatrix() * draw->transform.translate).x + (float)voxels->GetRadius();
}

float CollisionBody::GetMinX() const
{
	return (draw->GetMatrix() * draw->transform.translate).x - (float)voxels->GetRadius();
}

float CollisionBody::GetMaxY() const
{
	return (draw->GetMatrix() * draw->transform.translate).y + (float)voxels->GetRadius();
}

float CollisionBody::GetMinY() const
{
	return (draw->GetMatrix() * draw->transform.translate).y - (float)voxels->GetRadius();
}

float CollisionBody::GetMaxZ() const
{
	return (draw->GetMatrix() * draw->transform.translate).z + (float)voxels->GetRadius();
}

float CollisionBody::GetMinZ() const
{
	return (draw->GetMatrix() * draw->transform.translate).z - (float)voxels->GetRadius();
}