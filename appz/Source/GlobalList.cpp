#include "GlobalList.h"
#include "Mesh.h"
#include "GL\glew.h"
#include "LoadTGA.h"

GlobalList::GlobalList()
{
	draws.reserve(100000);
	materials.reserve(100000);
}

GlobalList::~GlobalList()
{
	for(std::map<std::wstring, Mesh*>::iterator mesh = meshList.begin(); mesh != meshList.end(); ++mesh)
	{
		if(mesh->second)
		{
			delete mesh->second;
		}
	}
	for(std::map<std::wstring, unsigned>::iterator texture = textureList.begin(); texture != textureList.end(); ++texture)
	{
		if(texture->second > 0)
		{
			glDeleteTextures(1, &texture->second);
		}
	}
}

bool GlobalList::AddMesh(Mesh*const mesh)
{
	meshList[mesh->GetName()] = mesh;
	return true;
}

bool GlobalList::AddTexture(const std::wstring name, const std::wstring filepath)
{
	textureList[name] = LoadTGA(filepath);
	return true;
}

bool GlobalList::AddMaterial(const Material& material)
{
	materials.push_back(material);
	materialList[material.GetName()] = &materials.back();
	return true;
}

bool GlobalList::AddDraw(const drawOrder& draw)
{
	//make the parent's child pointer point to the draw in the vector instead of the draw we were passed with
	draws.push_back(draw);
	draws.back().SetParentAs(draw.GetParent());
	drawList[draw.GetName()] = &draws.back();
	return true;
}

Mesh* GlobalList::GetMesh(const std::wstring meshName) const
{
	return meshList.find(meshName)->second;
}

drawOrder& GlobalList::GetDraw(const std::wstring drawName)
{
	return *drawList.find(drawName)->second;
}

Material& GlobalList::GetMaterial(const std::wstring materialName)
{
	return *materialList.find(materialName)->second;
}

unsigned GlobalList::GetTexture(const std::wstring textureName) const
{
	return textureList.find(textureName)->second;
}

std::map<std::wstring, Mesh*>& GlobalList::GetMeshList()
{
	return meshList;
}

std::map<std::wstring, drawOrder*>& GlobalList::GetDrawList()
{
	return drawList;
}

std::map<std::wstring, Material*>& GlobalList::GetMaterialList()
{
	return materialList;
}

std::map<std::wstring, unsigned>& GlobalList::GetTextureList()
{
	return textureList;
}