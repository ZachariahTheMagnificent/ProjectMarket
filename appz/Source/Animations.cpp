#include "Animations.h"

drawOrder::drawOrder()
{
	geometry = NULL;
	enableLight = false;
	mass = 0;
	bounce = 0;
	staticFriction = 0;
	kineticFriction = 0;
}

drawOrder::~drawOrder()
{
}

void drawOrder::Execute()
{
}

void drawOrder::SetMaterial(const Material& mat)
{
	material = mat;
}

void drawOrder::SetTerminalVelocityTo(Vector3 vector)
{
	vector.x = abs(vector.x);
	vector.y = abs(vector.y);
	vector.z = abs(vector.z);
	terminalVelocity = vector;
}

void drawOrder::CapVelocityToTerminal()
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

void drawOrder::SetVelocityTo(Vector3 newVelocity)
{
	velocity = newVelocity;
	CapVelocityToTerminal();
}

void drawOrder::UpdateVelocity(const double deltaTime)
{
	Vector3 acceleration = GetAcceleration();
	velocity += acceleration * deltaTime;
	CapVelocityToTerminal();
}

void drawOrder::UpdateTo(const double deltaTime)
{
	//previousLocation = transform.translate;
	transform.translate += velocity * deltaTime;
	for(std::vector<Voxel>::iterator voxel = voxels.begin(); voxel != voxels.end(); voxel++)
	{
		voxel->UpdateTo(deltaTime);
	}
}

void drawOrder::AddVoxel(float x, float y, float z, Vector3 position, Color color)
{
	voxels.push_back(Voxel());
	voxels.back().AssignTo(this);
	voxels.back().SetSizeTo(x, y, z);
	voxels.back().SetPositionTo(position);
	voxels.back().SetColorTo(color);
}

void drawOrder::GainMomentumFrom(drawOrder* draw, Vector3 momentumGain)
{
	AddForce(momentumGain);
	draw->AddForce(-momentumGain);
	//velocity += momentumGain / mass;
	//draw->velocity -= momentumGain / mass;
}

void drawOrder::LoseMomentumTo(drawOrder* draw, Vector3 momentumLost)
{
	AddForce(-momentumLost);
	draw->AddForce(momentumLost);
	//velocity -= momentumLost / mass;
	//draw->velocity += momentumLost / draw->mass;
}

void drawOrder::AddForce(Vector3 force)
{
	forces.push_back(force);
}

Vector3 drawOrder::GetAcceleration()
{
	Vector3 acceleration;
	for(std::vector<Vector3>::iterator force = forces.begin(); force != forces.end(); force++)
	{
		if(mass)
		{
			acceleration += *force / mass;
		}
	}
	return acceleration;
}

Vector3 drawOrder::GetMomentum()
{
	return velocity * mass;
}

void drawOrder::SetMomentumTo(Vector3 momentum)
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

float drawOrder::GetKinetic()
{
	return 0.5f * mass * velocity.Length() * velocity.Length();
}