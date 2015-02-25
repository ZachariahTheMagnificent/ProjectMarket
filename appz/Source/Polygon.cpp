#include "Polygon.h"

Polygon::Polygon(const Vertex& initVertex1, const Vertex& initVertex2, const Vertex& initVertex3)
{
	Set(initVertex1, initVertex2, initVertex3);
}

Polygon::~Polygon()
{
}

void Polygon::Set(const Vertex& initVertex1, const Vertex& initVertex2, const Vertex& initVertex3)
{
	vertices[0] = initVertex1;
	vertices[1] = initVertex2;
	vertices[2] = initVertex3;
	CalculateNormal();
}

bool Polygon::NormalIsFacing(const Vertex& vert) const
{
	return true;
}

bool Polygon::OppositeNormalIsFacing(const Vertex& vert)
{
	normal = -normal;
	bool check = NormalIsFacing(vert);
	normal = -normal;
	return check;
}

void Polygon::CalculateNormal()
{
	Vector3 edge1(vertices[0].pos - vertices[1].pos);
	Vector3 edge2(vertices[0].pos - vertices[1].pos);
	normal = edge1.Cross(edge2);
}