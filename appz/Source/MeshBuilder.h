#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H
/****************************************************************************/
/*!
\file MeshBuilder.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class that provides methods to generate mesh of different shapes
*/
/****************************************************************************/
#include "Mesh.h"
#include "Vertex.h"
#include "Custom Functions.h"

/******************************************************************************/
/*!
Class MeshBuilder:
\brief
Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::wstring &meshName, const float lengthX, const float lengthY, const float lengthZ);
	static Mesh* GenerateQuad(const std::wstring &meshName, const Color color, const float lengthX, const float lengthY);
	static Mesh* GenerateRepeatQuad(const std::wstring &meshName, const Color color, const float lengthX, const float lengthY);
	static Mesh* GenerateCube(const std::wstring &meshName, const Color color, const float lengthX, const float lengthY, const float lengthZ);
	static Mesh* GenerateSphere(const std::wstring &meshName, const Color color, const float radius, const int nSegments = 48, const int nRings = 48);
	static Mesh* GenerateCone(const std::wstring &meshName, const Color color, const float height, const float radius, const int nSlices = 32);
	static Mesh* GenerateCylinder(const std::wstring &meshName, const Color color, const float height, const float radius, const int nSlices = 32, const float thickness = 0);
	static Mesh* GenerateRing(const std::wstring &meshName, const Color color, const float radius, const float thickness, const int nSlices = 32);
	static Mesh* MeshBuilder::GenerateCircle(const std::wstring &meshName, const Color color, const float radius, const int nSlices = 32);
	static Mesh* GenerateOBJ(const std::wstring& name, const std::wstring &file_path);
	static Mesh* GenerateText(const std::wstring &file_path, unsigned numRow, unsigned numCol);
};

#endif