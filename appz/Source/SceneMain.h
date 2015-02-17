#pragma once

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "Light.h"
#include "Mtx44.h"
#include "DrawOrder.h"
#include "MatrixStack.h"
#include "ContactSolver.h"
#include <vector>

class SceneMain : public Scene
{
public:
	SceneMain(Keyboard& keyboard, GLMouse& mouse, Sound& snd, Graphics& gfx);
	~SceneMain(void);

	virtual void Init();
	virtual bool Update(const double dt);
	virtual void Render();
	virtual void Exit();
private:
	//enums
	enum GEOMETRY_TYPE
	{
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_TEXT,
		GEO_CUBE,	
		GEO_GROUND,
		NUM_GEOMETRY,
	};
	enum DRAW_REFERENCE
	{
		DRAW_SKYBOX,
		DRAW_LEFT,
		DRAW_RIGHT,
		DRAW_TOP,
		DRAW_BOTTOM,
		DRAW_FRONT,
		DRAW_BACK,

		DRAW_PLAYER,
		DRAW_GROUND,

		NUM_DRAWS,
	};
	enum LIGHTS
	{
		WORLD_LIGHT,

		NUMLIGHTS,
	};
	enum TEXTURE_TYPE
	{
		TEXTURE_BACK,
		TEXTURE_BOTTOM,
		TEXTURE_FRONT,
		TEXTURE_LEFT,
		TEXTURE_RIGHT,
		TEXTURE_TOP,
		TEXTURE_LARGE_FORERUNNER_FLOOR_PLATE,
		TEXTURE_GROUND,

		NUM_TEXTURES,
	};

	//all vectors and other objects used;
	std::vector<Mesh*> meshList;
	std::vector<drawOrder> drawOrders;
	std::vector<Voxel> voxels;
	std::vector<unsigned> textures;
	Light light[NUMLIGHTS];
	Camera camera;
	MS viewStack, projectionStack, modelStack;

	//print fps
	double deltaTime;
	int frameCounter;
	double accumulatingDT;
	double currentFPS;
	ContactSolver collisionSystem;

	//logic
	bool drawVoxels;

	Vector3 playerAcceleration;

	//functions
	void DoUserInput();

	void InnitTextures();
	void InnitLight();
	void InnitGeometry();
	void InnitDraws();
	void InnitForces();
	void InnitVoxels();
	void InnitLogic();
	void InnitSounds();

	void UpdateLogic();
	void UpdateView();
	void UpdateLight();
	void UpdateDraws();

	void ExecuteDrawOrder(drawOrder& draw);
};

