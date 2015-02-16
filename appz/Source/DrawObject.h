#pragma once
#include "Mesh.h"

class DrawObject
{
public:
	DrawObject(Mesh* mesh = NULL, const Material mat = Material(), const unsigned drawMode = GL_TRIANGLES, const bool enableLight = false);
	~DrawObject();
	void Set(Mesh* mesh, const Material mat, const unsigned drawMode = GL_TRIANGLES);
	void SetMeshTo(Mesh* mesh);
	void SetMaterialTo(const Material mat);
	void SetModeTo(const unsigned mode);
	void SetTransformationTo(const Mtx44 matrix);
	void enableLighting();
	void disableLighting();
	void ToggleLighting();
	bool IsLightingEnabled() const;
	Mesh* GetMesh() const;
	const Material& GetMaterial() const;
	unsigned GetMode() const;
	void Render() const;
	void RenderPartial(const unsigned offset, const unsigned count) const;
private:
	Mesh* mesh;
	Material mat;
	unsigned drawMode;
	Mtx44 transformation;
	bool enableLight;
};