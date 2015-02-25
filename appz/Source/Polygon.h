#pragma once
#include "Vertex.h"

class Polygon
{
	Polygon(const Vertex& initVertex1 = Vertex(), const Vertex& initVertex2 = Vertex(), const Vertex& initVertex3 = Vertex());
	~Polygon();
	void Set(const Vertex& initVertex1 = Vertex(), const Vertex& initVertex2 = Vertex(), const Vertex& initVertex3 = Vertex());
	void CalculateNormal();
	bool NormalIsFacing(const Vertex& vert) const;
	bool OppositeNormalIsFacing(const Vertex& vert);
private:
	Vertex vertices[3];
	Vector3 normal;
};