#pragma once
#include "Vertex.h"

class Polygonn
{
public:
	Polygonn(const Vertex& initVertex1 = Vertex(), const Vertex& initVertex2 = Vertex(), const Vertex& initVertex3 = Vertex());
	~Polygonn();
	void Set(const Vertex& initVertex1 = Vertex(), const Vertex& initVertex2 = Vertex(), const Vertex& initVertex3 = Vertex());
	void CalculateNormal();
	bool NormalIsFacing(const Vertex& vert) const;
	bool OppositeNormalIsFacing(const Vertex& vert);
	bool Intersects(Polygonn& polygon) const;
	bool Intersects(Vector3& line, Vector3 displacement) const;
	Vertex const* ReturnFirstVertex() const;
	Vertex const* ReturnSecondVertex() const;
	Vertex const* ReturnLastVertex() const;
	void GetBounds(float*const returnFurthestLeft, float*const returnFurthestRight, float*const returnFurthestDown, float*const returnFurthestUp, float*const returnFurthestBack, float*const returnFurthestFront);
	const Vector3& GetNormal() const;
	const Vertex GetVertex1() const;
	const Vertex GetVertex2() const;
	const Vertex GetVertex3() const;
	void MoveAlongNormalBy(const float displacement);
	Polygonn Flipped();
private:
	Vertex vertex1, vertex2, vertex3;
	Vector3 normal;
};