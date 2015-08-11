#ifndef MESH_H
#define MESH_H
/****************************************************************************/
/*!
\file Mesh.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class used to store VBO (vertex & color buffer) and polygons and generate voxels from them
*/
/****************************************************************************/
#include <string>
#include <vector>
#include "Mtx44.h"
#include "GL\glew.h"
#include "Polygon.h"
#include "VoxelOctree.h"

/******************************************************************************/
/*!
Class Mesh:
\brief
To store VBO (vertex & color buffer) and polygons and generate voxels from them
*/
/******************************************************************************/
class Mesh
{
public:
	Mesh(const std::wstring &meshName, std::vector<Vertex>& Vertex_buffer);
	~Mesh();
	const std::wstring& GetName() const;
	void Render( unsigned textureID = 0, unsigned mode = GL_TRIANGLES);
	//a function made to render only parts of the mesh
	void Render(unsigned offset, unsigned count, unsigned textureID, unsigned mode);
	void GetRanges(Range<int>& rangeX, Range<int>& rangeY, Range<int>& rangeZ);
	VoxelOctree* GenerateVoxel(VoxelOctree* tree) const;
private:
	const std::wstring name;
	unsigned m_vertexBuffer;
	std::vector<Polygonn> polygons;
	int nVerts;
};

#endif