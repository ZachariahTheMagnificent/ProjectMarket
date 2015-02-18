#include "MeshBuilder.h"
#include <GL\glew.h>
#include "LoadOBJ.h"

Mesh* MeshBuilder::GenerateAxes(const std::wstring &meshName, const float lengthX, const float lengthY, const float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(-lengthX/2, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX/2, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, -lengthY/2, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, lengthY/2, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, -lengthZ/2);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, lengthZ/2);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	Mesh* mesh = new Mesh(meshName, vertex_buffer_data);

	return mesh;
}

Mesh* MeshBuilder::GenerateQuad(const std::wstring &meshName, const Color color, const float lengthX, const float lengthY)
{
	std::vector<Vertex> vertex_buffer_data;
	vertex_buffer_data.resize(4);

	vertex_buffer_data[0].pos.Set(lengthX/2,0,lengthY/2);
	vertex_buffer_data[1].pos.Set(-lengthX/2,0,lengthY/2);
	vertex_buffer_data[2].pos.Set(lengthX/2,0,-lengthY/2);
	vertex_buffer_data[3].pos.Set(-lengthX/2,0,-lengthY/2);

	vertex_buffer_data[0].normal.Set(0,1,0);
	vertex_buffer_data[1].normal.Set(0,1,0);
	vertex_buffer_data[2].normal.Set(0,1,0);
	vertex_buffer_data[3].normal.Set(0,1,0);

	vertex_buffer_data[3].texCoord.Set(1, 1);
	vertex_buffer_data[1].texCoord.Set(0, 1);
	vertex_buffer_data[2].texCoord.Set(1, 0);
	vertex_buffer_data[0].texCoord.Set(0, 0);

	for(std::vector<Vertex>::iterator vert = vertex_buffer_data.begin(); vert != vertex_buffer_data.end(); vert++)
	{
		vert->color = color;
	}

	std::vector<Vertex> actual_vertex_buffer;
	actual_vertex_buffer.resize(6);
	actual_vertex_buffer[0] = vertex_buffer_data[2];
	actual_vertex_buffer[1] = vertex_buffer_data[1];
	actual_vertex_buffer[2] = vertex_buffer_data[0];
	actual_vertex_buffer[3] = vertex_buffer_data[3];
	actual_vertex_buffer[4] = vertex_buffer_data[1];
	actual_vertex_buffer[5] = vertex_buffer_data[2];

	Mesh *mesh = new Mesh(meshName, actual_vertex_buffer);

	return mesh;
}

Mesh* MeshBuilder::GenerateRepeatQuad(const std::wstring &meshName, const Color color, const float lengthX, const float lengthY)
{
	std::vector<Vertex> vertex_buffer_data;
	vertex_buffer_data.resize(4);

	vertex_buffer_data[0].pos.Set(lengthX/2,0,lengthY/2);
	vertex_buffer_data[1].pos.Set(-lengthX/2,0,lengthY/2);
	vertex_buffer_data[2].pos.Set(lengthX/2,0,-lengthY/2);
	vertex_buffer_data[3].pos.Set(-lengthX/2,0,-lengthY/2);

	vertex_buffer_data[0].normal.Set(0,1,0);
	vertex_buffer_data[1].normal.Set(0,1,0);
	vertex_buffer_data[2].normal.Set(0,1,0);
	vertex_buffer_data[3].normal.Set(0,1,0);

	vertex_buffer_data[3].texCoord.Set(50, 50);
	vertex_buffer_data[1].texCoord.Set(0, 50);
	vertex_buffer_data[2].texCoord.Set(50, 0);
	vertex_buffer_data[0].texCoord.Set(0, 0);

	for(std::vector<Vertex>::iterator vert = vertex_buffer_data.begin(); vert != vertex_buffer_data.end(); vert++)
	{
		vert->color = color;
	}

	std::vector<Vertex> actual_vertex_buffer;
	actual_vertex_buffer.resize(6);
	actual_vertex_buffer[0] = vertex_buffer_data[2];
	actual_vertex_buffer[1] = vertex_buffer_data[1];
	actual_vertex_buffer[2] = vertex_buffer_data[0];
	actual_vertex_buffer[3] = vertex_buffer_data[3];
	actual_vertex_buffer[4] = vertex_buffer_data[1];
	actual_vertex_buffer[5] = vertex_buffer_data[2];

	Mesh *mesh = new Mesh(meshName, actual_vertex_buffer);

	return mesh;
}

