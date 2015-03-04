#include "DrawOrder.h"
#include "Graphics.h"
#include "Mesh.h"
#include "Custom Functions.h"

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

Vector3 drawOrder::GetGlobalPosition() const
{
	return GetMatrix() * Vector3(0,0,0);
}

const std::wstring& drawOrder::GetName() const
{
	return name;
}

const drawOrder* drawOrder::GetChildren(const unsigned index) const
{
	return children[index];
}

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

void drawOrder::SetMeshTo(Mesh*const mesh)
{
	geometry = mesh;
}

void drawOrder::SetMaterialTo(Material* mat)
{
	material = mat;
}

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

Mtx44 drawOrder::GetModelTransform() const
{
	if(parent)
	{
		return transform.TranslationMatrix() * transform.ScalationMatrix() * parent->GetModelTransform();
	}
	return transform.RotationMatrix() * transform.TranslationMatrix() * transform.ScalationMatrix();
}
 
Mtx44 drawOrder::GetMatrix() const
{
	Mtx44 parentModel, parentRotation;
	if(parent)
	{
		parentModel = parent->GetModelTransform();
		parentRotation = parent->GetRotationMatrix();
	}
	else
	{
		parentModel.SetToIdentity();
		parentRotation.SetToIdentity();
	}
	return parentModel * parentRotation * transform.Matrix() * selfTransform.Matrix();
}

drawOrder* drawOrder::GetParent() const
{
	return parent;
}

void drawOrder::SetNameAs(const std::wstring name)
{
	this->name = name;
}

unsigned drawOrder::GetTexture() const
{
	return material->GetTexture();
}

void drawOrder::SetTextureTo(unsigned textureID)
{
	material->SetTextureTo(textureID);
}

Mtx44 drawOrder::GetTranslationMatrix() const
{
	return transform.TranslationMatrix();
}

Mtx44 drawOrder::GetRotationMatrix() const
{
	return transform.rotate.MatrixX() * transform.rotate.MatrixY() * transform.rotate.MatrixZ();
}

void drawOrder::Render() const
{
	geometry->Render(material->GetTexture() , drawMode);
}

void drawOrder::RenderPartial(const unsigned offset, const unsigned count) const
{
	geometry->Render(offset, count, material->GetTexture(), drawMode);
}

Mesh* drawOrder::GetMesh() const
{
	return geometry;
}

Material* drawOrder::GetMaterial() const
{
	return material;
}

unsigned drawOrder::GetDrawMode() const
{
	return drawMode;
}

bool drawOrder::IsLightEnabled() const
{
	return enableLight;
}