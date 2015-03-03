#pragma once
#include "DrawOrder.h"
#include <map>

class GlobalList
{
public:
	GlobalList();
	~GlobalList();
	bool AddMesh(Mesh*const mesh);
	bool AddTexture(const std::wstring name, const std::wstring filepath);
	bool AddMaterial(const Material& material);
	bool AddDraw(const drawOrder& draw);
	Mesh* GetMesh(const std::wstring meshName) const;
	drawOrder& GetDraw(const std::wstring drawName);
	Material& GetMaterial(const std::wstring materialName);
	unsigned GetTexture(const std::wstring textureName) const;
	std::map<std::wstring, Mesh*>& GetMeshList();
	std::map<std::wstring, drawOrder*>& GetDrawList();
	std::map<std::wstring, Material*>& GetMaterialList();
	std::map<std::wstring, unsigned>& GetTextureList();
private:
	std::vector<drawOrder> draws;
	std::vector<Material> materials; 
	std::map<std::wstring, Mesh*> meshList;
	std::map<std::wstring, drawOrder*> drawList;
	std::map<std::wstring, Material*> materialList;
	std::map<std::wstring, unsigned> textureList;
};