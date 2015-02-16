#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "DrawOrder.h"

class Camera
{
public:
	Camera();
	~Camera();
	const Vector3 ReturnUp() const;
	const Vector3 ReturnPosition() const;
	const Vector3 ReturnTarget() const;
	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Reset();
	Rotation GetRotation() const;
	Mtx44 GetRotationMatrix(bool x, bool y, bool z) const;
	void Update(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Rotate(const float x, const float y, const float z);
	void Rotate(const Rotation rotate);
	void Translate(const float x, const float y, const float z);
	void Translate(const Vector3 translate);
	void Move(const float x, const float y, const float z);
	void Move(const Vector3 translate);
private:
	Vector3 InnitUp;
	Transformation transform;
};

#endif