
#include "Mesh.h"
#include "GL\glew.h"
#include "LoadTGA.h"

Mesh::Mesh(const std::wstring &meshName, std::vector<Vertex>& Vertex_buffer)
	:
name(meshName)
{
	nVerts = Vertex_buffer.size();
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, Vertex_buffer.size() * sizeof(Vertex), &Vertex_buffer.front(), GL_STATIC_DRAW);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_vertexBuffer);
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