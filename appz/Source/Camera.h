#pragma once
/****************************************************************************/
/*!
\file Camera.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class used to help render a scene at a certain position and view
*/
/****************************************************************************/
#include "Vector3.h"
#include "DrawOrder.h"
/****************************************************************************/
/*!
Class Camera:
\brief
Used to help render a scene at a certain position and view
*/
/****************************************************************************/
class Camera
{
public:
	Camera();
	~Camera();
	const Vector3 ReturnUp() const;
	const Vector3& ReturnPosition() const;
	const Vector3 ReturnTarget() const;
	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Reset();
	Rotation GetRotation() const;
	Mtx44 GetRotationMatrix(bool x, bool y, bool z) const;
	Vector3 GetTarget() const;
	void Rotate(const float x, const float y, const float z);
	void Rotate(const Rotation rotate);
	void Translate(const float x, const float y, const float z);
	void Translate(const Vector3 translate);
	void Move(const float x, const float y, const float z);
	void Move(const Vector3 translate);
	bool IsLookingAt(const Vector3& point, const float halfAngle, const float cutoffDistance) const;
private:
	Vector3 InnitUp;
	Transformation transform;
};