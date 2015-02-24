#pragma once
#include "DrawOrder.h"
#include <map>

class GlobalList
{
public:
	GlobalList();
	~GlobalList();
	bool AddMesh(Mesh* mesh);
	bool AddTexture(const std::wstring filepath);
	bool AddMaterial(const Material& material);
	bool AddObject(const drawOrder& draw);
	Mesh* GetMesh(const std::wstring meshName) const;
	drawOrder& GetDraw(const std::wstring drawName) const;
	Material& GetMaterial(const std::wstring materialName) const;
	unsigned GetTexture(const std::wstring textureName) const;
private:
	std::map<std::wstring, Mesh*> meshList;
	std::vector<drawOrder> draws;
	std::map<std::wstring, drawOrder*> drawList;
	std::vector<Material> materials;
	std::map<std::wstring, Material*> materialList;
	std::map<std::wstring, unsigned> textureList;
};