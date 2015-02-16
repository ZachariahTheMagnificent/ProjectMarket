#pragma once
#include "Mesh.h"
#include "MatrixStack.h"
#include "Custom Functions.h"
#include "Voxel.h"

struct Rotation
{
	float x;
	float y;
	float z;
	void Set(const float rotX, const float rotY, const float rotZ)
	{
		x = rotX;
		y = rotY;
		z = rotZ;
	}

	Mtx44 MatrixX() const
	{
		Mtx44 matrixX;

		matrixX.SetToRotation(x,1.0f,0.0f,0.0f);

		return matrixX;
	}

	Mtx44 MatrixY() const
	{
		Mtx44 matrixY;

		matrixY.SetToRotation(y,0.0f,1.0f,0.0f);

		return matrixY;
	}

	Mtx44 MatrixZ() const
	{
		Mtx44 matrixZ;

		matrixZ.SetToRotation(z,0.0f,0.0f,1.0f);

		return matrixZ;
	}

	Rotation(const float rotX = 0, const float rotY = 0, const float rotZ = 0)
	{
		Set(rotX, rotY, rotZ);
	}

	void operator=(Rotation rotate)
	{
		x = rotate.x;
		y = rotate.y;
		z = rotate.z;
	}

	void operator+=(Rotation rotate)
	{
		x += rotate.x;
		y += rotate.y;
		z += rotate.z;
	}

	void operator+(Rotation rotate)
	{
		Rotation newRotate;

		newRotate = *this;
		newRotate += rotate;
	}
};

struct Transformation
{
	Vector3 translate;
	Rotation rotate;
	Vector3 pivot;
	Mtx44 Matrix() const
	{
		Mtx44 translation, rotation, reorientate;
		translation.SetToTranslation(translate);
		reorientate.SetToTranslation(pivot);
		rotation = reorientate.GetInverse() * rotate.MatrixX() * rotate.MatrixY() * rotate.MatrixZ() * reorientate;

		return translation * rotation;
	}
};

class drawOrder
{
public:
	drawOrder();
	~drawOrder();
	void SetTerminalVelocityTo(Vector3 vector);
	void CapVelocityToTerminal();
	void SetMaterial(const Material& mat);
	void SetVelocityTo(Vector3 newVelocity);
	void UpdateVelocity(const double deltaTime);
	void UpdateTo(const double deltaTime);
	void AddVoxel(float x, float y, float z, Vector3 position, Color color);
	void AddForce(Vector3 force);
	Vector3 GetAcceleration();
	Vector3 GetMomentum();
	void SetMomentumTo(Vector3 momentum);
	void GainMomentumFrom(drawOrder* draw, Vector3 momentumGain);
	void LoseMomentumTo(drawOrder* draw, Vector3 momentumLost);
	void Execute();
	float GetKinetic();
	void Render() const;
	void RenderPartial(const unsigned offset, const unsigned count) const;


	Mesh* geometry;
	Material material;
	unsigned drawMode;

	bool enableLight;
	float mass;
	float bounce;
	float staticFriction;
	float kineticFriction;
	Transformation transform;
	//this transformation will only apply to the parent and not it's children
	Transformation selfTransform;
	std::vector<drawOrder*> children;
	std::vector<Voxel> voxels;
	std::vector<Vector3> forces;
	Vector3 velocity;
	Vector3 terminalVelocity;
};