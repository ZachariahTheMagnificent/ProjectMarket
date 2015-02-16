#include <iostream>
#include <fstream>

#include "LoadOBJ.h"

bool ObjLoader::LoadOBJ(
		std::wstring file_path,
		std::vector<Vertex>& out_vertices
)
{
	std::ifstream fileStream(file_path, std::ios::binary);
	if(!fileStream.is_open())
	{
		std::cout << "Impossible to open " << file_path.c_str() << ". Are you in the right directory ?\n";
		return false;
	}

	std::vector<Vector3> temp_vertices;
	std::vector<TexCoord> temp_UVs;
	std::vector<Vector3> temp_normals;
	std::vector<int> vert_indices, uv_indices, normal_indices;

	while (!fileStream.eof())
	{
		char buf[256];
		fileStream.getline(buf, 256);

		//process vertex position
		if(strncmp("v ", buf, 2) == 0)
		{
			Vector3 vertex;
			sscanf_s((buf + 2), "%f%f%f", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}

		//process texcoord
		else if(strncmp("vt ", buf, 3) == 0)
		{
			TexCoord UV;
			sscanf_s((buf + 3), "%f%f", &UV.u, &UV.v);
			temp_UVs.push_back(UV);
		}

		//process normal
		else if(strncmp("vn ", buf, 3) == 0)
		{
			Vector3 normal;
			sscanf_s((buf + 3), "%f%f%f", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}

		//process face
		else if(strncmp("f ", buf, 2) == 0)
		{
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];

			int matches = sscanf_s((buf + 2), "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", 
			&vertexIndex[0], &uvIndex[0], &normalIndex[0], 
			&vertexIndex[1], &uvIndex[1], &normalIndex[1], 
			&vertexIndex[2], &uvIndex[2], &normalIndex[2], 
			&vertexIndex[3], &uvIndex[3], &normalIndex[3]);

			if(matches == 9) //triangle
			{
				vert_indices.push_back(vertexIndex[0]);
				vert_indices.push_back(vertexIndex[1]);
				vert_indices.push_back(vertexIndex[2]);

				uv_indices.push_back(uvIndex[0]);
				uv_indices.push_back(uvIndex[1]);
				uv_indices.push_back(uvIndex[2]);

				normal_indices.push_back(normalIndex[0]);
				normal_indices.push_back(normalIndex[1]);
				normal_indices.push_back(normalIndex[2]);
			}
			if(matches == 12) //quad
			{
				//triangle #1
				vert_indices.push_back(vertexIndex[0]);
				vert_indices.push_back(vertexIndex[1]);
				vert_indices.push_back(vertexIndex[2]);
				uv_indices.push_back(uvIndex[0]);
				uv_indices.push_back(uvIndex[1]);
				uv_indices.push_back(uvIndex[2]);
				normal_indices.push_back(normalIndex[0]);
				normal_indices.push_back(normalIndex[1]);
				normal_indices.push_back(normalIndex[2]);

				//triangle #1
				vert_indices.push_back(vertexIndex[2]);
				vert_indices.push_back(vertexIndex[3]);
				vert_indices.push_back(vertexIndex[0]);
				uv_indices.push_back(uvIndex[2]);
				uv_indices.push_back(uvIndex[3]);
				uv_indices.push_back(uvIndex[0]);
				normal_indices.push_back(normalIndex[2]);
				normal_indices.push_back(normalIndex[3]);
				normal_indices.push_back(normalIndex[0]);
			}
		}
	}
	fileStream.close();

	// For each vertex of each triangle, after fileStream.close()
	for(unsigned i = 0; i < vert_indices.size(); ++i)
	{
		// Get the indices of its attributes
		unsigned int vertexIndex = vert_indices[i];
		unsigned int uvIndex = uv_indices[i];
		unsigned int normalIndex = normal_indices[i];
		
		// Get the attributes thanks to the index
		Vector3 vertex = temp_vertices[vertexIndex - 1];
		TexCoord uv = temp_UVs[uvIndex - 1];
		Vector3 normal = temp_normals[normalIndex - 1];
		
		// Put the attributes in buffers
		Vertex v = {vertex, Color(), normal, uv};
		out_vertices.push_back(v);
	}

	return true;
}

//void ObjLoader::IndexVBO(
//	std::vector<Vector3>& in_vertices,
//	std::vector<TexCoord>& in_uvs,
//	std::vector<Vector3>& in_normals,
//
//	std::vector<unsigned>& out_indices,
//	std::vector<Vertex>& out_vertices
//)
//{
//	std::map<packedvertex,unsigned short> VertIndex;
//
//	// For each input vertex
//	for(unsigned int i = 0; i < in_vertices.size(); ++i) 
//	{
//		packedvertex packedvert = {in_vertices[i], in_normals[i] , in_uvs[i]};
//
//		// Try to find a similar vertex in our current output
//		std::map<packedvertex, unsigned short>::iterator result = VertIndex.find(packedvert);
//
//		if ( result != VertIndex.end() )
//		{ 
//			// A similar vertex is already in the VBO, use it instead !
//			out_indices.push_back( result->second );
//		}
//		else
//		{ 
//			// If not, it needs to be added in the output data.
//			Vertex vert = {in_vertices[i], Color(1, 1, 1), in_normals[i] , in_uvs[i]};
//			unsigned newindex = (unsigned)out_vertices.size() - 1;
//
//			out_vertices.push_back(vert);
//			out_indices.push_back( newindex );
//
//			VertIndex[ packedvert ] = newindex;
//		}
//	}
//}