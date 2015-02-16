#include "DrawObject.h"

DrawObject::DrawObject(Mesh* mesh, const Material mat, const unsigned drawMode, const bool enableLight)
	:
mesh(mesh),
mat(mat),
drawMode(drawMode),
enableLight(enableLight)
{
}

DrawObject::~DrawObject()
{
}

void DrawObject::Set(Mesh* mesh, const Material mat, const unsigned drawMode)
{
	SetMeshTo(mesh);
	SetMaterialTo(mat);
	SetModeTo(drawMode);
}

void DrawObject::SetMeshTo(Mesh* mesh)
{
	this->mesh = mesh;
}

void DrawObject::SetMaterialTo(const Material material)
{
	mat = material;
}

void DrawObject::SetModeTo(const unsigned mode)
{
	drawMode = mode;
}

void DrawObject::SetTransformationTo(const Mtx44 matrix)
{
	transformation = matrix;
}

Mesh* DrawObject::GetMesh() const
{
	return mesh;
}

const Material& DrawObject::GetMaterial() const
{
	return mat;
}

unsigned DrawObject::GetMode() const
{
	return drawMode;
}

void DrawObject::Render() const
{
	mesh->Render(mat.GetTexture() , drawMode);
}

void DrawObject::RenderPartial(const unsigned offset, const unsigned count) const
{
	mesh->Render(offset, count, mat.GetTexture(), drawMode);
}

void  DrawObject::enableLighting()
{
	enableLight = true;
}

void  DrawObject::disableLighting()
{
	enableLight = false;
}

void  DrawObject::ToggleLighting()
{
	enableLight = !enableLight;
}

bool  DrawObject::IsLightingEnabled() const
{
	return enableLight;
}