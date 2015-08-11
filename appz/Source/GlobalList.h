#pragma once
/****************************************************************************/
/*!
\file GlobalList.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A list of all our assets
*/
/****************************************************************************/
#include "DrawOrder.h"
#include "CollisionBody.h"
#include <map>
/****************************************************************************/
/*!
Class GlobalList:
\brief
A list of all our assets
*/
/****************************************************************************/
class GlobalList
{
public:
	GlobalList();
	~GlobalList();
	bool AddMesh(Mesh*const mesh);
	bool AddTexture(const std::wstring name, const std::wstring filepath);
	bool AddMaterial(const Material& material);
	bool AddCollisionBody(const CollisionBody& collisionBody);
	bool AddDraw(const drawOrder& draw);
	Mesh* GetMesh(const std::wstring meshName) const;
	drawOrder& GetDraw(const std::wstring drawName);
	Material& GetMaterial(const std::wstring materialName);
	CollisionBody& GetCollisionBody(const std::wstring collisionBodyName);
	unsigned GetTexture(const std::wstring textureName) const;
	std::map<std::wstring, Mesh*>& GetMeshList();
	std::map<std::wstring, drawOrder*>& GetDrawList();
	std::map<std::wstring, Material*>& GetMaterialList();
	std::map<std::wstring, CollisionBody*>& GetCollisionBodiesList();
	std::map<std::wstring, unsigned>& GetTextureList();
private:
	std::vector<drawOrder> draws;
	std::vector<CollisionBody> collisionBodies;
	std::vector<Material> materials; 
	std::map<std::wstring, Mesh*> meshList;
	std::map<std::wstring, drawOrder*> drawList;
	std::map<std::wstring, Material*> materialList;
	std::map<std::wstring, CollisionBody*> collisionBodiesList;
	std::map<std::wstring, unsigned> textureList;
};