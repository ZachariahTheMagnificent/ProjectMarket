#pragma once

#include <vector>
#include <iostream>
#include "MatrixStack.h"
#include "Mesh.h"
#include "Light.h"
#include "Mtx44.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "shader.hpp"
#include "LoadTGA.h"
#include "Camera.h"
#include "DrawOrder.h"

const unsigned MAX_LIGHTS = 8;
enum ORIENTATION
{
	ORIENTATION_TOP,
	ORIENTATION_BOTTOM,
	ORIENTATION_CENTRE,
	TOTAL_ORIENTATIONS,
};


class Graphics
{
public:
	Graphics();
	~Graphics();
	void Init(GLFWwindow* window);
	void SetProjectionTo(const float FOVy, const float aspectRatio, const float nearPlane, const float farPlane);
	void SetViewAt(const Camera& camera);
	void InitText(const std::wstring filepath);
	void RenderText(const std::string text, const Color color);
	void RenderTextOnScreen(const std::string text, const Color color, const float size, const float x, const float y, ORIENTATION orientation = ORIENTATION_BOTTOM);
	void RenderMeshOnScreen(const drawOrder& object, const Mtx44& matrix, ORIENTATION orientation = ORIENTATION_BOTTOM);
	void RenderMesh(const drawOrder& object, const Mtx44& Matrix);
	bool AddLight(Light* light);
	void UpdateLights();
private:
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_LIGHTENABLED,
		U_NUMLIGHTS,

		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,

		U_LIGHT2_TYPE,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT2_COSINNER,
		U_LIGHT2_EXPONENT,
		U_LIGHT2_POSITION,
		U_LIGHT2_COLOR,
		U_LIGHT2_POWER,
		U_LIGHT2_KC,
		U_LIGHT2_KL,
		U_LIGHT2_KQ,

		U_LIGHT3_TYPE,
		U_LIGHT3_SPOTDIRECTION,
		U_LIGHT3_COSCUTOFF,
		U_LIGHT3_COSINNER,
		U_LIGHT3_EXPONENT,
		U_LIGHT3_POSITION,
		U_LIGHT3_COLOR,
		U_LIGHT3_POWER,
		U_LIGHT3_KC,
		U_LIGHT3_KL,
		U_LIGHT3_KQ,

		U_LIGHT4_TYPE,
		U_LIGHT4_SPOTDIRECTION,
		U_LIGHT4_COSCUTOFF,
		U_LIGHT4_COSINNER,
		U_LIGHT4_EXPONENT,
		U_LIGHT4_POSITION,
		U_LIGHT4_COLOR,
		U_LIGHT4_POWER,
		U_LIGHT4_KC,
		U_LIGHT4_KL,
		U_LIGHT4_KQ,

		U_LIGHT5_TYPE,
		U_LIGHT5_SPOTDIRECTION,
		U_LIGHT5_COSCUTOFF,
		U_LIGHT5_COSINNER,
		U_LIGHT5_EXPONENT,
		U_LIGHT5_POSITION,
		U_LIGHT5_COLOR,
		U_LIGHT5_POWER,
		U_LIGHT5_KC,
		U_LIGHT5_KL,
		U_LIGHT5_KQ,

		U_LIGHT6_TYPE,
		U_LIGHT6_SPOTDIRECTION,
		U_LIGHT6_COSCUTOFF,
		U_LIGHT6_COSINNER,
		U_LIGHT6_EXPONENT,
		U_LIGHT6_POSITION,
		U_LIGHT6_COLOR,
		U_LIGHT6_POWER,
		U_LIGHT6_KC,
		U_LIGHT6_KL,
		U_LIGHT6_KQ,

		U_LIGHT7_TYPE,
		U_LIGHT7_SPOTDIRECTION,
		U_LIGHT7_COSCUTOFF,
		U_LIGHT7_COSINNER,
		U_LIGHT7_EXPONENT,
		U_LIGHT7_POSITION,
		U_LIGHT7_COLOR,
		U_LIGHT7_POWER,
		U_LIGHT7_KC,
		U_LIGHT7_KL,
		U_LIGHT7_KQ,

		U_TOTAL,
	};
	unsigned m_parameters[U_TOTAL];
	unsigned m_programID;
	unsigned m_vertexArrayID;
	Light* lights[MAX_LIGHTS + 1];
	int currentNumOfLights;
	drawOrder meshText;
	Material textMaterial;
	GLFWwindow* m_window;

	MS viewStack, modelStack, projectionStack;
};