#include "GlobalList.h"

GlobalList::GlobalList()
{
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

bool GlobalList::AddMesh(Mesh* mesh)
{
	meshList[mesh->GetName()] = mesh;
	return true;
}

bool GlobalList::AddTexture(const std::wstring filepath)
{
	std::wstring name = filepath.substr(0, filepath.size() - 4);
	textureList[filepath] = LoadTGA(filepath);
	return true;
}

bool GlobalList::AddMaterial(const Material& material)
{
	materials.push_back(material);
	materialList[material.GetName()] = &materials.back();
	return true;
}

bool GlobalList::AddObject(const drawOrder& draw)
{
	draws.push_back(draw);
	drawList[draw.GetName()] = &draws.back();
	return true;
}

Mesh* GlobalList::GetMesh(const std::wstring meshName) const
{
	return meshList.find(meshName)->second;
}

drawOrder& GlobalList::GetDraw(const std::wstring drawName) const
{
	return *drawList.find(drawName)->second;
}

Material& GlobalList::GetMaterial(const std::wstring materialName) const
{
	return *materialList.find(materialName)->second;
}

unsigned GlobalList::GetTexture(const std::wstring textureName) const
{
	return textureList.find(textureName)->second;
}