Mesh* MeshBuilder::GenerateCube(const std::wstring &meshName, const Color color, const float lengthX, const float lengthY, const float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(-lengthX/2, -lengthY/2, -lengthZ/2);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX/2, -lengthY/2, -lengthZ/2);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX/2, lengthY/2, -lengthZ/2);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX/2, lengthY/2, -lengthZ/2);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX/2, -lengthY/2, lengthZ/2);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX/2, -lengthY/2, lengthZ/2);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX/2, lengthY/2, lengthZ/2);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX/2, lengthY/2, lengthZ/2);
	v.color = color;
	vertex_buffer_data.push_back(v);
	
	std::vector<Vertex> actual_vertex_buffer;
	actual_vertex_buffer.resize(36);
	actual_vertex_buffer[0] = vertex_buffer_data[7];
	actual_vertex_buffer[0].normal.Set(0, 0, 1);
	actual_vertex_buffer[1] = vertex_buffer_data[4];
	actual_vertex_buffer[1].normal.Set(0, 0, 1);
	actual_vertex_buffer[2] = vertex_buffer_data[6];
	actual_vertex_buffer[2].normal.Set(0, 0, 1);
	actual_vertex_buffer[3] = vertex_buffer_data[5];
	actual_vertex_buffer[3].normal.Set(0, 0, 1);
	actual_vertex_buffer[4] = vertex_buffer_data[6];
	actual_vertex_buffer[4].normal.Set(0, 0, 1);
	actual_vertex_buffer[5] = vertex_buffer_data[4];
	actual_vertex_buffer[5].normal.Set(0, 0, 1);
	actual_vertex_buffer[6] = vertex_buffer_data[6];
	actual_vertex_buffer[6].normal.Set(1, 0, 0);
	actual_vertex_buffer[7] = vertex_buffer_data[5];
	actual_vertex_buffer[7].normal.Set(1, 0, 0);
	actual_vertex_buffer[8] = vertex_buffer_data[2];
	actual_vertex_buffer[8].normal.Set(1, 0, 0);
	actual_vertex_buffer[9] = vertex_buffer_data[1];
	actual_vertex_buffer[9].normal.Set(1, 0, 0);
	actual_vertex_buffer[10] = vertex_buffer_data[2];
	actual_vertex_buffer[10].normal.Set(1, 0, 0);
	actual_vertex_buffer[11] = vertex_buffer_data[5];
	actual_vertex_buffer[11].normal.Set(1, 0, 0);
	actual_vertex_buffer[12] = vertex_buffer_data[3];
	actual_vertex_buffer[12].normal.Set(0, 1, 0);
	actual_vertex_buffer[13] = vertex_buffer_data[7];
	actual_vertex_buffer[13].normal.Set(0, 1, 0);
	actual_vertex_buffer[14] = vertex_buffer_data[2];
	actual_vertex_buffer[14].normal.Set(0, 1, 0);
	actual_vertex_buffer[15] = vertex_buffer_data[6];
	actual_vertex_buffer[15].normal.Set(0, 1, 0);
	actual_vertex_buffer[16] = vertex_buffer_data[2];
	actual_vertex_buffer[16].normal.Set(0, 1, 0);
	actual_vertex_buffer[17] = vertex_buffer_data[7];
	actual_vertex_buffer[17].normal.Set(0, 1, 0);
	actual_vertex_buffer[18] = vertex_buffer_data[2];
	actual_vertex_buffer[18].normal.Set(0, 0, -1);
	actual_vertex_buffer[19] = vertex_buffer_data[1];
	actual_vertex_buffer[19].normal.Set(0, 0, -1);
	actual_vertex_buffer[20] = vertex_buffer_data[3];
	actual_vertex_buffer[20].normal.Set(0, 0, -1);
	actual_vertex_buffer[21] = vertex_buffer_data[0];
	actual_vertex_buffer[21].normal.Set(0, 0, -1);
	actual_vertex_buffer[22] = vertex_buffer_data[3];
	actual_vertex_buffer[22].normal.Set(0, 0, -1);
	actual_vertex_buffer[23] = vertex_buffer_data[1];
	actual_vertex_buffer[23].normal.Set(0, 0, -1);
	actual_vertex_buffer[24] = vertex_buffer_data[3];
	actual_vertex_buffer[24].normal.Set(-1, 0, 0);
	actual_vertex_buffer[25] = vertex_buffer_data[0];
	actual_vertex_buffer[25].normal.Set(-1, 0, 0);
	actual_vertex_buffer[26] = vertex_buffer_data[7];
	actual_vertex_buffer[26].normal.Set(-1, 0, 0);
	actual_vertex_buffer[27] = vertex_buffer_data[4];
	actual_vertex_buffer[27].normal.Set(-1, 0, 0);
	actual_vertex_buffer[28] = vertex_buffer_data[7];
	actual_vertex_buffer[28].normal.Set(-1, 0, 0);
	actual_vertex_buffer[29] = vertex_buffer_data[0];
	actual_vertex_buffer[29].normal.Set(-1, 0, 0);
	actual_vertex_buffer[30] = vertex_buffer_data[1];
	actual_vertex_buffer[30].normal.Set(0, -1, 0);
	actual_vertex_buffer[31] = vertex_buffer_data[5];
	actual_vertex_buffer[31].normal.Set(0, -1, 0);
	actual_vertex_buffer[32] = vertex_buffer_data[0];
	actual_vertex_buffer[32].normal.Set(0, -1, 0);
	actual_vertex_buffer[33] = vertex_buffer_data[4];
	actual_vertex_buffer[33].normal.Set(0, -1, 0);
	actual_vertex_buffer[34] = vertex_buffer_data[0];
	actual_vertex_buffer[34].normal.Set(0, -1, 0);
	actual_vertex_buffer[35] = vertex_buffer_data[5];
	actual_vertex_buffer[35].normal.Set(0, -1, 0);

	Mesh *mesh = new Mesh(meshName, actual_vertex_buffer);

	return mesh;
}

