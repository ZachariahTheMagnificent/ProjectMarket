#pragma once
/****************************************************************************/
/*!
\file Polygon.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class used store and handle polygon values
*/
/****************************************************************************/
#include "Vertex.h"
/****************************************************************************/
/*!
Class Polygonn:
\brief
Stores and handles polygon values
*/
/****************************************************************************/
class Polygonn
{
public:
	Polygonn(const Vertex& initVertex1 = Vertex(), const Vertex& initVertex2 = Vertex(), const Vertex& initVertex3 = Vertex());
	~Polygonn();
	void Set(const Vertex& initVertex1 = Vertex(), const Vertex& initVertex2 = Vertex(), const Vertex& initVertex3 = Vertex());
	void CalculateNormal();
	bool NormalIsFacing(const Vertex& vert) const;
	bool OppositeNormalIsFacing(const Vertex& vert) const;
	bool Intersects(Polygonn& polygon) const;
	bool Intersects(Vector3& line, Vector3 displacement) const;
	void GetBounds(float*const returnFurthestLeft, float*const returnFurthestRight, float*const returnFurthestDown, float*const returnFurthestUp, float*const returnFurthestBack, float*const returnFurthestFront) const;
	const Vector3& GetNormal() const;
	const Vertex& GetVertex1() const;
	const Vertex& GetVertex2() const;
	const Vertex& GetVertex3() const;
	void MoveAlongNormalBy(const float displacement);
	Polygonn Flipped() const;
private:
	Vertex vertex1, vertex2, vertex3;
	Vector3 normal;
};