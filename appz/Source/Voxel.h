#pragma once
#include "Vector3.h"
#include "Vertex.h"

struct drawOrder;

class Voxel
{
public:
	Voxel();
	~Voxel();
	Vector3 GetVelocity() const;
	float GetMaxX() const;
	float GetMinX() const;
	float GetMaxY() const;
	float GetMinY() const;
	float GetMaxZ() const;
	float GetMinZ() const;
	Vector3 GetPosition() const;
	Vector3 GetSize() const;
	Vector3 GetDistanceFrom(const Voxel& voxel) const;
	bool IsCollidingWith(const Voxel& voxel) const;
	bool IsBehind(const Voxel& voxel) const;
	bool IsInFrontOf(const Voxel& voxel) const;
	bool IsToTheLeftOf(const Voxel& voxel) const;
	bool IsToTheRightOf(const Voxel& voxel) const;
	bool IsAbove(const Voxel& voxel) const;
	bool IsBelow(const Voxel& voxel) const;
	//bool DoCollisionWith(Voxel* voxel, const double dt);
	void SetSizeTo(const float x, const float y, const float z);
	void SetColorTo(const Color newColor);
	void ChangeVelocityTo(const Vector3 newVelocity, Voxel* TransferMomentumToThisVoxel = NULL);
	void SetPositionTo(const Vector3 newPosition);
	void AssignTo(drawOrder* newDraw);
	void UpdateTo(const double deltaTime);
private:
	drawOrder* draw;
	Vector3 position;
	float sizeX;
	float sizeY;
	float sizeZ;
	Color color;
};