Mesh* MeshBuilder::GenerateSphere(const std::wstring &meshName, const Color color, const float radius, const int nSegments, const int nRings)
{
	std::vector<Vertex> vertex_buffer_data;

	vertex_buffer_data.resize((nRings + 1) * (nSegments + 1));
	for(int index = 0; index < (nRings + 1); index++)
	{
		double ringDegree =(Math::PI / nRings) * index;
		double y = cos(ringDegree) * radius;
		if(ringDegree > Math::HALF_PI)
		{
			ringDegree = Math::PI - ringDegree;
		}
		const double ringRadius = sin(ringDegree) * radius;
		std::vector<Vertex>::iterator begin = vertex_buffer_data.begin() + (index * (nSegments + 1));
		std::vector<Vertex>::iterator end = begin + (nSegments + 1);
		double degree = 0;
		double increment = Math::TWO_PI/nSegments;
		for(std::vector<Vertex>::iterator vert = begin; vert != end; vert++)
		{
			double x;
			double z;
			if(degree < Math::HALF_PI)
			{
				x = sin(degree) * ringRadius;
				z = cos(degree) * ringRadius;
				vert->pos.Set(x,y,z);
				vert->normal.Set(x,y,z);
				vert->color = color;
			}
			else if(degree < Math::PI)
			{
				x = sin(Math::PI - degree) * ringRadius;
				z = cos(Math::PI - degree) * ringRadius * -1;
				vert->pos.Set(x,y,z);
				vert->normal.Set(x,y,z);
				vert->color = color;
			}
			else if(degree < Math::PI + Math::HALF_PI)
			{
				x = cos(Math::PI + Math::HALF_PI - degree) * ringRadius * -1;
				z = sin(Math::PI + Math::HALF_PI - degree) * ringRadius * -1;
				vert->pos.Set(x,y,z);
				vert->normal.Set(x,y,z);
				vert->color = color;
			}
			else
			{
				x = sin(Math::TWO_PI - degree) * ringRadius * -1;
				z = cos(Math::TWO_PI - degree) * ringRadius;
				vert->pos.Set(x,y,z);
				vert->normal.Set(x,y,z);
				vert->color = color;
			}
			degree+= increment;
		}
	}

	std::vector<Vertex> actual_vertex_buffer;
	actual_vertex_buffer.resize(nRings * nSegments * 6);
	int iFace = 0;
	for(std::vector<Vertex>::iterator index = actual_vertex_buffer.begin(); index != actual_vertex_buffer.end(); iFace++)
	{
		for(int segment = 0; segment  < nSegments; segment++)
		{
			//Triangle #1
			*index = vertex_buffer_data[iFace];
			index++;
			*index = vertex_buffer_data[iFace + (nSegments + 1)];
			index++;
			*index = vertex_buffer_data[iFace + (nSegments + 1) + 1];

			index++;

			//Triangle #2
			*index = vertex_buffer_data[iFace];
			index++;
			*index = vertex_buffer_data[iFace + (nSegments + 1) + 1];
			index++;
			*index = vertex_buffer_data[iFace + 1];
			index++;
			iFace++;
		}
	}

	Mesh* mesh = new Mesh(meshName, actual_vertex_buffer);

	return mesh;
}

