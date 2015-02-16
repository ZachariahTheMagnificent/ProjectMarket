#ifndef VERTEX_H
#define VERTEX_H

#include"Vector3.h"

struct TexCoord
{
	float u, v;
	TexCoord(float u = 0, float v = 0)
	{
		Set(u, v);
	}
	void Set(float u, float v)
	{
		this->u = u;
		this->v = v;
	}
};

struct Color
{
	float r; 
	float g;
	float b;
	Color(float r = 1, float g = 1, float b = 1)
	{
		Set(r, g, b);
	}
	void Set(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

struct Vertex 
{
	Vector3 pos;
	Color color;
	Vector3 normal;
	TexCoord texCoord;
	bool operator< (const Vertex someOtherVertex) const
	{
		return memcmp((void*)this, (void*)&someOtherVertex, sizeof(Vertex)) > 0;
	};
};

#endif