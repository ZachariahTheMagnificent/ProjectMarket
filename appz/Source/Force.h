#pragma once
#include "Vector3.h"

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