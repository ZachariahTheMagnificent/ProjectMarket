#pragma once
#include "Force.h"
#include "VoxelOctree.h"
#include "DrawOrder.h"

class CollisionBody
{
public:
	CollisionBody(std::wstring name = std::wstring(), drawOrder* draw = NULL, float mass = 0, float bounce = 0, float staticFriction = 0, float kineticFriction = 0);
	~CollisionBody();
	
	std::wstring GetName() const;
	void SetTerminalVelocityTo(Vector3 vector);
	float GetMass() const;
	void UpdateForcesTo(const double deltaTime);
	void UpdateVelocity(const double deltaTime);
	void UpdateTo(const double deltaTime);
	void ApplyFriction();
	void GainMomentumFrom(CollisionBody* draw, Vector3 momentumGain);
	const Vector3& GetVelocity() const;
	void LoseMomentumTo(CollisionBody* draw, Vector3 momentumLost);
	void AddForce(Vector3 force);
	void AddForce(Force force);
	Vector3 GetAcceleration();
	Vector3 GetMomentum();
	void SetMomentumTo(Vector3 momentum);
	void CapVelocityToTerminal();
	void SetMassTo(const float mass);
	void SetFrictionTo(const float staticz, const float kineticz);
	void GenerateVoxels();
	void SetNameAs(const std::wstring name);
	float GetKinetic();
	float GetMaxX() const;
	float GetMinX() const;
	float GetMaxY() const;
	float GetMinY() const;
	float GetMaxZ() const;
	float GetMinZ() const;
private:
	std::wstring name;
	drawOrder* draw;
	VoxelOctree* voxels;
	Vector3 velocity;
	std::vector<Force> forces;
	Vector3 terminalVelocity;
	float mass;
	float bounce;
	float staticFriction;
	float kineticFriction;
};