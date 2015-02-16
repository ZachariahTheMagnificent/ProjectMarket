#ifndef _MATERIAL_H
#define _MATERIAL_H
#include "LoadTGA.h"

struct Component
{
	Component(const float r = 0.1f, const float g = 0.1f, const float b = 0.1f)
	{
		Set(r, g, b);
	}
	void Set(const float r, const float g, const float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
	float r, g, b;
};

class Material
{
public:
	Material()
	{
		Component comp;
		SetTo(comp, comp, comp, 0, 0);
	}
	Material(const Component kAmbient, const Component kDiffuse, const Component kSpecular, const float kShininess, const unsigned textureID)
	{
		SetTo(kAmbient, kDiffuse, kSpecular, kShininess, textureID);
	}
	void SetTo(const Component kAmbient, const Component kDiffuse, const Component kSpecular, const float kShininess, const unsigned texture)
	{
		SetAmbientTo(kAmbient);
		SetDiffuseTo(kDiffuse);
		SetSpecularTo(kSpecular);
		SetShininessTo(kShininess);
		SetTextureTo(texture);
	}
	void SetAmbientTo(const Component Ambient)
	{
		kAmbient = Ambient;
	}
	void SetDiffuseTo(const Component Diffuse)
	{
		kDiffuse = Diffuse;
	}
	void SetSpecularTo(const Component Specular)
	{
		kSpecular = Specular;
	}
	void SetShininessTo(const float Shininess)
	{
		kShininess = Shininess;
	}
	void SetTextureTo(const unsigned texture)
	{
		textureID = texture;
	}
	void SetAmbientTo(const float r, const float g, const float b)
	{
		SetAmbientTo(Component(r,g,b));
	}
	void SetDiffuseTo(const float r, const float g, const float b)
	{
		SetDiffuseTo(Component(r,g,b));
	}
	void SetSpecularTo(const float r, const float g, const float b)
	{
		SetSpecularTo(Component(r,g,b));
	}
	const Component& GetAmbient() const
	{
		return kAmbient;
	}
	const Component& GetDiffuse() const
	{
		return kDiffuse;
	}
	const Component& GetSpecular() const
	{
		return kSpecular;
	}
	const unsigned GetTexture() const
	{
		return textureID;
	}
	float GetShininess() const
	{
		return kShininess;
	}
private:
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;
	unsigned textureID;
};

#endif