Mesh* MeshBuilder::GenerateCone(const std::wstring &meshName, const Color color, const float height, const float radius, const int nSlices)
{
	std::vector<Vertex> vertex_buffer_data;

	//two extra vertices for the tip of the cone and centre of the circle 
	vertex_buffer_data.resize((nSlices + 1) + 2);

	//vertices for the circle
	double degree = 0;
	double increment = Math::TWO_PI/nSlices;
	std::vector<Vertex>::iterator vert;
	for(vert = vertex_buffer_data.begin(); vert != vertex_buffer_data.end() - 2; vert++)
	{
		double x;
		double z;
		if(degree < Math::HALF_PI)
		{
			x = sin(degree) * radius;
			z = cos(degree) * radius;
			vert->pos.Set(x,-height/2,z);
			vert->color = color;
		}
		else if(degree < Math::PI)
		{
			x = sin(Math::PI - degree) * radius;
			z = cos(Math::PI - degree) * radius * -1;
			vert->pos.Set(x,-height/2,z);
			vert->color = color;
		}
		else if(degree < Math::PI + Math::HALF_PI)
		{
			x = cos(Math::PI + Math::HALF_PI - degree) * radius * -1;
			z = sin(Math::PI + Math::HALF_PI - degree) * radius * -1;
			vert->pos.Set(x,-height/2,z);
			vert->color = color;
		}
		else
		{
			x = sin(Math::TWO_PI - degree) * radius * -1;
			z = cos(Math::TWO_PI - degree) * radius;
			vert->pos.Set(x,-height/2,z);
			vert->color = color;
		}
		degree+= increment;
	}

	//vertex for centre of circle
	vert->pos.Set(0,-height/2,0);
	vert->color = color;
	vert++;

	//vertex for tip of cone
	vert->pos.Set(0,height/2,0);
	vert->color = color;


	//Where the actual verts are placed.
	std::vector<Vertex> actual_vertex_buffer;
	actual_vertex_buffer.resize(nSlices * 6);
	//Index and other variables are defined outside so they can be reused in other loops
	std::vector<Vertex>::iterator index;
	std::vector<Vertex>::iterator end = actual_vertex_buffer.begin() + nSlices * 3;
	int iCentre = nSlices + 1;
	int iFace = 0;

	//for loop for the base of the cone
	for(index = actual_vertex_buffer.begin(); index != end; index++)
	{
		*index = vertex_buffer_data[iFace];
		index->normal.Set(0.f, -1.f, 0.f);
		index++;
		*index = vertex_buffer_data[iCentre];
		index->normal.Set(0.f, -1.f, 0.f);
		index++;
		*index = vertex_buffer_data[iFace + 1];
		index->normal.Set(0.f, -1.f, 0.f);
		iFace++;
	}

	iFace = 0;
	iCentre++;
	end = actual_vertex_buffer.end();

	//for loop for the sides of the cone
	for(; index != end; index++)
	{
		*index = vertex_buffer_data[iFace + 1];
		index->normal = index->pos;
		index->normal.y = height;
		index++;
		*index = vertex_buffer_data[iCentre];
		index->normal = index->pos;
		index++;
		*index = vertex_buffer_data[iFace];
		index->normal = index->pos;
		index->normal.y = height;
		iFace++;
	}

	Mesh* mesh = new Mesh(meshName, actual_vertex_buffer);
	return mesh;
}

