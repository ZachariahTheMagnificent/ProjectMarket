#ifndef LOAD_OBJ_H
#define LOAD_OBJ_H

#include <vector>
#include <map>
#include "Vertex.h"
#include "Vector3.h"
#include "Directory.h"

//a more compressed version of Vertex that excludes the color member created to make indexing and finding similar vertices faster.
//struct packedvertex{
//	Vector3 position;
//	Vector3 normal;
//	TexCoord uv;
//	bool operator<(const packedvertex that) const
//	{
//		return memcmp((void*)this, (void*)&that, sizeof(packedvertex)) > 0;
//	};
//};

class ObjLoader
{
public:
	static bool LoadOBJ(
		std::wstring file_path,
		std::vector<Vertex>& out_vertices
	);

	////Indexes the vertices from the file
	//static void IndexVBO(
	//	std::vector<Vector3> & in_vertices,
	//	std::vector<TexCoord> & in_uvs,
	//	std::vector<Vector3> & in_normals,

	//	std::vector<unsigned> & out_indices,
	//	std::vector<Vertex> & out_vertices
	//);
};

#endif