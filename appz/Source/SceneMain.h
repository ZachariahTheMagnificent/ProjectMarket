#pragma once

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "Light.h"
#include "Mtx44.h"
#include "DrawOrder.h"
#include "MatrixStack.h"
#include "ContactSolver.h"
#include "player.h"
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
		GEO_SKYBOX,
		GEO_TEXT,
		GEO_CUBE,	
		GEO_GROUND,
		GEO_CABINET1,
		GEO_CAN1,
		GEO_CAN2,
		GEO_CAN3,
		GEO_CEREAL1,
		GEO_CEREAL2,
		GEO_CEREAL3,
		GEO_PACKET1,
		GEO_PACKET2,
		GEO_PACKET3,
		NUM_GEOMETRY,
	};
	enum DRAW_REFERENCE
	{
		DRAW_MAIN,
		DRAW_SKYBOX,

		DRAW_PLAYER,
		DRAW_GROUND,
		DRAW_CABINET1,
		DRAW_CAN1,
		DRAW_CAN2,
		DRAW_CAN3,
		DRAW_CEREAL1,
		DRAW_CEREAL2,
		DRAW_CEREAL3,
		DRAW_PACKET1,
		DRAW_PACKET2,
		DRAW_PACKET3,

		NUM_DRAWS,
	};
	enum LIGHTS
	{
		WORLD_LIGHT,

		NUMLIGHTS,
	};
	enum TEXTURE_TYPE
	{
		TEXTURE_SKYBOX,
		TEXTURE_LARGE_FORERUNNER_FLOOR_PLATE,
		TEXTURE_GROUND,
		TEXTURE_CABINET1,
		TEXTURE_CAN1,
		TEXTURE_CAN2,
		TEXTURE_CAN3,
		TEXTURE_CEREAL1,
		TEXTURE_CEREAL2,
		TEXTURE_CEREAL3,
		TEXTURE_PACKET1,
		TEXTURE_PACKET2,
		TEXTURE_PACKET3,

		NUM_TEXTURES,
	};

	//all vectors and other objects used;
	std::vector<Mesh*> meshList;
	std::vector<drawOrder> drawOrders;
	std::vector<Voxel> voxels;
	std::vector<unsigned> textures;
	Light light[NUMLIGHTS];
	Camera camera;
	Player* player;
	bool isJumping;
	bool isFalling;
	double jumpedHeight;
	bool isFrog;

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
};

