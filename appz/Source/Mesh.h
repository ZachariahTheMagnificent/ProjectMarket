#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include "Mtx44.h"
#include "GL\glew.h"
#include "Polygon.h"
#include "VoxelOctree.h"

/******************************************************************************/
/*!
		Class Mesh:
\brief	To store VBO (vertex & color buffer) and IBO (index buffer)
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
	void SetColor(Color color);
	VoxelOctree* GenerateVoxel(VoxelOctree* tree) const;
private:
	const std::wstring name;
	unsigned m_vertexBuffer;
	std::vector<Polygonn> polygons;
	int nVerts;
};

#endif