Mesh* MeshBuilder::GenerateCylinder(const std::wstring &meshName, const Color color, const float height, const float radius, const int nSlices, const float thickness)
{
	std::vector<Vertex> vertex_buffer_data;

	//two extra vertices for the two centres of the base and top of the cylinder
	vertex_buffer_data.resize((nSlices + 1)*2 + 2);

	//vertices for the circle
	{
		double y = -height/2;
		std::vector<Vertex>::iterator end = vertex_buffer_data.begin() + nSlices + 1;
		std::vector<Vertex>::iterator vert = vertex_buffer_data.begin();
		//for loop that loops twice to create the bottom and top of the cylinder
		for(int index = 0; index < 2; index++)
		{
			double degree = 0;
			double increment = Math::TWO_PI/nSlices;
			for(; vert != end; vert++)
			{
				double x;
				double z;
				if(degree < Math::HALF_PI)
				{
					x = sin(degree) * radius;
					z = cos(degree) * radius;
					vert->pos.Set(x,y,z);
					vert->color = color;
				}
				else if(degree < Math::PI)
				{
					x = sin(Math::PI - degree) * radius;
					z = cos(Math::PI - degree) * radius * -1;
					vert->pos.Set(x,y,z);
					vert->color = color;
				}
				else if(degree < Math::PI + Math::HALF_PI)
				{
					x = cos(Math::PI + Math::HALF_PI - degree) * radius * -1;
					z = sin(Math::PI + Math::HALF_PI - degree) * radius * -1;
					vert->pos.Set(x,y,z);
					vert->color = color;
				}
				else
				{
					x = sin(Math::TWO_PI - degree) * radius * -1;
					z = cos(Math::TWO_PI - degree) * radius;
					vert->pos.Set(x,y,z);
					vert->color = color;
				}
				degree+= increment;
			}
			//defining the centre
			vert->pos.Set(0,y,0);
			vert->color = color;
			vert++;
			y = height/2;
			end = vertex_buffer_data.end() - 1;
		}
	}

	std::vector<Vertex> actual_vertex_buffer;
	actual_vertex_buffer.resize(nSlices*12);
	//index and other variables are defined outside the loop so they can be reused
	std::vector<Vertex>::iterator index = actual_vertex_buffer.begin();
	std::vector<Vertex>::iterator end = actual_vertex_buffer.begin() + nSlices*3;
	int iFace = 0;
	int iCentre = nSlices + 1;
	//for loop for the bottom of the cylinder
	for(; index != end; index++)
	{
		*index = vertex_buffer_data[iFace];
		index->normal.Set(0.f, -1.f, 0.f);
		index++;
		*index = vertex_buffer_data[iCentre];
		index->normal.Set(0.f, -1.f, 0.f);
		index++;
		*index = vertex_buffer_data[iFace + 1];
		index->normal.Set(0.f, -1.f, 0.f);
		iFace++;
	}

	iFace+=2;
	iCentre = (nSlices + 1) * 2 + 1;
	end += nSlices*3;
	//for loop for top of the cylinder
	for(; index != end; index++)
	{
		*index = vertex_buffer_data[iFace + 1];
		index->normal.Set(0.f, -1.f, 0.f);
		index++;
		*index = vertex_buffer_data[iCentre];
		index->normal.Set(0.f, -1.f, 0.f);
		index++;
		*index = vertex_buffer_data[iFace];
		index->normal.Set(0.f, -1.f, 0.f);
		iFace++;
	}

	end = actual_vertex_buffer.end();
	iFace = 0;

	//for loop for the sides of the cylinder
	for(; index != end; index++)
	{
		//Triangle #1
		*index = vertex_buffer_data[iFace + nSlices + 2];
		index->normal.x = index->pos.x;
		index->normal.z = index->pos.z;
		index++;
		*index = vertex_buffer_data[iFace];
		index->normal.x = index->pos.x;
		index->normal.z = index->pos.z;
		index++;
		*index = vertex_buffer_data[iFace + 1];
		index->normal.x = index->pos.x;
		index->normal.z = index->pos.z;
		index++;

		//Triangle #2
		*index = vertex_buffer_data[iFace + nSlices + 2];
		index->normal.x = index->pos.x;
		index->normal.z = index->pos.z;
		index++;
		*index = vertex_buffer_data[iFace + 1];
		index->normal.x = index->pos.x;
		index->normal.z = index->pos.z;
		index++;
		*index = vertex_buffer_data[iFace + nSlices + 3];
		index->normal.x = index->pos.x;
		index->normal.z = index->pos.z;
		iFace++;
	}

	Mesh* mesh = new Mesh(meshName, actual_vertex_buffer);
	return mesh;
}

