#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include "Mtx44.h"
#include "GL\glew.h"
#include "Voxel.h"
#include "Polygon.h"

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
	void SetColor(Color color);
	std::vector<Voxel> GenerateVoxels();
private:
	const std::wstring name;
	unsigned m_vertexBuffer;
	std::vector<Polygon> polygons;
	int nVerts;
};

#endif