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
	if(parent && parent->GetName() != L"main")
	{
		return parent->GetModelTransform() * transform.TranslationMatrix() * transform.RotationMatrix() * transform.ScalationMatrix();
	}
	return transform.TranslationMatrix() * transform.RotationMatrix() * transform.ScalationMatrix();
}

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
	Mtx44 translationMatrix;
	translationMatrix.SetToTranslation(GetGlobalPosition());
	return translationMatrix;
}

Mtx44 drawOrder::GetRotationMatrix() const
{
	return transform.rotate.MatrixX() * transform.rotate.MatrixY() * transform.rotate.MatrixZ();
}

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