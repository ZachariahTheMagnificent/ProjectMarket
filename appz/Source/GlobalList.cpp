#include "GlobalList.h"
#include "Mesh.h"
#include "GL\glew.h"
#include "LoadTGA.h"
/****************************************************************************/
/*!
\file GlobalList.cpp
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A list of all our assets
*/
/****************************************************************************/

/****************************************************************************/
/*!
\brief
Default constructor
*/
/****************************************************************************/
GlobalList::GlobalList()
{
	draws.reserve(100000);
	materials.reserve(100000);
	collisionBodies.reserve(100000);
}
/****************************************************************************/
/*!
\brief
Default destructor
*/
/****************************************************************************/
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
/****************************************************************************/
/*!
\brief
Add a mesh to the list
\param mesh
		the mesh to be added
*/
/****************************************************************************/
bool GlobalList::AddMesh(Mesh*const mesh)
{
	meshList[mesh->GetName()] = mesh;
	return true;
}
/****************************************************************************/
/*!
\brief
Add a texture to the list
\param name
		the name of the texture
\param filepath
		the path to the file containing the texture(as a *.tga)
*/
/****************************************************************************/
bool GlobalList::AddTexture(const std::wstring name, const std::wstring filepath)
{
	textureList[name] = LoadTGA(filepath);
	return true;
}
/****************************************************************************/
/*!
\brief
Add a material to the list
\param material
		the material to be added
*/
/****************************************************************************/
bool GlobalList::AddMaterial(const Material& material)
{
	materials.push_back(material);
	materialList[material.GetName()] = &materials.back();
	return true;
}
/****************************************************************************/
/*!
\brief
Add a collision body to the list
\param collisionBody
		the collisionBody to be added
*/
/****************************************************************************/
bool GlobalList::AddCollisionBody(const CollisionBody& collisionBody)
{
	collisionBodies.push_back(collisionBody);
	collisionBodiesList[collisionBody.GetName()] = &collisionBodies.back();
	return true;
}
/****************************************************************************/
/*!
\brief
Add a drawOrder to the list
\param draw
		the drawOrder to be added
*/
/****************************************************************************/
bool GlobalList::AddDraw(const drawOrder& draw)
{
	//make the parent's child pointer point to the draw in the vector instead of the draw we were passed with
	draws.push_back(draw);
	draws.back().SetParentAs(draw.GetParent());
	drawList[draw.GetName()] = &draws.back();
	return true;
}
/****************************************************************************/
/*!
\brief
Get a mesh from the list
\param meshName
		the name of the mesh
*/
/****************************************************************************/
Mesh* GlobalList::GetMesh(const std::wstring meshName) const
{
	return meshList.find(meshName)->second;
}
/****************************************************************************/
/*!
\brief
Get a drawOrder from the list
\param drawName
		the name of the drawOrder
*/
/****************************************************************************/
drawOrder& GlobalList::GetDraw(const std::wstring drawName)
{
	return *drawList.find(drawName)->second;
}
/****************************************************************************/
/*!
\brief
Get a material from the list
\param materialName
		the name of the material
*/
/****************************************************************************/
Material& GlobalList::GetMaterial(const std::wstring materialName)
{
	return *materialList.find(materialName)->second;
}
/****************************************************************************/
/*!
\brief
Get a collision body from the list
\param Name
		the name of the collision body
*/
/****************************************************************************/
CollisionBody& GlobalList::GetCollisionBody(const std::wstring collisionBodyName)
{
	return *collisionBodiesList.find(collisionBodyName)->second;
}
/****************************************************************************/
/*!
\brief
Get a texture from the list
\param Name
		the name of the texture
*/
/****************************************************************************/
unsigned GlobalList::GetTexture(const std::wstring textureName) const
{
	return textureList.find(textureName)->second;
}
/****************************************************************************/
/*!
\brief
Returns the map of meshes
*/
/****************************************************************************/
std::map<std::wstring, Mesh*>& GlobalList::GetMeshList()
{
	return meshList;
}
/****************************************************************************/
/*!
\brief
Returns the map of draws
*/
/****************************************************************************/
std::map<std::wstring, drawOrder*>& GlobalList::GetDrawList()
{
	return drawList;
}
/****************************************************************************/
/*!
\brief
Returns the map of materials
*/
/****************************************************************************/
std::map<std::wstring, Material*>& GlobalList::GetMaterialList()
{
	return materialList;
}
/****************************************************************************/
/*!
\brief
Returns the map of collision bodies
*/
/****************************************************************************/
std::map<std::wstring, CollisionBody*>& GlobalList::GetCollisionBodiesList()
{
	return collisionBodiesList;
}
/****************************************************************************/
/*!
\brief
Returns the map of textures
*/
/****************************************************************************/
std::map<std::wstring, unsigned>& GlobalList::GetTextureList()
{
	return textureList;
}