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
#include "GlobalList.h"
#include "VoxelOctree.h"

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
	GlobalList globals;
	Light light[2];
	Camera camera;

	//print fps
	double deltaTime;
	int frameCounter;
	double accumulatingDT;
	double currentFPS;
	ContactSolver collisionSystem;
	VoxelOctree collisionEnvironment;

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
	void InnitMaterials();
	void InnitLight();
	void InnitGeometry();
	void InnitDraws();
	void InnitForces();
	void InnitCollisions();
	void InnitLogic();
	void InnitSounds();

	void UpdateLogic();
	void UpdateDidact();
	void UpdateRing();
	void UpdateView();
	void UpdateLight();
	void UpdateDraws();
};

