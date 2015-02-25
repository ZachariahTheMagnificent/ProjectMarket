#include "DrawOrder.h"
#include "Graphics.h"

drawOrder::drawOrder(std::wstring name, Mesh* geometry, Material* material, drawOrder* parent, bool enableLight, float mass, float bounce, float staticFriction, float kineticFriction)
	:
name(name),
geometry(geometry),
material(material),
enableLight(enableLight),
mass(mass),
bounce(bounce),
staticFriction(staticFriction),
kineticFriction(kineticFriction)
{
	this->parent = NULL;
	SetParentAs(parent);
	boundRadius = 0;
	drawMode = GL_TRIANGLES;
}

drawOrder::~drawOrder()
{
}

void drawOrder::Copy(drawOrder& original)
{
	name = original.name;
	geometry = original.geometry;
	material = original.material;
	enableLight = original.enableLight;
	mass = original.mass;
	bounce = original.bounce;
	staticFriction = original.staticFriction;
	kineticFriction = original.kineticFriction;
	SetParentAs(original.parent);
	drawMode = original.drawMode;
}

const std::wstring& drawOrder::GetName() const
{
	return name;
}

void drawOrder::Execute(Graphics& gfx)
{
	for(std::vector<drawOrder*>::iterator child = children.begin(); child != children.end(); child++)
	{
		(*child)->Execute(gfx);
	}
	//a small check to see weather the draw order is pointing to a geometry before drawing it.
	if(geometry)
	{
		gfx.RenderMesh(*this, GetMatrix());
	}
}

void drawOrder::SetMaterial(Material* mat)
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

void drawOrder::SetNameAs(const std::wstring name)
{
	this->name = name;
}

void drawOrder::SetParentAs(drawOrder* parent)
{
	if(parent)
	{
		for(std::vector<drawOrder*>::iterator child = parent->children.begin(); child != parent->children.end(); ++child)
		{
			if(*child == this)
			{
				parent->children.erase(child);
				break;
			}
		}
	}
	this->parent = parent;
	if(parent)
	{
		parent->children.push_back(this);
	}
}

Mtx44 drawOrder::GetModelTransform() const
{
	if(parent)
	{
		return transform.TranslationMatrix() * transform.ScalationMatrix() * parent->GetModelTransform();
	}
	return transform.RotationMatrix() * transform.TranslationMatrix() * transform.ScalationMatrix();
}
 
Mtx44 drawOrder::GetMatrix() const
{
	return parent->GetModelTransform() * parent->GetRotationMatrix() * transform.Matrix() * selfTransform.Matrix();
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

float drawOrder::GetMass() const
{
	return mass;
}
void drawOrder::UpdateForcesTo(const double deltaTime)
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
void drawOrder::UpdateVelocity(const double deltaTime)
{
	Vector3 acceleration = GetAcceleration();
	velocity += acceleration * deltaTime;
	CapVelocityToTerminal();
}

void drawOrder::ApplyFriction()
{
	velocity *= (1 - staticFriction);
}

void drawOrder::UpdateTo(const double deltaTime)
{
	transform.translate += velocity * deltaTime;
	ApplyFriction();
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
	Force actualForce;
	actualForce.SetLifespanTo(0);
	actualForce.SetVector(force);
	forces.push_back(actualForce);
}

void drawOrder::AddForce(Force force)
{
	forces.push_back(force);
}

Vector3 drawOrder::GetAcceleration()
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

unsigned drawOrder::GetTexture() const
{
	return material->GetTexture();
}

void drawOrder::SetTextureTo(unsigned textureID)
{
	material->SetTextureTo(textureID);
}

Mtx44 drawOrder::GetTranslationMatrix() const
{
	return transform.TranslationMatrix();
}

Mtx44 drawOrder::GetRotationMatrix() const
{
	return transform.rotate.MatrixX() * transform.rotate.MatrixY() * transform.rotate.MatrixZ();
}

void drawOrder::GenerateVoxels()
{
	if(geometry)
	{
		voxels = geometry->GenerateVoxels();
	}
	float furtherstX = INT_MIN;
	float furtherstY = INT_MIN;
	float furtherstZ = INT_MIN;
	float nearestX = INT_MAX;
	float nearestY = INT_MAX;
	float nearestZ = INT_MAX;
	for(std::vector<Voxel>::iterator voxel = voxels.begin(); voxel != voxels.end(); ++voxel)
	{
		//the voxel is currently not bound to any draw so it should be at it's orgin
		int x = voxel->GetPosition().x, y = voxel->GetPosition().y, z = voxel->GetPosition().z;
		if(x < nearestX)
		{
			nearestX = x;
		}
		if(x > furtherstX)
		{
			furtherstX = x;
		}
		if(y < nearestY)
		{
			nearestY = y;
		}
		if(y > furtherstY)
		{
			furtherstY = y;
		}
		if(z < nearestZ)
		{
			nearestZ = z;
		}
		if(z > furtherstZ)
		{
			furtherstZ = z;
		}
		voxel->AssignTo(this);
	}
	float sizeX = abs(furtherstX - nearestX);
	float sizeY = abs(furtherstY - nearestY);
	float sizeZ = abs(furtherstZ - nearestZ);
	if(sizeX > sizeY && sizeX > sizeZ)
	{
		boundRadius = sizeX * 0.5 + 0.5;
	}
	if(sizeY > sizeX && sizeY > sizeZ)
	{
		boundRadius = sizeY * 0.5 + 0.5;
	}
	else
	{
		boundRadius = sizeZ * 0.5 + 0.5;
	}
}

void drawOrder::SetVoxelsToWorldPosition()
{
	for(std::vector<Voxel>::iterator voxel = voxels.begin(); voxel != voxels.end(); ++voxel)
	{
		voxel->ApplyCurrentMatrix();
	}
}

void drawOrder::SetVoxelsToOrgin()
{
	for(std::vector<Voxel>::iterator voxel = voxels.begin(); voxel != voxels.end(); ++voxel)
	{
		voxel->ResetToOrgin();
	}
}

bool drawOrder::IsCollidingWith(drawOrder& draw) const
{
	const float MinX = draw.GetMinX();
	const float MinY = draw.GetMinY();
	const float MinZ = draw.GetMinZ();
	const float MaxX = draw.GetMaxX();
	const float MaxY = draw.GetMaxY();
	const float MaxZ = draw.GetMaxZ();

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

float drawOrder::GetKinetic()
{
	return 0.5f * mass * velocity.Length() * velocity.Length();
}

void drawOrder::Render() const
{
	geometry->Render(material->GetTexture() , drawMode);
}

void drawOrder::RenderPartial(const unsigned offset, const unsigned count) const
{
	geometry->Render(offset, count, material->GetTexture(), drawMode);
}

float drawOrder::GetMaxX() const
{
	return (GetMatrix() * transform.translate).x + (float)boundRadius;
}

float drawOrder::GetMinX() const
{
	return (GetMatrix() * transform.translate).x - (float)boundRadius;
}

float drawOrder::GetMaxY() const
{
	return (GetMatrix() * transform.translate).y + (float)boundRadius;
}

float drawOrder::GetMinY() const
{
	return (GetMatrix() * transform.translate).y - (float)boundRadius;
}

float drawOrder::GetMaxZ() const
{
	return (GetMatrix() * transform.translate).z + (float)boundRadius;
}

float drawOrder::GetMinZ() const
{
	return (GetMatrix() * transform.translate).z - (float)boundRadius;
}