#pragma once
#include "Vector3.h"
#include "Vertex.h"
#include "Mtx44.h"
/****************************************************************************/
/*!
\file Voxel.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class used to store and handle voxel information
*/
/****************************************************************************/

/****************************************************************************/
/*!
Class Voxel:
\brief
Used to store and handle voxel information
*/
/****************************************************************************/
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
	void SetSolidityTo(const unsigned char solidity);
private:
	Vector3 position;
	Color color;
	unsigned char solidness;
};