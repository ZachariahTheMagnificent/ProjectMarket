#include "DrawOrder.h"
#include "Graphics.h"
#include "Mesh.h"
#include "Custom Functions.h"
/****************************************************************************/
/*!
\file DrawOrder.cpp
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
Contains drawOrder which is a class used to help render objects in a scene in a hierarchical fashion
*/
/****************************************************************************/

/****************************************************************************/
/*!
\brief
Constructor for drawOrder
\param name
		sets the name of the draw
\param geometry
		sets the geomery of the draw
\param material
		sets the material of the drawOrder
\param parent
		sets the parent of the drawOrder
\param enableLight
		bool that decides if the drawOrder will have lighting
*/
/****************************************************************************/
drawOrder::drawOrder(std::wstring name, Mesh* geometry, Material* material, drawOrder* parent, bool enableLight)
	:
name(name),
geometry(geometry),
material(material),
enableLight(enableLight),
drawMode(GL_TRIANGLES),
parent(NULL)
{
	SetParentAs(parent);
}
/****************************************************************************/
/*!
\brief
Default destructor. If it has a parent, it will remove itself from it's parent's children vector
*/
/****************************************************************************/
drawOrder::~drawOrder()
{
	if(parent)
	{
		for(std::vector<drawOrder*>::iterator child = parent->children.begin(); child != parent->children.end(); ++child)
		{
			if(*child == this)
			{
				parent->children.erase(child);
				break;
			}
		}
	}
}
/****************************************************************************/
/*!
\brief
Returns the global position of the drawOrder
*/
/****************************************************************************/
Vector3 drawOrder::GetGlobalPosition() const
{
	return GetMatrix() * Vector3(0,0,0);
}
/****************************************************************************/
/*!
\brief
Returns the name of the drawOrder
*/
/****************************************************************************/
const std::wstring& drawOrder::GetName() const
{
	return name;
}
/****************************************************************************/
/*!
\brief
Returns one of it's children according to the index
\param index
		index of it's child to be returned
*/
/****************************************************************************/
const drawOrder* drawOrder::GetChildren(const unsigned index) const
{
	return children[index];
}
/****************************************************************************/
/*!
\brief
Tells OpenGL to draw itself and it's children
*/
/****************************************************************************/
void drawOrder::Execute(Graphics& gfx)
{
	for(std::vector<drawOrder*>::iterator child = children.begin(); child != children.end(); child++)
	{
		(*child)->Execute(gfx);
	}
	//a small check to see weather the draw order is pointing to a geometry before drawing it.
	if(geometry)
	{
		gfx.RenderMesh(*this, GetMatrix());
	}
}
/****************************************************************************/
/*!
\brief
Sets the drawOrder's mesh
*/
/****************************************************************************/
void drawOrder::SetMeshTo(Mesh*const mesh)
{
	geometry = mesh;
}
/****************************************************************************/
/*!
\brief
Sets the drawOrder's material
*/
/****************************************************************************/
void drawOrder::SetMaterialTo(Material* mat)
{
	material = mat;
}
/****************************************************************************/
/*!
\brief
Sets the drawOrder's parent and the new parent's children
\param parent
		the drawOrder's new parent
*/
/****************************************************************************/
void drawOrder::SetParentAs(drawOrder* parent)
{
	if(parent)
	{
		for(std::vector<drawOrder*>::iterator child = parent->children.begin(); child != parent->children.end(); ++child)
		{
			if(*child == this)
			{
				parent->children.erase(child);
				break;
			}
		}
	}
	this->parent = parent;
	if(parent)
	{
		parent->children.push_back(this);
	}
}
/****************************************************************************/
/*!
\brief
Returns the drawOrder's(incomplete) modelTransform
*/
/****************************************************************************/
Mtx44 drawOrder::GetModelTransform() const
{
	if(parent)
	{
		return parent->GetModelTransform() * transform.TranslationMatrix() * transform.RotationMatrix() * transform.ScalationMatrix();
	}
	return transform.TranslationMatrix() * transform.RotationMatrix() * transform.ScalationMatrix();
}
/****************************************************************************/
/*!
\brief
Returns the drawOrder's complete modelTransform
*/
/****************************************************************************/
Mtx44 drawOrder::GetMatrix() const
{
	Mtx44 modelTransform;
	if(parent)
	{
		modelTransform = parent->GetModelTransform();
	}
	else
	{
		modelTransform.SetToIdentity();
	}
	return modelTransform * transform.TranslationMatrix() * selfTransform.TranslationMatrix() * transform.RotationMatrix() * selfTransform.RotationMatrix() * transform.ScalationMatrix() * selfTransform.ScalationMatrix();
}
/****************************************************************************/
/*!
\brief
Returns the drawOrder's parent
*/
/****************************************************************************/
drawOrder* drawOrder::GetParent() const
{
	return parent;
}
/****************************************************************************/
/*!
\brief
Sets the name of the drawOrder
\param name
		the new name of the drawOrder
*/
/****************************************************************************/
void drawOrder::SetNameAs(const std::wstring name)
{
	this->name = name;
}
/****************************************************************************/
/*!
\brief
Returns the drawOrder's texture
*/
/****************************************************************************/
unsigned drawOrder::GetTexture() const
{
	return material->GetTexture();
}
/****************************************************************************/
/*!
\brief
Sets the drawOrder's texture
*/
/****************************************************************************/
void drawOrder::SetTextureTo(unsigned textureID)
{
	material->SetTextureTo(textureID);
}
/****************************************************************************/
/*!
\brief
Returns the transformation of the drawOrder as a translation matrix
*/
/****************************************************************************/
Mtx44 drawOrder::GetTranslationMatrix() const
{
	Mtx44 translationMatrix;
	translationMatrix.SetToTranslation(GetGlobalPosition());
	return translationMatrix;
}
/****************************************************************************/
/*!
\brief
Returns the drawOrder's rotationMatrix
*/
/****************************************************************************/
Mtx44 drawOrder::GetRotationMatrix() const
{
	return transform.rotate.MatrixX() * transform.rotate.MatrixY() * transform.rotate.MatrixZ();
}
/****************************************************************************/
/*!
\brief
Returns the drawOrder's scaleMatrix
*/
/****************************************************************************/
Mtx44 drawOrder::GetScaleMatrix() const
{
	Mtx44 parentScale;
	if(parent)
	{
		parentScale = parent->GetScaleMatrix();
	}
	else
	{
		parentScale.SetToIdentity();
	}
	return transform.ScalationMatrix() * parentScale;
}
/****************************************************************************/
/*!
\brief
Renders the drawOrder
*/
/****************************************************************************/
void drawOrder::Render() const
{
	geometry->Render(material->GetTexture() , drawMode);
}
/****************************************************************************/
/*!
\brief
Renders a portion of the drawOrder's mesh
\param offset
		offsets the first vertex to be rendered in the vertex buffer
\param count
		the number of vertices to be rendered after that
*/
/****************************************************************************/
void drawOrder::RenderPartial(const unsigned offset, const unsigned count) const
{
	geometry->Render(offset, count, material->GetTexture(), drawMode);
}
/****************************************************************************/
/*!
\brief
Returns the drawOrder's mesh
*/
/****************************************************************************/
Mesh* drawOrder::GetMesh() const
{
	return geometry;
}
/****************************************************************************/
/*!
\brief
Returns the drawOrder's material
*/
/****************************************************************************/
Material* drawOrder::GetMaterial() const
{
	return material;
}
/****************************************************************************/
/*!
\brief
Returns the drawOrder's drawMode
*/
/****************************************************************************/
unsigned drawOrder::GetDrawMode() const
{
	return drawMode;
}
/****************************************************************************/
/*!
\brief
Returns the bool that decides whether or not the drawOrder has lighting
*/
/****************************************************************************/
bool drawOrder::IsLightEnabled() const
{
	return enableLight;
}