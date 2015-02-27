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
#include "ShopperIdlerLv1.h"
#include "ShopperWandererLv2.h"
#include "WizardLv2.h"
#include "ShopperPayerLv1.h"
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
	ShopperWandererLv2 SWLv2[2];
	WizardLv2 wizard;
	ShopperIdler SILv1;
	ShopperPayerLv1 SPLv1;
	bool isJumping;
	bool isFalling;
	double jumpedHeight;
	bool isFrog;
	bool UpdateLv2;
	bool UpdateLv1;

	//print fps
	double deltaTime;
	int frameCounter;
	double accumulatingDT;
	double currentFPS;
	ContactSolver collisionSystem;
	VoxelOctree collisionEnvironment;

	//logic
	bool drawVoxels;

	Vector3 playerAcceleration;

	//functions
	void DoUserInput();

	void InnitItems(const drawOrder& basedraw, const Vector3 offset, Vector3 increment);
	void InnitTextures();
	void InnitLight();
	void InnitGeometry();
	void InnitDraws();
	void InnitForces();
	void InnitVoxels();
	void InnitLogic();
	void InnitSounds();
	void InnitMaterials();

	void CreateItems(drawOrder& item, Vector3 offset, std::wstring parentname, Rotation RotateItem, int ItemPerColumn, int ColumnPerCompartment,float defaultZ, float ItemDistanceX,float ItemDistanceZ, int NumBunch, int NumCabinet, Vector3 BunchOffset, Vector3 CabinetOffset);

	void UpdateLogic();
	void UpdateView();
	void UpdateLight();
	void UpdateDraws();
};