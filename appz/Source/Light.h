#ifndef _LIGHT_H
#define _LIGHT_H
/****************************************************************************/
/*!
\file Light.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class that contains light values
*/
/****************************************************************************/
#include "Vertex.h"
/****************************************************************************/
/*!
Struct Light:
\brief
contains light values
*/
/****************************************************************************/
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