#include "Camera.h"
#include "Mtx44.h"
/****************************************************************************/
/*!
\file Camera.cpp
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class used to help render a scene at a certain position and view
*/
/****************************************************************************/

/****************************************************************************/
/*!
\brief
empty default constructor
*/
/****************************************************************************/
Camera::Camera()
{
}
/****************************************************************************/
/*!
\brief
empty default destructer
*/
/****************************************************************************/
Camera::~Camera()
{
}
/****************************************************************************/
/*!
\brief
checks if the camera is looking at a certain point
\param point
		the point that will be checked against
\param halfAngle
		half of the angle that the angle between the camera viewing vector and the position of the point from the camera must be within for the function to return true(in degrees)
\param cutoffDistance
		the distance which the point must be within from the camera for the function to return true
*/
/****************************************************************************/
bool Camera::IsLookingAt(const Vector3& point, const float halfAngle, const float cutoffDistance) const
{
	Vector3 pointFromCamera = point - ReturnPosition();
	float length = pointFromCamera.Length();
	pointFromCamera.Normalize();
	Vector3 target = GetTarget();
	float actualHalfAngle = abs(acos(pointFromCamera.Dot(target)));
	if(actualHalfAngle <= Math::DegreeToRadian(halfAngle) && length <= cutoffDistance)
	{
		return true;
	}
	return false;
}
/****************************************************************************/
/*!
\brief
Initalizes the camera
\param pos
		what the position of the camera will be initialized to
\param target
		the point that the camera will be looking at
\param up
		initializes the up vector of the camera
*/
/****************************************************************************/
void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	transform.translate = pos;
	transform.rotate.Set(0,90,0);
}
/****************************************************************************/
/*!
\brief
Returns the camera's up vector
*/
/****************************************************************************/
const Vector3 Camera::ReturnUp() const
{
	Vector3 up(0,1,0);

	up = transform.rotate.MatrixX() * transform.rotate.MatrixY() * transform.rotate.MatrixZ() * up;

	return up;
}
/****************************************************************************/
/*!
\brief
Returns the canera's position
*/
/****************************************************************************/
const Vector3& Camera::ReturnPosition() const
{
	return transform.translate;
}
/****************************************************************************/
/*!
\brief
Returns the camera's target
*/
/****************************************************************************/
Vector3 Camera::GetTarget() const
{
	Vector3 target(3, 0, 0);

	target = transform.rotate.MatrixX() * transform.rotate.MatrixY() * transform.rotate.MatrixZ() * target;
	return target.Normalized();
}
/****************************************************************************/
/*!
\brief
Returns the camera's target in world space
*/
/****************************************************************************/
const Vector3 Camera::ReturnTarget() const
{
	Vector3 target(GetTarget());

	target += ReturnPosition();
	return target;
}
/****************************************************************************/
/*!
\brief
Resets the camera
*/
/****************************************************************************/
void Camera::Reset()
{
	transform.translate.SetZero();
	transform.rotate.Set(0,0,0);
}
/****************************************************************************/
/*!
\brief
Rotates the camera
\param x
		how much we want to rotate around the x-axis
\param y
		how much we want to rotate around the y-axis
\param z
		how much we want to rotate around the z-axis
*/
/****************************************************************************/
void Camera::Rotate( const float x, const float y, const float z)
{
	Rotation rotate;
	rotate.Set(x, y, z);
	Rotate(rotate);
}
/****************************************************************************/
/*!
\brief
Returns the camera's rotation
*/
/****************************************************************************/
Rotation Camera::GetRotation() const
{
	return transform.rotate;
}
/****************************************************************************/
/*!
\brief
Rotates the camera
\param rotate
		the value that we want to rotate the camera with
*/
/****************************************************************************/
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
/****************************************************************************/
/*!
\brief
Translates the camera
\param x
		how much we want to translate along the x-axis
\param y
		how much we want to translate along the y-axis
\param z
		how much we want to translate along the z-axis
*/
/****************************************************************************/
void Camera::Translate( const float x, const float y, const float z)
{
	Vector3 translate;
	translate.Set(x, y, z);
	Translate(translate);
}
/****************************************************************************/
/*!
\brief
Translates the camera
\param translate
		the value that we want to translate the camera with
*/
/****************************************************************************/
void Camera::Translate( const Vector3 translate)
{
	transform.translate += translate;
}
/****************************************************************************/
/*!
\brief
Moves the camera according to where it is facing
\param x
		how much we want to move the camera to it's sides
\param y
		how much we want to move the camera vertically
\param z
		how much we want to move the camera forwand and backward
*/
/****************************************************************************/
void Camera::Move( const float x, const float y, const float z)
{
	Vector3 translation;
	translation.Set(x,y,z);
	translation = transform.rotate.MatrixY() * translation;

	Translate(translation);
}
/****************************************************************************/
/*!
\brief
Moves the camera according to where it is facing
\param translate
		translate values for the move
*/
/****************************************************************************/
void Camera::Move(const Vector3 translate)
{
	Vector3 translation = translate;
	translation = transform.rotate.MatrixY() * translation;

	Translate(translation);
}
/****************************************************************************/
/*!
\brief
Returns the camera's rotation as a matrix
*/
/****************************************************************************/
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