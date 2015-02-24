#pragma once
#include "Vector3.h"
#include "Vertex.h"
#include "Mtx44.h"

class drawOrder;

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
	Color GetColor() const;
	Mtx44 GetRotationMatrix() const;
	Vector3 GetPosition() const;
	static float GetSize();
	Vector3 GetDistanceFrom(const Voxel& voxel) const;
	Voxel At(const double time);
	bool IsCollidingWith(const Voxel& voxel) const;
	bool IsBehind(const Voxel& voxel) const;
	bool IsInFrontOf(const Voxel& voxel) const;
	bool IsToTheLeftOf(const Voxel& voxel) const;
	bool IsToTheRightOf(const Voxel& voxel) const;
	bool IsAbove(const Voxel& voxel) const;
	bool IsBelow(const Voxel& voxel) const;
	bool operator==(const Voxel& voxel) const;
	void SetColorTo(const Color newColor);
	void ChangeVelocityTo(const Vector3 newVelocity, Voxel* TransferMomentumToThisVoxel = NULL);
	void SetPositionTo(const Vector3 newPosition);
	void AssignTo(drawOrder* newDraw);
	void ApplyCurrentMatrix();
	void ApplyToMatrix(Mtx44 matrix);
	void ResetToOrgin();
private:
	drawOrder* draw;
	Vector3 position;
	Vector3 displacement;
	Color color;
};