#pragma once

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "Light.h"
#include "Mtx44.h"
#include "DrawOrder.h"
#include "MatrixStack.h"
#include "ContactSolver.h"
#include "Force.h"
#include <vector>

class ScenePhysics : public Scene
{
public:
	ScenePhysics(Keyboard& keyboard, GLMouse& mouse, Sound& snd, Graphics& gfx);
	~ScenePhysics(void);

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
		GEO_LIFT,
		GEO_HALF_DOOR,
		GEO_DIDACT,
		GEO_SENTINEL,
		GEO_GROUND,
		GEO_FOOTBALL_FIELD,
		GEO_RING,
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
		DRAW_LEFT_LIFT,
		DRAW_RIGHT_LIFT,
		DRAW_GROUND,
		DRAW_FOOTBALL_FIELD,
		DRAW_THING_AT_CENTRE,

		DRAW_CORRUPTED_SENTINEL,
		DRAW_ROCK_SENTINEL,
		DRAW_STONE_SENTINEL,
		DRAW_WISE_SENTINEL,
		DRAW_SNEAKY_SENTINEL,
		DRAW_PURE_SENTINEL,

		NUM_DRAWS,
	};
	enum LIGHTS
	{
		WORLD_LIGHT,
		FOOTBALL_LIGHT,

		NUMLIGHTS,
	};
	enum TEXTURE_TYPE
	{
		TEXTURE_BACK,
		TEXTURE_BOTTOM,
		TEXTURE_DIDACT,
		TEXTURE_DOOR,
		TEXTURE_ELECTRONIC_CIRCUIT,
		TEXTURE_FOOTBALL_FIELD,
		TEXTURE_FRONT,
		TEXTURE_KITTEN_BRI,
		TEXTURE_LARGE_FORERUNNER_FLOOR_PLATE,
		TEXTURE_LEFT,
		TEXTURE_METALPLATEFLOORFULL,
		TEXTURE_METAL_TILE,
		TEXTURE_PLATE_METAL,
		TEXTURE_RIGHT,
		TEXTURE_RING,
		TEXTURE_TOP,

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
	bool didactIsSummoned;
	bool curruptedIsFound;
	bool wiseIsFound;
	bool rockIsFound;
	bool stoneIsFound;
	bool sneakyIsFound;
	bool pureIsFound;
	Vector3 playerAcceleration;
	Vector3 currupteds_place;
	Vector3 Wises_place;
	Vector3 rocks_place;
	Vector3 stones_place;
	Vector3 sneakys_place;
	Vector3 pures_place;

	//functions
	void DoUserInput();

	void InnitDitact();
	void InnitTextures();
	void InnitLight();
	void InnitGeometry();
	void InnitDraws();
	void InnitForces();
	void InnitVoxels();
	void InnitLogic();
	void InnitSounds();

	void UpdateLogic();
	void UpdateDidact();
	void UpdateRing();
	void UpdateView();
	void UpdateLight();
	void UpdateDraws();

	void ExecuteDrawOrder(drawOrder& draw);
};

