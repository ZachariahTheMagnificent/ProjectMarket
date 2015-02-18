#pragma once
#include "Vector3.h"

struct drawOrder;

class Force
{
public:
	Force(const unsigned boundX = 0, const unsigned boundY = 0, const unsigned boundZ = 0, bool attract = false);
	~Force();
	Vector3 GetVector() const;
	void UpdateTo(const double deltaTime);
	void SetBoundsTo(const unsigned boundX, const unsigned boundY, const unsigned boundZ);
	void SetLifespanTo(float time);
	void SetVector(Vector3 vector);
	void ToggleAttraction();
	void SetToAttract();
	void SetToRepel();
	bool WillAffect(drawOrder& draw);
	void ApplyTo(drawOrder* draw);
	bool isDead() const;
private:
	Vector3 force;
	Vector3 position;
	unsigned boundX;
	unsigned boundY;
	unsigned boundZ;
	bool attract;
	float lifespan;
};