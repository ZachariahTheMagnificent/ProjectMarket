#include "Mesh.h"
#include "GL\glew.h"
#include "LoadTGA.h"

Mesh::Mesh(const std::wstring &meshName, std::vector<Vertex>& Vertex_buffer)
	:
name(meshName)
{
	nVerts = Vertex_buffer.size();
	polygons.reserve(nVerts/3);
	for(std::vector<Vertex>::iterator vert1 = Vertex_buffer.begin(); vert1 != Vertex_buffer.end(); vert1+=3)
	{
		if(!((vert1 + 2)->pos - (vert1 + 1)->pos).Cross(vert1->pos - (vert1 + 1)->pos).IsZero())
		{
			polygons.push_back(Polygonn(*vert1, *(vert1 + 1), *(vert1 + 2)));
		}
	}
	
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	std::vector<Vertex> buffz;
	for(std::vector<Polygonn>::iterator polygon = polygons.begin(), end = polygons.end(); polygon != end; ++polygon)
	{
		buffz.push_back(polygon->GetVertex1());
		buffz.push_back(polygon->GetVertex2());
		buffz.push_back(polygon->GetVertex3());
	}
	glBufferData(GL_ARRAY_BUFFER, Vertex_buffer.size() * sizeof(Vertex), &buffz.front(), GL_STATIC_DRAW);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_vertexBuffer);
}

const std::wstring& Mesh::GetName() const
{
	return name;
}

void Mesh::GetRanges(Range<int>& rangeX, Range<int>& rangeY, Range<int>& rangeZ)
{
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
	rangeX.Set(furthestLeft, furthestRight);
	rangeY.Set(furthestDown, furthestUp);
	rangeZ.Set(furthestBack, furthestFront);
}

VoxelOctree* Mesh::GenerateVoxel(VoxelOctree* tree) const
{
	for(std::vector<Polygonn>::const_iterator polygon = polygons.begin(); polygon != polygons.end(); ++polygon)
	{
		//create the 5 polygons that the voxels will be checked against
		Polygonn polygon1(*polygon);
		polygon1.MoveAlongNormalBy(-0.5);

		Polygonn polygon2(polygon->Flipped());
		polygon2.MoveAlongNormalBy(-0.5);

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
						Voxel voxel;
						voxel.SetSolidityTo(1);
						voxel.SetPositionTo(temp.pos);
						float red = rand();
						red = red - (int)red;
						float green = rand();
						green = green - (int)green;
						float blue = rand();
						blue = blue - (int)blue;
						voxel.SetColorTo(Color(red,green,blue));
						tree->AddVoxel(voxel);
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
		//const unsigned steps = (LongestVector.Length() + 0.5);
		//for(Vector3 displacement1, displacement2, increment1 = triangleVector1 / steps, increment2 = triangleVector2 / steps; displacement1.Length() < triangleVector1.Length(); displacement1 += increment1, displacement2 += increment2)
		//{
		//	create a vector that we create our voxel in
		//	Vector3 point1 = polygon->ReturnFirstVertex()->pos + displacement1;
		//	Vector3 point2 = polygon->ReturnLastVertex()->pos + displacement2;
		//	Vector3 voxelVector = point2 - point1;
		//	if(voxelVector.IsZero())
		//	{
		//		continue;
		//	}
		//	for(Vector3 displacement = voxelVector.Normalized() * (0.5), increment = voxelVector.Normalized(); displacement.Length() < voxelVector.Length(); displacement += increment)
		//	{
		//		Vector3 voxelPosition = point1 + displacement;

		//		remove the floating point values
		//		voxelPosition.x = (int)(voxelPosition.x + 0.5);
		//		voxelPosition.y = (int)(voxelPosition.y + 0.5);
		//		voxelPosition.z = (int)(voxelPosition.z + 0.5);

		//		Voxel voxel;
		//		voxel.SetSolidityTo(1);
		//		voxel.SetPositionTo(voxelPosition);
		//		float red = rand();
		//		red = red - (int)red;
		//		float green = rand();
		//		green = green - (int)green;
		//		float blue = rand();
		//		blue = blue - (int)blue;
		//		voxel.SetColorTo(Color(red,green,blue));

		//		
		//		tree->AddVoxel(voxel);
		//	}
		//}
	}
	return tree;
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