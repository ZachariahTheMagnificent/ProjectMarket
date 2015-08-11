#include "Polygon.h"
/****************************************************************************/
/*!
\file Polygon.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class used to see if a value is within a certain range
*/
/****************************************************************************/

/****************************************************************************/
/*!
\brief
Default constructor
\param initVertex1
initializes the first vertex
\param initVertex2
initializes the second vertex
\param initVertex3
initializes the first vertex
*/
/****************************************************************************/
Polygonn::Polygonn(const Vertex& initVertex1, const Vertex& initVertex2, const Vertex& initVertex3)
{
	Set(initVertex1, initVertex2, initVertex3);
}
/****************************************************************************/
/*!
\brief
default destructor
*/
/****************************************************************************/
Polygonn::~Polygonn()
{
}
/****************************************************************************/
/*!
\brief
Checks if the polygon intersects with teh given polygon
\param polygon
		polygon to be checked together with
*/
/****************************************************************************/
bool Polygonn::Intersects(Polygonn& polygon) const
{
	return true;
}
/****************************************************************************/
/*!
\brief
Checks if a given line intersects the polygon
\param line
		the gradient of the line to be checked against
\param displacement
		the displacement of the line to be checked against
*/
/****************************************************************************/
bool Polygonn::Intersects(Vector3& line, Vector3 displacement) const
{
	float distance = -normal.x*vertex1.pos.x - normal.y*vertex1.pos.y - normal.z*vertex1.pos.z;
	float equation = (-displacement.x*normal.x - displacement.y*normal.y - displacement.z*normal.z - distance)/(line.x*normal.x + line.y*normal.y + line.z*normal.z);
	return true;
}
/****************************************************************************/
/*!
\brief
Set function
\param initVertex1
initializes the first vertex
\param initVertex2
initializes the second vertex
\param initVertex3
initializes the first vertex
*/
/****************************************************************************/
void Polygonn::Set(const Vertex& initVertex1, const Vertex& initVertex2, const Vertex& initVertex3)
{
	vertex1 = initVertex1;
	vertex2 = initVertex2;
	vertex3 = initVertex3;
	CalculateNormal();
}
/****************************************************************************/
/*!
\brief
Checks if the normal of the polygon is facing a vertex
*/
/****************************************************************************/
bool Polygonn::NormalIsFacing(const Vertex& vert) const
{
	//Vector3 testVec = vert.pos - vertex1.pos;
	//float angle = cosh(testVec.Dot(normal)/(testVec.Length() * normal.Length()));
	//if(angle > Math::HALF_PI)
	//{
	//	return false;
	//}
	float distance = -normal.x*vertex1.pos.x - normal.y*vertex1.pos.y - normal.z*vertex1.pos.z;
	float test = normal.x*vertex2.pos.x + normal.y*vertex2.pos.y + normal.z*vertex2.pos.z + distance;
	float equation = normal.x*vert.pos.x + normal.y*vert.pos.y + normal.z*vert.pos.z + distance;
	if(equation <= 0)
	{
		return false;
	}
	return true;
}
/****************************************************************************/
/*!
\brief
Checks if the normal of the polygon is facing the opposite direction of a vertex
*/
/****************************************************************************/
bool Polygonn::OppositeNormalIsFacing(const Vertex& vert) const
{
	Vector3 testNormal = -normal;
	float distance = -testNormal.x*vertex1.pos.x - testNormal.y*vertex1.pos.y - testNormal.z*vertex1.pos.z;
	float equation = testNormal.x*vert.pos.x + testNormal.y*vert.pos.y + testNormal.z*vert.pos.z + distance;
	if(equation <= 0)
	{
		return false;
	}
	return true;
}
/****************************************************************************/
/*!
\brief
Calculates the polygon's normal
*/
/****************************************************************************/
void Polygonn::CalculateNormal()
{
	Vector3 edge1(vertex1.pos - vertex2.pos);
	Vector3 edge2(vertex3.pos - vertex2.pos);
	normal = edge1.Cross(edge2).Normalized();
}
/****************************************************************************/
/*!
\brief
Get the bounds of the polygon
\param returnFurthestLeft
		a pointer to the location to store the polygon's furthest left
\param returnFurthestRight
		a pointer to the location to store the polygon's furthest right
\param returnFurthestDown
		a pointer to the location to store the polygon's furthest down
\param returnFurthestUp
		a pointer to the location to store the polygon's furthest up
\param returnFurthestBack
		a pointer to the location to store the polygon's furthest back
\param returnFurthestFront
		a pointer to the location to store the polygon's furthest front
*/
/****************************************************************************/
void Polygonn::GetBounds(float*const returnFurthestLeft, float*const returnFurthestRight, float*const returnFurthestDown, float*const returnFurthestUp, float*const returnFurthestBack, float*const returnFurthestFront) const
{
	//range for x
	if(vertex1.pos.x <= vertex2.pos.x && vertex1.pos.x <= vertex3.pos.x)
	{
		*returnFurthestLeft = vertex1.pos.x;
	}
	else if(vertex2.pos.x <= vertex1.pos.x && vertex2.pos.x <= vertex3.pos.x)
	{
		*returnFurthestLeft = vertex2.pos.x;
	}
	else if(vertex3.pos.x <= vertex1.pos.x && vertex3.pos.x <= vertex2.pos.x)
	{
		*returnFurthestLeft = vertex3.pos.x;
	}

	if(vertex1.pos.x >= vertex2.pos.x && vertex1.pos.x >= vertex3.pos.x)
	{
		*returnFurthestRight = vertex1.pos.x;
	}
	else if(vertex2.pos.x >= vertex1.pos.x && vertex2.pos.x >= vertex3.pos.x)
	{
		*returnFurthestRight = vertex2.pos.x;
	}
	else if(vertex3.pos.x >= vertex1.pos.x && vertex3.pos.x >= vertex2.pos.x)
	{
		*returnFurthestRight = vertex3.pos.x;
	}
	
	//range for y
	if(vertex1.pos.y <= vertex2.pos.y && vertex1.pos.y <= vertex3.pos.y)
	{
		*returnFurthestDown = vertex1.pos.y;
	}
	else if(vertex2.pos.y <= vertex1.pos.y && vertex2.pos.y <= vertex3.pos.y)
	{
		*returnFurthestDown = vertex2.pos.y;
	}
	else if(vertex3.pos.y <= vertex1.pos.y && vertex3.pos.y <= vertex2.pos.y)
	{
		*returnFurthestDown = vertex3.pos.y;
	}

	if(vertex1.pos.y >= vertex2.pos.y && vertex1.pos.y >= vertex3.pos.y)
	{
		*returnFurthestUp = vertex1.pos.y;
	}
	else if(vertex2.pos.y >= vertex1.pos.y && vertex2.pos.y >= vertex3.pos.y)
	{
		*returnFurthestUp = vertex2.pos.y;
	}
	else if(vertex3.pos.y >= vertex1.pos.y && vertex3.pos.y >= vertex2.pos.y)
	{
		*returnFurthestUp = vertex3.pos.y;
	}

	//range for z
	if(vertex1.pos.z <= vertex2.pos.z && vertex1.pos.z <= vertex3.pos.z)
	{
		*returnFurthestBack = vertex1.pos.z;
	}
	else if(vertex2.pos.z <= vertex1.pos.z && vertex2.pos.z <= vertex3.pos.z)
	{
		*returnFurthestBack = vertex2.pos.z;
	}
	else if(vertex3.pos.z <= vertex1.pos.z && vertex3.pos.z <= vertex2.pos.z)
	{
		*returnFurthestBack = vertex3.pos.z;
	}

	if(vertex1.pos.z >= vertex2.pos.z && vertex1.pos.z >= vertex3.pos.z)
	{
		*returnFurthestFront = vertex1.pos.z;
	}
	else if(vertex2.pos.z >= vertex1.pos.z && vertex2.pos.z >= vertex3.pos.z)
	{
		*returnFurthestFront = vertex2.pos.z;
	}
	else if(vertex3.pos.z >= vertex1.pos.z && vertex3.pos.z >= vertex2.pos.z)
	{
		*returnFurthestFront = vertex3.pos.z;
	}
}
/****************************************************************************/
/*!
\brief
Returns the polygon's normal
*/
/****************************************************************************/
const Vector3& Polygonn::GetNormal() const
{
	return normal;
}
/****************************************************************************/
/*!
\brief
Returns the polygon's first vertex
*/
/****************************************************************************/
const Vertex& Polygonn::GetVertex1() const
{
	return vertex1;
}
/****************************************************************************/
/*!
\brief
Returns the polygon's second vertex
*/
/****************************************************************************/
const Vertex& Polygonn::GetVertex2() const
{
	return vertex2;
}
/****************************************************************************/
/*!
\brief
Returns the polygon's third vertex
*/
/****************************************************************************/
const Vertex& Polygonn::GetVertex3() const
{
	return vertex3;
}
/****************************************************************************/
/*!
\brief
Move the polygon along it's normal
\param displacement
		the offset to move the polygon with
*/
/****************************************************************************/
void Polygonn::MoveAlongNormalBy(const float displacement)
{
	Vector3 vectorDisplacement = normal * displacement;

	vertex1.pos += vectorDisplacement;
	vertex2.pos += vectorDisplacement;
	vertex3.pos += vectorDisplacement;
}
/****************************************************************************/
/*!
\brief
Returns a copy of itself flipped
*/
/****************************************************************************/
Polygonn Polygonn::Flipped() const
{
	return Polygonn(vertex1, vertex3, vertex2);
}