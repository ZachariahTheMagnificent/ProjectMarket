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
#include "GlobalList.h"
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
	GlobalList globals;
	Light light[1];
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
	void InnitMaterials();

	void UpdateLogic();
	void UpdateView();
	void UpdateLight();
	void UpdateDraws();
};