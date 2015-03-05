#pragma once
#include <vector>
#include "MatrixStack.h"
#include "Material.h"
#include "Mesh.h"

class Graphics;

struct Rotation
{
	float x;
	float y;
	float z;
	void Set(const float rotX, const float rotY, const float rotZ)
	{
		x = rotX;
		y = rotY;
		z = rotZ;
	}

	Mtx44 MatrixX() const
	{
		Mtx44 matrixX;

		matrixX.SetToRotation(x,1.0f,0.0f,0.0f);

		return matrixX;
	}

	Mtx44 MatrixY() const
	{
		Mtx44 matrixY;

		matrixY.SetToRotation(y,0.0f,1.0f,0.0f);

		return matrixY;
	}

	Mtx44 MatrixZ() const
	{
		Mtx44 matrixZ;

		matrixZ.SetToRotation(z,0.0f,0.0f,1.0f);

		return matrixZ;
	}

	Rotation(const float rotX = 0, const float rotY = 0, const float rotZ = 0)
	{
		Set(rotX, rotY, rotZ);
	}

	void operator=(Rotation rotate)
	{
		x = rotate.x;
		y = rotate.y;
		z = rotate.z;
	}

	void operator+=(Rotation rotate)
	{
		x += rotate.x;
		y += rotate.y;
		z += rotate.z;
	}

	void operator+(Rotation rotate)
	{
		Rotation newRotate;

		newRotate = *this;
		newRotate += rotate;
	}
};

struct Transformation
{
	Vector3 translate;
	Rotation rotate;
	Vector3 scale;
	Vector3 pivot;

	Transformation()
	{
		scale.Set(1,1,1);
	}
	Mtx44 TranslationMatrix() const
	{
		Mtx44 translation;
		translation.SetToTranslation(translate);

		return translation;
	}
	Mtx44 RotationMatrix() const
	{
		Mtx44 rotation, reorientate;
		reorientate.SetToTranslation(pivot);
		rotation = reorientate.GetInverse() * rotate.MatrixX() * rotate.MatrixY() * rotate.MatrixZ() * reorientate;

		return rotation;
	}
	Mtx44 ScalationMatrix() const
	{
		Mtx44 scalation;
		scalation.SetToScale(scale.x,scale.y,scale.z);

		return scalation;
	}
	Mtx44 Matrix() const
	{
		Mtx44 translation, rotation, scalation, reorientate;
		translation.SetToTranslation(translate);
		reorientate.SetToTranslation(pivot);
		scalation.SetToScale(scale.x,scale.y,scale.z);
		rotation = reorientate.GetInverse() * rotate.MatrixX() * rotate.MatrixY() * rotate.MatrixZ() * reorientate;

		return TranslationMatrix() * RotationMatrix() * ScalationMatrix();
	}
};

class drawOrder
{
public:
	drawOrder(std::wstring name = std::wstring(), Mesh* geometry = NULL, Material* material = NULL, drawOrder* parent = NULL, bool enableLight = false);
	~drawOrder();
	const std::wstring& GetName() const;
	Mtx44 GetMatrix() const;
	Mtx44 GetTranslationMatrix() const;
	Mtx44 GetRotationMatrix() const;
	Mtx44 GetScaleMatrix() const;
	Vector3 GetGlobalPosition() const;
	const drawOrder* GetChildren(const unsigned index) const;
	Mesh* GetMesh() const;
	Material* GetMaterial() const;
	unsigned GetDrawMode() const;
	unsigned GetTexture() const;
	drawOrder* GetParent() const;
	bool IsLightEnabled() const;
	void SetNameAs(const std::wstring name);
	void SetMeshTo(Mesh*const mesh);
	void SetTextureTo(unsigned textureID);
	void SetMaterialTo(Material* mat);
	void SetParentAs(drawOrder* parent);
	void Execute(Graphics& gfx);
	void Render() const;
	void RenderPartial(const unsigned offset, const unsigned count) const;
private:
	Mtx44 GetModelTransform() const;
	drawOrder* parent;
	std::vector<drawOrder*> children;
	unsigned drawMode;
	bool enableLight;
	std::wstring name;
	Mesh* geometry;
	Material* material;
public:
	Transformation transform;
	//this transformation will only apply to the parent and not it's children
	Transformation selfTransform;
};