
#include "Mesh.h"
#include "GL\glew.h"
#include "LoadTGA.h"

Mesh::Mesh(const std::wstring &meshName, std::vector<Vertex>& Vertex_buffer)
	:
name(meshName)
{
	nVerts = Vertex_buffer.size();
	vertices = Vertex_buffer;
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, Vertex_buffer.size() * sizeof(Vertex), &Vertex_buffer.front(), GL_STATIC_DRAW);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_vertexBuffer);
}

const std::wstring& Mesh::GetName() const
{
	return name;
}

std::vector<Voxel> Mesh::GenerateVoxels()
{
	std::vector<Voxel> voxels;
	const float sizeOfVoxel = Voxel::GetSize();
	//create a buffer to store the vertices that were transformed by the matrix
	std::vector<Vertex> temp_vertices;
	temp_vertices = vertices;
	std::vector<bool> VoxelGrid;
	int furthestLeft = INT_MAX;
	int furthestRight = INT_MIN;
	int furthestDown = INT_MAX;
	int furthestUp = INT_MIN;
	int furthestBack = INT_MAX;
	int furthestFront = INT_MIN;
	for(std::vector<Vertex>::iterator vertex = temp_vertices.begin(); vertex != temp_vertices.end(); ++vertex)
	{
		if(vertex->pos.x < furthestLeft)
		{
			furthestLeft = vertex->pos.x;
		}
		if(vertex->pos.x > furthestRight)
		{
			furthestRight = vertex->pos.x + 1;
		}
		if(vertex->pos.y < furthestDown)
		{
			furthestDown = vertex->pos.y;
		}
		if(vertex->pos.y > furthestUp)
		{
			furthestUp = vertex->pos.y + 1;
		}
		if(vertex->pos.z < furthestBack)
		{
			furthestBack = vertex->pos.z;
		}
		if(vertex->pos.z > furthestFront)
		{
			furthestFront = vertex->pos.z + 1;
		}
	}
	int lengthX(furthestRight - furthestLeft + 1);
	int lengthY(furthestUp - furthestDown + 1);
	int lengthZ(furthestFront - furthestBack + 1);
	VoxelGrid.resize(lengthX * lengthY * lengthZ);
	Vector3 voxelDisplacement(0 - furthestLeft, 0 - furthestDown, 0 - furthestBack);
	//for(std::vector<Vertex>::iterator vertex = vertices.begin(); vertex != vertices.end(); vertex += 3)
	//{
	//	Vector3 triangleVector1 = vertex->pos - (vertex + 1)->pos;
	//	Vector3 triangleVector2 = (vertex + 2)->pos - (vertex + 1)->pos;
	//	Vector3 normal = triangleVector1.Cross(triangleVector2);
	//}
	int areaXY = lengthX * lengthY;
	for(std::vector<Vertex>::iterator vertex = temp_vertices.begin(); vertex != temp_vertices.end();vertex+=3)
	{
		//create 2 vectors to represent the triangle
		Vector3 triangleVector1 = (vertex+1)->pos - vertex->pos;
		Vector3 triangleVector2 = (vertex+1)->pos - (vertex+2)->pos;
		Vector3 LongestVector;
		if(triangleVector1.Length() > triangleVector2.Length())
		{
			LongestVector = triangleVector1;
		}
		else
		{
			LongestVector = triangleVector2;
		}
		const unsigned steps = (LongestVector.Length() + 0.5) / sizeOfVoxel;
		for(Vector3 displacement1, displacement2, increment1 = triangleVector1 / steps, increment2 = triangleVector2 / steps; displacement1.Length() < triangleVector1.Length(); displacement1 += increment1, displacement2 += increment2)
		{
			//create a vector that we create our voxel in
			Vector3 point1 = vertex->pos + displacement1;
			Vector3 point2 = (vertex+2)->pos + displacement2;
			Vector3 voxelVector = point2 - point1;
			for(Vector3 displacement = voxelVector.Normalized() * (sizeOfVoxel*0.5), increment = voxelVector.Normalized() * sizeOfVoxel; displacement.Length() < voxelVector.Length(); displacement += increment)
			{
				Vector3 voxelPosition = point1 + displacement;

				//remove the floating point values
				voxelPosition.x = (int)(voxelPosition.x + voxelDisplacement.x + 0.5);
				voxelPosition.y = (int)(voxelPosition.y + voxelDisplacement.y + 0.5);
				voxelPosition.z = (int)(voxelPosition.z + voxelDisplacement.z + 0.5);

				
				int index = voxelPosition.x + voxelPosition.y * lengthX + voxelPosition.z * areaXY;
				VoxelGrid[index] = true;
			}
		}
	}
	for(int x = furthestLeft; x <= furthestRight; ++x)
	{
		for(int y = furthestDown; y <= furthestUp; ++x)
		{
			for(int z = furthestBack; z <= furthestFront; ++z)
			{
				if(VoxelGrid[(voxelDisplacement.x + x) + (voxelDisplacement.y + y) * lengthX + (voxelDisplacement.z + z) * areaXY])
				{
					Voxel temp;
					temp.SetPositionTo(Vector3(x,y,z));
					float red = rand();
					red = red - (int)red;
					float green = rand();
					green = green - (int)green;
					float blue = rand();
					blue = blue - (int)blue;
					temp.SetColorTo(Color(red,green,blue));
					voxels.push_back(temp);
				}
			}
		}
	}
	return voxels;
}

void Mesh::Render(unsigned textureID, unsigned mode)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Color)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Color) + sizeof(Vector3)));
	glDrawArrays(mode, 0, nVerts);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::SetColor(Color color)
{
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), &Vertex_buffer.front(), GL_STATIC_DRAW);
}

void Mesh::Render(unsigned offset, unsigned count, unsigned textureID, unsigned mode)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Color)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Color) + sizeof(Vector3)));
	glDrawArrays(mode, offset, count);

	glBindTexture(GL_TEXTURE_2D, 0);
}