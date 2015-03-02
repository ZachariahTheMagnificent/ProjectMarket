#pragma once
#include "Vector3.h"
#include "Vertex.h"
#include "Mtx44.h"

class Voxel
{
public:
	Voxel();
	~Voxel();
	float GetMaxX() const;
	float GetMinX() const;
	float GetMaxY() const;
	float GetMinY() const;
	float GetMaxZ() const;
	float GetMinZ() const;
	Color GetColor() const;
	const char& GetSolidness() const;
	Mtx44 GetRotationMatrix() const;
	Vector3 GetPosition() const;
	static float GetSize();
	Vector3 GetDistanceFrom(const Voxel& voxel) const;
	bool IsBehind(const Voxel& voxel) const;
	bool IsInFrontOf(const Voxel& voxel) const;
	bool IsToTheLeftOf(const Voxel& voxel) const;
	bool IsToTheRightOf(const Voxel& voxel) const;
	bool IsAbove(const Voxel& voxel) const;
	bool IsBelow(const Voxel& voxel) const;
	bool operator==(const Voxel& voxel) const;
	void SetColorTo(const Color newColor);
	void SetPositionTo(const Vector3 newPosition);
	void ApplyToMatrix(Mtx44 matrix);
	void ResetToOrgin();
private:
	Vector3 position;
	Vector3 displacement;
	Color color;
	char solidness;
};