Mesh* MeshBuilder::GenerateRing(const std::wstring &meshName, const Color color, const float radius, const float thickness, const int nSlices)
{
	std::vector<Vertex> vertex_buffer_data;

	vertex_buffer_data.resize(nSlices * 2 + 2);
	double degree = 0;
	double increment = Math::TWO_PI/nSlices;
	for(std::vector<Vertex>::iterator vert = vertex_buffer_data.begin(); vert != vertex_buffer_data.end(); vert++)
	{
		double x;
		double z;
		if(degree < Math::HALF_PI)
		{
			x = sin(degree) * radius;
			z = cos(degree) * radius;
			vert->pos.Set(x, 0.0f, z);
			vert->color = color;
			vert->normal.Set(0.0f, 1.0f, 0.0f);
			vert++;
			x = sin(degree) * (radius - thickness);
			z = cos(degree) * (radius - thickness);
			vert->pos.Set(x, 0.0f, z);
			vert->color = color;
			vert->normal.Set(0.0f, 1.0f, 0.0f);
		}
		else if(degree < Math::PI)
		{
			x = cos(degree - Math::HALF_PI) * radius;
			z = sin(degree - Math::HALF_PI) * radius * -1;
			vert->pos.Set(x, 0.0f, z);
			vert->color = color;
			vert->normal.Set(0.0f, 1.0f, 0.0f);
			vert++;
			x = cos(degree - Math::HALF_PI) * (radius - thickness);
			z = sin(degree - Math::HALF_PI) * (radius - thickness) * -1;
			vert->pos.Set(x, 0.0f, z);
			vert->color = color;
			vert->normal.Set(0.0f, 1.0f, 0.0f);
		}
		else if(degree < Math::HALF_PI * 3)
		{
			x = abs(sin(degree - Math::PI)) * radius * -1;
			z = abs(cos(degree - Math::PI)) * radius * -1;
			vert->pos.Set(x, 0.0f, z);
			vert->color = color;
			vert->normal.Set(0.0f, 1.0f, 0.0f);
			vert++;
			x = abs(sin(degree - Math::PI)) * (radius - thickness) * -1;
			z = abs(cos(degree - Math::PI)) * (radius - thickness) * -1;
			vert->pos.Set(x, 0.0f, z);
			vert->color = color;
			vert->normal.Set(0.0f, 1.0f, 0.0f);
		}
		else
		{
			x = cos(degree - Math::HALF_PI * 3) * radius * -1;
			z = sin(degree - Math::HALF_PI * 3) * radius;
			vert->pos.Set(x, 0.0f, z);
			vert->color = color;
			vert->normal.Set(0.0f, 1.0f, 0.0f);
			vert++;
			x = cos(degree - Math::HALF_PI * 3) * (radius - thickness) * -1;
			z = sin(degree - Math::HALF_PI * 3) * (radius - thickness);
			vert->pos.Set(x, 0.0f, z);
			vert->color = color;
			vert->normal.Set(0.0f, 1.0f, 0.0f);
		}

		degree+= increment;
	}


	std::vector<Vertex> actual_vertex_buffer;
	actual_vertex_buffer.resize(nSlices * 6);
	int iFace = 0;
	for(std::vector<Vertex>::iterator index = actual_vertex_buffer.begin(); index != actual_vertex_buffer.end(); index++)
	{
		if(isOdd(iFace))
		{
			*index = vertex_buffer_data[iFace];
			index++;
			*index = vertex_buffer_data[iFace + 1];
			index++;
			*index = vertex_buffer_data[iFace+2];
		}
		else
		{
			*index = vertex_buffer_data[iFace + 1];
			index++;
			*index = vertex_buffer_data[iFace];
			index++;
			*index = vertex_buffer_data[iFace+2];
		}
		iFace++;
	}

	Mesh* mesh = new Mesh(meshName, actual_vertex_buffer);

	return mesh;
}

