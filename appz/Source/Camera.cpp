#include "Camera.h"
#include "Mtx44.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

bool Camera::IsLookingAt(const Vector3& point, const float halfAngle, const float cutoffDistance) const
{
	Vector3 pointFromCamera = point - ReturnPosition();
	float length = pointFromCamera.Length();
	pointFromCamera.Normalize();
	Vector3 target = GetTarget();
	float actualHalfAngle = abs(acos(pointFromCamera.Dot(target)));
	char buffer[128];
	sprintf(buffer, "%.3f, %.3f, %.3f, %.3f\n", pointFromCamera.x, pointFromCamera.y, pointFromCamera.z, length);
	std::cout << buffer << actualHalfAngle << std::endl;
	if(actualHalfAngle <= Math::DegreeToRadian(halfAngle) && length <= cutoffDistance)
	{
		return true;
	}
	return false;
}

void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	transform.translate = pos;
	transform.rotate.Set(0,90,0);
}

const Vector3 Camera::ReturnUp() const
{
	Vector3 up(0,1,0);

	up = transform.rotate.MatrixX() * transform.rotate.MatrixY() * transform.rotate.MatrixZ() * up;

	return up;
}

const Vector3& Camera::ReturnPosition() const
{
	return transform.translate;
}

Vector3 Camera::GetTarget() const
{
	Vector3 target(3, 0, 0);

	target = transform.rotate.MatrixX() * transform.rotate.MatrixY() * transform.rotate.MatrixZ() * target;
	return target.Normalized();
}

const Vector3 Camera::ReturnTarget() const
{
	Vector3 target(GetTarget());

	target += ReturnPosition();
	return target;
}

void Camera::Reset()
{
	transform.translate.SetZero();
	transform.rotate.Set(0,0,0);
}

void Camera::Update(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	Translate(pos.x, pos.y, pos.z);
}

void Camera::Rotate( const float x, const float y, const float z)
{
	Rotation rotate;
	rotate.Set(x, y, z);
	Rotate(rotate);
}

Rotation Camera::GetRotation() const
{
	return transform.rotate;
}

void Camera::Rotate(const Rotation rotate)
{
	static const float Z_LookLimit = 70;
	transform.rotate += rotate;
	if(transform.rotate.z > Z_LookLimit)
	{
		transform.rotate.z = Z_LookLimit;
	}
	else if(transform.rotate.z < -Z_LookLimit)
	{
		transform.rotate.z = -Z_LookLimit;
	}
}

void Camera::Translate( const float x, const float y, const float z)
{
	Vector3 translate;
	translate.Set(x, y, z);
	Translate(translate);
}

void Camera::Translate( const Vector3 translate)
{
	transform.translate += translate;
}

void Camera::Move( const float x, const float y, const float z)
{
	Vector3 translation;
	translation.Set(x,y,z);
	translation = transform.rotate.MatrixY() * translation;

	Translate(translation);
}

void Camera::Move(const Vector3 translate)
{
	Vector3 translation = translate;
	translation = transform.rotate.MatrixY() * translation;

	Translate(translation);
}

Mtx44 Camera::GetRotationMatrix(bool x, bool y, bool z) const
{
	Mtx44 rotationMatrix;
	rotationMatrix.SetToIdentity();
	if(x)
	{
		rotationMatrix = rotationMatrix * transform.rotate.MatrixX();
	}
	if(y)
	{
		rotationMatrix = rotationMatrix * transform.rotate.MatrixY();
	}
	if(z)
	{
		rotationMatrix = rotationMatrix * transform.rotate.MatrixZ();
	}
	return rotationMatrix;
}