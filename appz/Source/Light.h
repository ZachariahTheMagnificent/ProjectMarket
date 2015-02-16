#ifndef _LIGHT_H
#define _LIGHT_H

#include "Vertex.h"

struct Light
{
	Vector3 position;
	Color color;
	float power;
	float kC, kL, kQ;
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;

	void Set(Vector3 position, Color color, float power, float kC, float kL, float kQ)
	{
		this->position = position;
		this->color = color;
		this->power = power;
		this->kC = kC;
		this->kL = kL;
		this->kQ = kQ;
	}
	Light()
	{
		Vector3 position;
		Color color;
		float power = 1.0f;
		float kC = 1.0f;
		float kL = 0.01f;
		float kQ = 0.001f;

		Set(position, color, power, kC, kL, kQ);
	}
	Light(Vector3 position, Color color, float power, float kC, float kL, float kQ)
	{
		Set(position, color, power, kC, kL, kQ);
	}
};

#endif