Mesh* MeshBuilder::GenerateCircle(const std::wstring &meshName, const Color color, const float radius, const int nSlices)
{
	Mesh* mesh = GenerateRing(meshName, color, radius, radius, nSlices);
	return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::wstring &file_path)
{
	std::vector<Vertex> vertex_buffer;
	ObjLoader::LoadOBJ(file_path, vertex_buffer);
	//set the file name as the name of the object removing the .obj at the end
	Mesh* mesh = new Mesh(file_path.substr(0,file_path.size() - 4), vertex_buffer);
	return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::wstring &file_path, unsigned numRow, unsigned numCol)
{
	std::vector<Vertex> vertex_buffer_data;
	const double incrementU = 1.0 / numCol;
	const double decrementV = 1.0 / numRow;
	TexCoord BottomLeft(0, 1 - decrementV);
	TexCoord BottomRight(incrementU, 1 - decrementV);
	TexCoord TopLeft(0, 1);
	TexCoord TopRight(incrementU, 1);
	Color color(1,1,1);
	Vector3 normal;

	vertex_buffer_data.resize(6 * numRow * numCol);
	std::vector<Vertex>::iterator vert = vertex_buffer_data.begin();

	for(int y = 0; y < numRow; y++)
	{
		for(int x = 0; x < numCol; x++)
		{
			vert->pos.Set(0, 1, 0);
			vert->color;
			vert->normal;
			vert->texCoord = TopLeft;
			vert++;

			vert->pos.Set(1, 0, 0);
			vert->color;
			vert->normal;
			vert->texCoord = BottomRight;
			vert++;

			vert->pos.Set(1, 1, 0);
			vert->color;
			vert->normal;
			vert->texCoord = TopRight;
			vert++;

			vert->pos.Set(0, 0, 0);
			vert->color;
			vert->normal;
			vert->texCoord = BottomLeft;
			vert++;

			vert->pos.Set(1, 0, 0);
			vert->color;
			vert->normal;
			vert->texCoord = BottomRight;
			vert++;

			vert->pos.Set(0, 1, 0);
			vert->color;
			vert->normal;
			vert->texCoord = TopLeft;
			vert++;
			BottomLeft.u += incrementU;
			BottomRight.u += incrementU;
			TopLeft.u += incrementU;
			TopRight.u += incrementU;
		}
		BottomLeft.v -= decrementV;
		BottomRight.v -= decrementV;
		TopLeft.v -= decrementV;
		TopRight.v -= decrementV;
	}

	Mesh *mesh = new Mesh(file_path.substr(0,file_path.length()-4), vertex_buffer_data);
	return mesh;
}