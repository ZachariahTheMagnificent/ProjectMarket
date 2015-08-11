#pragma once
#include "Vector3.h"
/****************************************************************************/
/*!
\file Force.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class used to store and handle force information
*/
/****************************************************************************/

/****************************************************************************/
/*!
Class Force:
\brief
Used to store and handle force information
*/
/****************************************************************************/
class Force
{
public:
	Force(const Vector3 force = Vector3(), bool attract = false);
	~Force();
	Vector3 GetVector() const;
	void UpdateTo(const double deltaTime);
	void SetLifespanTo(float time);
	void SetVector(Vector3 vector);
	void ToggleAttraction();
	void SetToAttract();
	void SetToRepel();
	bool isDead() const;
private:
	Vector3 force;
	bool attract;
	float lifespan;
};