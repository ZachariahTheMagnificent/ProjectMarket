
#include "Mesh.h"
#include "GL\glew.h"
#include "LoadTGA.h"

Mesh::Mesh(const std::wstring &meshName, std::vector<Vertex>& Vertex_buffer)
	:
name(meshName)
{
	nVerts = Vertex_buffer.size();
	polygons.reserve(nVerts/3);
	for(std::vector<Vertex>::iterator vert1 = Vertex_buffer.begin(),vert2 = vert1 + 1,vert3 = vert2 + 1; vert3 != Vertex_buffer.end(); ++vert1, ++vert2, ++vert3)
	{
		if(!(vert1->pos - vert2->pos).Cross(vert3->pos - vert2->pos).IsZero())
		{
			polygons.push_back(Polygonn(*vert1, *vert2, *vert3));
		}
	}
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
	const int sizeOfVoxel = Voxel::GetSize();
	std::vector<bool> VoxelGrid;
	int furthestLeft = INT_MAX;
	int furthestRight = INT_MIN;
	int furthestDown = INT_MAX;
	int furthestUp = INT_MIN;
	int furthestBack = INT_MAX;
	int furthestFront = INT_MIN;

	//loop through all our vertices
	for(std::vector<Polygonn>::iterator polygon = polygons.begin(), end = polygons.end(); polygon != end; ++polygon)
	{
		Vertex const* vert = polygon->ReturnLastVertex();
		for(Vertex const* vertex = polygon->ReturnFirstVertex(); vertex != vert; ++vertex)
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
	}
	//increase the range by 1 to accomadate for all vertices in the grid
	int lengthX(furthestRight - furthestLeft + 1);
	int lengthY(furthestUp - furthestDown + 1);
	int lengthZ(furthestFront - furthestBack + 1);
	VoxelGrid.resize(lengthX * lengthY * lengthZ);
	Vector3 voxelDisplacement(0 - furthestLeft, 0 - furthestDown, 0 - furthestBack);
	int areaXY = lengthX * lengthY;
	for(std::vector<Polygonn>::iterator polygon = polygons.begin(); polygon != polygons.end(); ++polygon)
	{
		//create the 5 polygons that the voxels will be checked against
		Polygonn polygon1(*polygon);
		polygon1.MoveAlongNormalBy(-1);

		Polygonn polygon2(polygon->Flipped());
		polygon2.MoveAlongNormalBy(-1);

		Polygonn polygon3(*polygon1.ReturnFirstVertex(), *polygon1.ReturnLastVertex(), *polygon2.ReturnSecondVertex());
		Polygonn polygon4(*polygon2.ReturnFirstVertex(), *polygon2.ReturnLastVertex(), *polygon1.ReturnSecondVertex());
		Polygonn polygon5(*polygon1.ReturnSecondVertex(), *polygon2.ReturnLastVertex(), *polygon2.ReturnSecondVertex());
		float furthestLeft, furthestRight, furthestDown, furthestUp, furthestBack, furthestFront;

		polygon->GetBounds(&furthestLeft, &furthestRight, &furthestDown, &furthestUp, &furthestBack, &furthestFront);
		furthestLeft = (int)furthestLeft;
		furthestRight = (int)(furthestRight + 0.5);
		furthestDown = (int)furthestDown;
		furthestUp = (int)(furthestUp + 0.5);
		furthestBack = (int)furthestBack;
		furthestFront = (int)(furthestFront + 0.5);
		for(int z = furthestBack, endZ = furthestFront + 1; z <= endZ; ++z)
		{
			for(int y = furthestDown, endY = furthestUp + 1; y <= endY; ++y)
			{
				for(int x = furthestLeft, endX = furthestRight + 1; x <= endX; ++x)
				{
					Vertex temp;
					temp.pos.Set(x,y,z);
					if(polygon1.NormalIsFacing(temp) && polygon2.NormalIsFacing(temp) && polygon3.NormalIsFacing(temp) && polygon4.NormalIsFacing(temp) && polygon5.NormalIsFacing(temp))
					{
						Vector3 voxelPosition(voxelDisplacement + temp.pos);
						voxelPosition.x = (int)(voxelPosition.x + 0.5);
						voxelPosition.y = (int)(voxelPosition.y + 0.5);
						voxelPosition.z = (int)(voxelPosition.z + 0.5);
						int index = voxelPosition.x + voxelPosition.y * lengthX + voxelPosition.z * areaXY;
						if(VoxelGrid[index] == false)
						{
							Voxel voxel;
							voxel.SetPositionTo(temp.pos);
							float red = rand();
							red = red - (int)red;
							float green = rand();
							green = green - (int)green;
							float blue = rand();
							blue = blue - (int)blue;
							voxel.SetColorTo(Color(red,green,blue));
							voxels.push_back(voxel);
							VoxelGrid[index] = true;
						}
					}
				}
			}
		}
		////create 2 vectors to represent the triangle
		//Vector3 triangleVector1 = polygon->ReturnSecondVertex()->pos - polygon->ReturnFirstVertex()->pos;
		//Vector3 triangleVector2 = polygon->ReturnSecondVertex()->pos - polygon->ReturnLastVertex()->pos;
		//Vector3 LongestVector;
		//if(triangleVector1.Length() > triangleVector2.Length())
		//{
		//	LongestVector = triangleVector1;
		//}
		//else
		//{
		//	LongestVector = triangleVector2;
		//}
		//const unsigned steps = (LongestVector.Length() + 0.5) / sizeOfVoxel;
		//for(Vector3 displacement1, displacement2, increment1 = triangleVector1 / steps, increment2 = triangleVector2 / steps; displacement1.Length() < triangleVector1.Length(); displacement1 += increment1, displacement2 += increment2)
		//{
		//	//create a vector that we create our voxel in
		//	Vector3 point1 = polygon->ReturnFirstVertex()->pos + displacement1;
		//	Vector3 point2 = polygon->ReturnLastVertex()->pos + displacement2;
		//	Vector3 voxelVector = point2 - point1;
		//	if(voxelVector.IsZero())
		//	{
		//		continue;
		//	}
		//	for(Vector3 displacement = voxelVector.Normalized() * (sizeOfVoxel*0.5), increment = voxelVector.Normalized() * sizeOfVoxel; displacement.Length() < voxelVector.Length(); displacement += increment)
		//	{
		//		Vector3 voxelPosition = point1 + displacement;

		//		//remove the floating point values
		//		voxelPosition.x = (int)(voxelPosition.x + voxelDisplacement.x + 0.5);
		//		voxelPosition.y = (int)(voxelPosition.y + voxelDisplacement.y + 0.5);
		//		voxelPosition.z = (int)(voxelPosition.z + voxelDisplacement.z + 0.5);

		//		
		//		int index = voxelPosition.x + voxelPosition.y * lengthX + voxelPosition.z * areaXY;
		//		VoxelGrid[index] = true;
		//	}
		//}
	}

	//for(int z = furthestBack; z <= furthestFront; ++z)
	//{
	//	for(int y = furthestDown; y <= furthestUp; ++y)
	//	{
	//		for(int x = furthestLeft; x <= furthestRight; ++x)
	//		{
	//			if(VoxelGrid[(voxelDisplacement.x + x) + (voxelDisplacement.y + y) * lengthX + (voxelDisplacement.z + z) * areaXY])
	//			{
	//				Voxel temp;
	//				temp.SetPositionTo(Vector3(x,y,z));
	//				float red = rand();
	//				red = red - (int)red;
	//				float green = rand();
	//				green = green - (int)green;
	//				float blue = rand();
	//				blue = blue - (int)blue;
	//				temp.SetColorTo(Color(red,green,blue));
	//				voxels.push_back(temp);
	//			}
	//		}
	//	}
	//}
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