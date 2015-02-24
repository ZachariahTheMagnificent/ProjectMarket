#include "SceneMainMenu.h"
#include "GL\glew.h"
#include "Application.h"
#include "shader.hpp"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "PlayerHuman.h"
#include "PlayerFrog.h"

SceneMainMenu::SceneMainMenu(Keyboard& keyboard, GLMouse& mouse, Sound& snd, Graphics& gfx)
	:
Scene(keyboard, mouse, snd, gfx)
{
}

SceneMainMenu::~SceneMainMenu(void)
{
}

void SceneMainMenu::Init()
{
	InnitLight();
	InnitTextures();
	InnitSounds();
	InnitGeometry();
	InnitDraws();
	InnitVoxels();
	InnitForces();
	InnitLogic();
	gfx.InitText(L"Image//kitten_bri.tga");
	player = new PlayerHuman;
	isJumping = false;
	isFalling = false;
	jumpedHeight = 0;
	isFrog = false;

	camera.Init(Vector3(21.7, 5, 68.3), Vector3(1, 0, 0), Vector3(0, 1, 0));
	gfx.SetProjectionTo(45.f, 4.f / 3.f, 0.1f, 90000.f);
	gfx.InitText(L"Image//kitten_bri.tga");
}


void SceneMainMenu::InnitSounds()
{
	//snd.loadWave("pure", "sound//pure.wav");
}

void SceneMainMenu::InnitLogic()
{
	frameCounter = 0;
	accumulatingDT = 0;
	currentFPS = 60;
	drawVoxels = false;
}

void SceneMainMenu::InnitTextures()
{
	textures.resize(NUM_TEXTURES, 0);
	textures[TEXTURE_SKYBOX] = LoadTGA(L"Image//skybox.tga");
	textures[TEXTURE_GROUND] = LoadTGA(L"Image//ground.tga");
	textures[TEXTURE_CABINET1] = LoadTGA(L"Image//Cabinet1Texture.tga");
	textures[TEXTURE_CAN1] = LoadTGA(L"Image//can1.tga");
	textures[TEXTURE_CAN2] = LoadTGA(L"Image//can2.tga");
	textures[TEXTURE_CAN3] = LoadTGA(L"Image//can3.tga");
	textures[TEXTURE_CEREAL1] = LoadTGA(L"Image//cereal1.tga");
	textures[TEXTURE_CEREAL2] = LoadTGA(L"Image//cereal2.tga");
	textures[TEXTURE_CEREAL3] = LoadTGA(L"Image//cereal3.tga");
	textures[TEXTURE_PACKET1] = LoadTGA(L"Image//packet1.tga");
	textures[TEXTURE_PACKET2] = LoadTGA(L"Image//packet2.tga");
	textures[TEXTURE_PACKET3] = LoadTGA(L"Image//packet3.tga");
	textures[TEXTURE_BUILDING] = LoadTGA(L"Image//dullwhite.tga");
	textures[TEXTURE_LIFT] = LoadTGA(L"Image//blue.tga");
	textures[TEXTURE_LIFTDOOR] = LoadTGA(L"Image//liftdoor.tga");
	textures[TEXTURE_OUTERDOOR] = LoadTGA(L"Image//glassdoor_texture.tga");
	textures[TEXTURE_INNERDOOR] = LoadTGA(L"Image//glassdoor_texture.tga");
	textures[TEXTURE_TRAVELATORSUPPORT] = LoadTGA(L"Image//dullwhite.tga");
	textures[TEXTURE_TRAVELATORSLOPE] = LoadTGA(L"Image//travelatorslope_texture.tga");
	textures[TEXTURE_TRAVELATORHANDLE] = LoadTGA(L"Image//travelatorhandle_texture.tga");
	textures[TEXTURE_LARGE_FORERUNNER_FLOOR_PLATE] = LoadTGA(L"Image//large_forerunner_floor_plate.tga");
	textures[TEXTURE_PLAYBUTTON] = LoadTGA(L"Image//Quad1.tga");
	textures[TEXTURE_INSTBUTTON] = LoadTGA(L"Image//Quad2.tga");
	textures[TEXTURE_CREDITSBUTTON] = LoadTGA(L"Quad3.tga");
	textures[TEXTURE_EXITBUTTON] = LoadTGA(L"Image//Quad4.tga");
	textures[TEXTURE_BG] = LoadTGA(L"Image//BG.tga");
	textures[TEXTURE_INCREDITS] = LoadTGA(L"Image//incredits.tga");
	textures[TEXTURE_INSTRUCTIONS] = LoadTGA(L"Image//instructions.tga");
	textures[TEXTURE_INEXIT] = LoadTGA(L"Image//inexit.tga");
}

void SceneMainMenu::InnitLight()
{
	light[WORLD_LIGHT].type = Light::LIGHT_DIRECTIONAL;
	light[WORLD_LIGHT].position.Set(20, 20, 20);
	light[WORLD_LIGHT].color.Set(1, 1, 1);
	light[WORLD_LIGHT].power = 0.23;
	light[WORLD_LIGHT].kC = 1.f;
	light[WORLD_LIGHT].kL = 0.01f;
	light[WORLD_LIGHT].kQ = 0.001f;
	light[WORLD_LIGHT].cosCutoff = cos(Math::DegreeToRadian(180));
	light[WORLD_LIGHT].cosInner = cos(Math::DegreeToRadian(30));
	light[WORLD_LIGHT].exponent = 1.f;
	light[WORLD_LIGHT].spotDirection.Set(0.f, 1.f, 1.f);

	gfx.AddLight(&light[WORLD_LIGHT]);
}

void SceneMainMenu::InnitGeometry()
{
	//Initialize all meshes to NULL
	meshList.resize(NUM_GEOMETRY, NULL);

	meshList[GEO_SKYBOX] = MeshBuilder::GenerateOBJ(L"OBJ//skybox.obj");
	meshList[GEO_GROUND] = MeshBuilder::GenerateRepeatQuad(L"ground", Color(1, 1, 1), 50.f, 50.f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube(L"Cube",Color(),1,1,1);
	meshList[GEO_CABINET1] = MeshBuilder::GenerateOBJ(L"OBJ//Cabinet1.obj");
	meshList[GEO_CAN1] = MeshBuilder::GenerateOBJ(L"OBJ//can1.obj");
	meshList[GEO_CAN2] = MeshBuilder::GenerateOBJ(L"OBJ//can2.obj");
	meshList[GEO_CAN3] = MeshBuilder::GenerateOBJ(L"OBJ//can3.obj");
	meshList[GEO_CEREAL1] = MeshBuilder::GenerateOBJ(L"OBJ//cereal1.obj");
	meshList[GEO_CEREAL2] = MeshBuilder::GenerateOBJ(L"OBJ//cereal2.obj");
	meshList[GEO_CEREAL3] = MeshBuilder::GenerateOBJ(L"OBJ//cereal3.obj");
	meshList[GEO_PACKET1] = MeshBuilder::GenerateOBJ(L"OBJ//packet1.obj");
	meshList[GEO_PACKET2] = MeshBuilder::GenerateOBJ(L"OBJ//packet2.obj");
	meshList[GEO_PACKET3] = MeshBuilder::GenerateOBJ(L"OBJ//packet3.obj");
	meshList[GEO_BUILDING] = MeshBuilder::GenerateOBJ(L"OBJ//building.obj");
	meshList[GEO_LIFT] = MeshBuilder::GenerateOBJ(L"OBJ//bluelift.obj");
	meshList[GEO_LIFTDOOR] = MeshBuilder::GenerateOBJ(L"OBJ//liftdoor.obj");
	meshList[GEO_OUTERDOOR] = MeshBuilder::GenerateOBJ(L"OBJ//outerdoor.obj");
	meshList[GEO_INNERDOOR] = MeshBuilder::GenerateOBJ(L"OBJ//innerdoor.obj");
	meshList[GEO_TRAVELATORSUPPORT] = MeshBuilder::GenerateOBJ(L"OBJ//travelatorsupport.obj");
	meshList[GEO_TRAVELATORSLOPE] = MeshBuilder::GenerateOBJ(L"OBJ//travelatorslope.obj");
	meshList[GEO_TRAVELATORHANDLE] = MeshBuilder::GenerateOBJ(L"OBJ//travelatorhandle.obj");
	meshList[GEO_PLAYBUTTON] = MeshBuilder::GenerateQuad(L"play", Color(1, 1, 1), 50.f, 50.f);
	meshList[GEO_INSTBUTTON] = MeshBuilder::GenerateQuad(L"instructions", Color(1, 1, 1), 50.f, 50.f);
	meshList[GEO_CREDITSBUTTON] = MeshBuilder::GenerateQuad(L"credits", Color(1, 1, 1), 50.f, 50.f);
	meshList[GEO_EXITBUTTON] = MeshBuilder::GenerateQuad(L"exit", Color(1, 1, 1), 50.f, 50.f);
	meshList[GEO_BG] = MeshBuilder::GenerateQuad(L"BG", Color(1, 1, 1), 50.f, 50.f);
	meshList[GEO_INCREDITS] = MeshBuilder::GenerateQuad(L"incredits", Color(1, 1, 1), 50.f, 50.f);
	meshList[GEO_INSTRUCTIONS] = MeshBuilder::GenerateQuad(L"incredits", Color(1, 1, 1), 50.f, 50.f);
	meshList[GEO_INEXIT] = MeshBuilder::GenerateQuad(L"incredits", Color(1, 1, 1), 50.f, 50.f);
}

void SceneMainMenu::InnitDraws()
{
	drawOrders.resize(NUM_DRAWS + meshList.size() - NUM_GEOMETRY);

	//skybox will be the main draw order that all other draw orders are children of
	drawOrders[DRAW_MAIN].geometry = NULL;
	drawOrders[DRAW_MAIN].enableLight = false;

	//positions are offset a little from their proper position because of floating point error

	drawOrders[DRAW_SKYBOX].geometry = meshList[GEO_SKYBOX];
	drawOrders[DRAW_SKYBOX].transform.translate.Set(0,0,0);
	drawOrders[DRAW_SKYBOX].transform.scale.Set(10000,10000,10000);
	drawOrders[DRAW_SKYBOX].material.SetTextureTo(textures[TEXTURE_SKYBOX]);
	drawOrders[DRAW_SKYBOX].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_SKYBOX].enableLight = false;

	drawOrders[DRAW_GROUND].geometry = meshList[GEO_GROUND];
	drawOrders[DRAW_GROUND].transform.translate.Set(0,0,0);
	drawOrders[DRAW_GROUND].material.SetTextureTo(textures[TEXTURE_GROUND]);
	drawOrders[DRAW_GROUND].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_GROUND].enableLight = false;

	drawOrders[DRAW_PLAYER].geometry = meshList[GEO_CUBE];
	drawOrders[DRAW_PLAYER].transform.translate.Set(0,0.1,0);
	drawOrders[DRAW_PLAYER].material.SetTextureTo(textures[TEXTURE_LARGE_FORERUNNER_FLOOR_PLATE]);
	drawOrders[DRAW_PLAYER].SetTerminalVelocityTo(Vector3(60,60,60));
	drawOrders[DRAW_PLAYER].staticFriction = 0.03;
	drawOrders[DRAW_PLAYER].mass = 1;
	drawOrders[DRAW_PLAYER].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_PLAYER].enableLight = false;

	drawOrders[DRAW_CABINET1].geometry = meshList[GEO_CABINET1];
	drawOrders[DRAW_CABINET1].transform.translate.Set(10,0.1,0);
	drawOrders[DRAW_CABINET1].material.SetTextureTo(textures[TEXTURE_CABINET1]);
	drawOrders[DRAW_CABINET1].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_CABINET1].enableLight = false;

	drawOrders[DRAW_CAN1].geometry = meshList[GEO_CAN1];
	drawOrders[DRAW_CAN1].transform.translate.Set(15,0.1,0);
	drawOrders[DRAW_CAN1].material.SetTextureTo(textures[TEXTURE_CAN1]);
	drawOrders[DRAW_CAN1].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_CAN1].enableLight = false;

	drawOrders[DRAW_CAN2].geometry = meshList[GEO_CAN2];
	drawOrders[DRAW_CAN2].transform.translate.Set(20,0.1,0);
	drawOrders[DRAW_CAN2].material.SetTextureTo(textures[TEXTURE_CAN2]);
	drawOrders[DRAW_CAN2].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_CAN2].enableLight = false;

	drawOrders[DRAW_CAN3].geometry = meshList[GEO_CAN3];
	drawOrders[DRAW_CAN3].transform.translate.Set(25,0.1,0);
	drawOrders[DRAW_CAN3].material.SetTextureTo(textures[TEXTURE_CAN3]);
	drawOrders[DRAW_CAN3].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_CAN3].enableLight = false;

	drawOrders[DRAW_CEREAL1].geometry = meshList[GEO_CEREAL1];
	drawOrders[DRAW_CEREAL1].transform.translate.Set(30,0.1,0);
	drawOrders[DRAW_CEREAL1].material.SetTextureTo(textures[TEXTURE_CEREAL1]);
	drawOrders[DRAW_CEREAL1].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_CEREAL1].enableLight = false;

	drawOrders[DRAW_CEREAL2].geometry = meshList[GEO_CEREAL2];
	drawOrders[DRAW_CEREAL2].transform.translate.Set(35,0.1,0);
	drawOrders[DRAW_CEREAL2].material.SetTextureTo(textures[TEXTURE_CEREAL2]);
	drawOrders[DRAW_CEREAL2].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_CEREAL2].enableLight = false;

	drawOrders[DRAW_CEREAL3].geometry = meshList[GEO_CEREAL3];
	drawOrders[DRAW_CEREAL3].transform.translate.Set(40,0.1,0);
	drawOrders[DRAW_CEREAL3].material.SetTextureTo(textures[TEXTURE_CEREAL3]);
	drawOrders[DRAW_CEREAL3].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_CEREAL3].enableLight = false;

	drawOrders[DRAW_PACKET1].geometry = meshList[GEO_PACKET1];
	drawOrders[DRAW_PACKET1].transform.translate.Set(45,0.1,0);
	drawOrders[DRAW_PACKET1].material.SetTextureTo(textures[TEXTURE_PACKET1]);
	drawOrders[DRAW_PACKET1].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_PACKET1].enableLight = false;

	drawOrders[DRAW_PACKET2].geometry = meshList[GEO_PACKET2];
	drawOrders[DRAW_PACKET2].transform.translate.Set(50,0.1,0);
	drawOrders[DRAW_PACKET2].material.SetTextureTo(textures[TEXTURE_PACKET2]);
	drawOrders[DRAW_PACKET2].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_PACKET2].enableLight = false;

	drawOrders[DRAW_PACKET3].geometry = meshList[GEO_PACKET3];
	drawOrders[DRAW_PACKET3].transform.translate.Set(55,0.1,0);
	drawOrders[DRAW_PACKET3].material.SetTextureTo(textures[TEXTURE_PACKET3]);
	drawOrders[DRAW_PACKET3].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_PACKET3].enableLight = false;

	drawOrders[DRAW_BUILDING].geometry = meshList[GEO_BUILDING];
	drawOrders[DRAW_BUILDING].transform.translate.Set(0,0.1,-30);
	drawOrders[DRAW_BUILDING].material.SetTextureTo(textures[TEXTURE_BUILDING]);
	drawOrders[DRAW_BUILDING].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_BUILDING].enableLight = false;

	drawOrders[DRAW_LIFT_1].geometry = meshList[GEO_LIFT];
	drawOrders[DRAW_LIFT_1].transform.translate.Set(15.0,5.5,-101.6);
	drawOrders[DRAW_LIFT_1].material.SetTextureTo(textures[TEXTURE_LIFT]);
	drawOrders[DRAW_LIFT_1].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_LIFT_1].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_LIFT_1].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_LIFT_1].material.SetShininessTo(20);
	drawOrders[DRAW_LIFT_1].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_LIFT_1].enableLight = true;

	drawOrders[DRAW_LIFT_2].geometry = meshList[GEO_LIFT];
	drawOrders[DRAW_LIFT_2].transform.translate.Set(15.0,15.6,-101.6);
	drawOrders[DRAW_LIFT_2].material.SetTextureTo(textures[TEXTURE_LIFT]);
	drawOrders[DRAW_LIFT_2].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_LIFT_2].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_LIFT_2].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_LIFT_2].material.SetShininessTo(20);
	drawOrders[DRAW_LIFT_2].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_LIFT_2].enableLight = true;

	drawOrders[DRAW_LIFTDOOR_1_LEFT].geometry = meshList[GEO_LIFTDOOR];
	drawOrders[DRAW_LIFTDOOR_1_LEFT].transform.translate.Set(14.0,5,-98.6);
	drawOrders[DRAW_LIFTDOOR_1_LEFT].material.SetTextureTo(textures[TEXTURE_LIFTDOOR]);
	drawOrders[DRAW_LIFTDOOR_1_LEFT].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_LIFTDOOR_1_LEFT].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_LIFTDOOR_1_LEFT].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_LIFTDOOR_1_LEFT].material.SetShininessTo(20);
	drawOrders[DRAW_LIFTDOOR_1_LEFT].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_LIFTDOOR_1_LEFT].enableLight = true;

	drawOrders[DRAW_LIFTDOOR_1_RIGHT].geometry = meshList[GEO_LIFTDOOR];
	drawOrders[DRAW_LIFTDOOR_1_RIGHT].transform.translate.Set(16.0,5,-98.6);
	drawOrders[DRAW_LIFTDOOR_1_RIGHT].material.SetTextureTo(textures[TEXTURE_LIFTDOOR]);
	drawOrders[DRAW_LIFTDOOR_1_RIGHT].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_LIFTDOOR_1_RIGHT].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_LIFTDOOR_1_RIGHT].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_LIFTDOOR_1_RIGHT].material.SetShininessTo(20);
	drawOrders[DRAW_LIFTDOOR_1_RIGHT].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_LIFTDOOR_1_RIGHT].enableLight = true;

	drawOrders[DRAW_LIFTDOOR_2_LEFT].geometry = meshList[GEO_LIFTDOOR];
	drawOrders[DRAW_LIFTDOOR_2_LEFT].transform.translate.Set(14.0,15.1,-98.6);
	drawOrders[DRAW_LIFTDOOR_2_LEFT].material.SetTextureTo(textures[TEXTURE_LIFTDOOR]);
	drawOrders[DRAW_LIFTDOOR_2_LEFT].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_LIFTDOOR_2_LEFT].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_LIFTDOOR_2_LEFT].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_LIFTDOOR_2_LEFT].material.SetShininessTo(20);
	drawOrders[DRAW_LIFTDOOR_2_LEFT].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_LIFTDOOR_2_LEFT].enableLight = true;

	drawOrders[DRAW_LIFTDOOR_2_RIGHT].geometry = meshList[GEO_LIFTDOOR];
	drawOrders[DRAW_LIFTDOOR_2_RIGHT].transform.translate.Set(16.0,15.1,-98.6);
	drawOrders[DRAW_LIFTDOOR_2_RIGHT].material.SetTextureTo(textures[TEXTURE_LIFTDOOR]);
	drawOrders[DRAW_LIFTDOOR_2_RIGHT].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_LIFTDOOR_2_RIGHT].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_LIFTDOOR_2_RIGHT].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_LIFTDOOR_2_RIGHT].material.SetShininessTo(20);
	drawOrders[DRAW_LIFTDOOR_2_RIGHT].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_LIFTDOOR_2_RIGHT].enableLight = true;
	//Draw Door
	drawOrders[DRAW_OUTERDOOR_1_RIGHT].geometry = meshList[GEO_OUTERDOOR];
	drawOrders[DRAW_OUTERDOOR_1_RIGHT].transform.translate.Set(2,4.5,-8.6);
	drawOrders[DRAW_OUTERDOOR_1_RIGHT].material.SetTextureTo(textures[TEXTURE_OUTERDOOR]);
	drawOrders[DRAW_OUTERDOOR_1_RIGHT].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_OUTERDOOR_1_RIGHT].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_OUTERDOOR_1_RIGHT].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_OUTERDOOR_1_RIGHT].material.SetShininessTo(20);
	drawOrders[DRAW_OUTERDOOR_1_RIGHT].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_OUTERDOOR_1_RIGHT].enableLight = true;

	drawOrders[DRAW_OUTERDOOR_1_LEFT].geometry = meshList[GEO_OUTERDOOR];
	drawOrders[DRAW_OUTERDOOR_1_LEFT].transform.translate.Set(-2,4.5,-8.6);
	drawOrders[DRAW_OUTERDOOR_1_LEFT].transform.rotate.Set(0,180,0);
	drawOrders[DRAW_OUTERDOOR_1_LEFT].material.SetTextureTo(textures[TEXTURE_OUTERDOOR]);
	drawOrders[DRAW_OUTERDOOR_1_LEFT].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_OUTERDOOR_1_LEFT].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_OUTERDOOR_1_LEFT].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_OUTERDOOR_1_LEFT].material.SetShininessTo(20);
	drawOrders[DRAW_OUTERDOOR_1_LEFT].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_OUTERDOOR_1_LEFT].enableLight = true;

	drawOrders[DRAW_OUTERDOOR_2_RIGHT].geometry = meshList[GEO_OUTERDOOR];
	drawOrders[DRAW_OUTERDOOR_2_RIGHT].transform.translate.Set(-9,4.5,-105.4);
	drawOrders[DRAW_OUTERDOOR_2_RIGHT].material.SetTextureTo(textures[TEXTURE_OUTERDOOR]);
	drawOrders[DRAW_OUTERDOOR_2_RIGHT].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_OUTERDOOR_2_RIGHT].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_OUTERDOOR_2_RIGHT].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_OUTERDOOR_2_RIGHT].material.SetShininessTo(20);
	drawOrders[DRAW_OUTERDOOR_2_RIGHT].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_OUTERDOOR_2_RIGHT].enableLight = true;

	drawOrders[DRAW_OUTERDOOR_2_LEFT].geometry = meshList[GEO_OUTERDOOR];
	drawOrders[DRAW_OUTERDOOR_2_LEFT].transform.translate.Set(-13,4.5,-105.4);
	drawOrders[DRAW_OUTERDOOR_2_LEFT].transform.rotate.Set(0,180,0);
	drawOrders[DRAW_OUTERDOOR_2_LEFT].material.SetTextureTo(textures[TEXTURE_OUTERDOOR]);
	drawOrders[DRAW_OUTERDOOR_2_LEFT].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_OUTERDOOR_2_LEFT].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_OUTERDOOR_2_LEFT].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_OUTERDOOR_2_LEFT].material.SetShininessTo(20);
	drawOrders[DRAW_OUTERDOOR_2_LEFT].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_OUTERDOOR_2_LEFT].enableLight = true;

	drawOrders[DRAW_INNERDOOR_1].geometry = meshList[GEO_INNERDOOR];
	drawOrders[DRAW_INNERDOOR_1].transform.translate.Set(-17.5,4.5,-19.6);
	drawOrders[DRAW_INNERDOOR_1].transform.rotate.Set(0,180,0);
	drawOrders[DRAW_INNERDOOR_1].material.SetTextureTo(textures[TEXTURE_INNERDOOR]);
	drawOrders[DRAW_INNERDOOR_1].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_INNERDOOR_1].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_INNERDOOR_1].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_INNERDOOR_1].material.SetShininessTo(20);
	drawOrders[DRAW_INNERDOOR_1].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_INNERDOOR_1].enableLight = true;

	drawOrders[DRAW_INNERDOOR_2].geometry = meshList[GEO_INNERDOOR];
	drawOrders[DRAW_INNERDOOR_2].transform.translate.Set(-17.5,14.5,-19.6);
	drawOrders[DRAW_INNERDOOR_2].transform.rotate.Set(0,180,0);
	drawOrders[DRAW_INNERDOOR_2].material.SetTextureTo(textures[TEXTURE_INNERDOOR]);
	drawOrders[DRAW_INNERDOOR_2].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_INNERDOOR_2].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_INNERDOOR_2].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_INNERDOOR_2].material.SetShininessTo(20);
	drawOrders[DRAW_INNERDOOR_2].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_INNERDOOR_2].enableLight = true;

	//Draw Travelator
	drawOrders[DRAW_TRAVELATORSUPPORT_UP].geometry = meshList[GEO_TRAVELATORSUPPORT];
	drawOrders[DRAW_TRAVELATORSUPPORT_UP].transform.translate.Set(-2,7.1,-21.6);
	drawOrders[DRAW_TRAVELATORSUPPORT_UP].material.SetTextureTo(textures[TEXTURE_TRAVELATORSUPPORT]);
	drawOrders[DRAW_TRAVELATORSUPPORT_UP].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_TRAVELATORSUPPORT_UP].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_TRAVELATORSUPPORT_UP].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_TRAVELATORSUPPORT_UP].material.SetShininessTo(20);
	drawOrders[DRAW_TRAVELATORSUPPORT_UP].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_TRAVELATORSUPPORT_UP].enableLight = true;

	drawOrders[DRAW_TRAVELATORSLOPE_UP].geometry = meshList[GEO_TRAVELATORSLOPE];
	drawOrders[DRAW_TRAVELATORSLOPE_UP].transform.translate.Set(-2,5.9,-21.6);
	drawOrders[DRAW_TRAVELATORSLOPE_UP].material.SetTextureTo(textures[TEXTURE_TRAVELATORSLOPE]);
	drawOrders[DRAW_TRAVELATORSLOPE_UP].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_TRAVELATORSLOPE_UP].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_TRAVELATORSLOPE_UP].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_TRAVELATORSLOPE_UP].material.SetShininessTo(20);
	drawOrders[DRAW_TRAVELATORSLOPE_UP].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_TRAVELATORSLOPE_UP].enableLight = true;

	drawOrders[DRAW_TRAVELATORHANDLE_UP_1].geometry = meshList[GEO_TRAVELATORHANDLE];
	drawOrders[DRAW_TRAVELATORHANDLE_UP_1].transform.translate.Set(-1.8,7.8,-20.4);
	drawOrders[DRAW_TRAVELATORHANDLE_UP_1].material.SetTextureTo(textures[TEXTURE_TRAVELATORHANDLE]);
	drawOrders[DRAW_TRAVELATORHANDLE_UP_1].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_TRAVELATORHANDLE_UP_1].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_TRAVELATORHANDLE_UP_1].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_TRAVELATORHANDLE_UP_1].material.SetShininessTo(20);
	drawOrders[DRAW_TRAVELATORHANDLE_UP_1].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_TRAVELATORHANDLE_UP_1].enableLight = true;

	drawOrders[DRAW_TRAVELATORHANDLE_UP_2].geometry = meshList[GEO_TRAVELATORHANDLE];
	drawOrders[DRAW_TRAVELATORHANDLE_UP_2].transform.translate.Set(-1.8,7.8,-22.65);
	drawOrders[DRAW_TRAVELATORHANDLE_UP_2].material.SetTextureTo(textures[TEXTURE_TRAVELATORHANDLE]);
	drawOrders[DRAW_TRAVELATORHANDLE_UP_2].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_TRAVELATORHANDLE_UP_2].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_TRAVELATORHANDLE_UP_2].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_TRAVELATORHANDLE_UP_2].material.SetShininessTo(20);
	drawOrders[DRAW_TRAVELATORHANDLE_UP_2].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_TRAVELATORHANDLE_UP_2].enableLight = true;

	drawOrders[DRAW_TRAVELATORSUPPORT_DOWN].geometry = meshList[GEO_TRAVELATORSUPPORT];
	drawOrders[DRAW_TRAVELATORSUPPORT_DOWN].transform.translate.Set(-2,7.1,-24.6);
	drawOrders[DRAW_TRAVELATORSUPPORT_DOWN].material.SetTextureTo(textures[TEXTURE_TRAVELATORSUPPORT]);
	drawOrders[DRAW_TRAVELATORSUPPORT_DOWN].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_TRAVELATORSUPPORT_DOWN].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_TRAVELATORSUPPORT_DOWN].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_TRAVELATORSUPPORT_DOWN].material.SetShininessTo(20);
	drawOrders[DRAW_TRAVELATORSUPPORT_DOWN].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_TRAVELATORSUPPORT_DOWN].enableLight = true;

	drawOrders[DRAW_TRAVELATORSLOPE_DOWN].geometry = meshList[GEO_TRAVELATORSLOPE];
	drawOrders[DRAW_TRAVELATORSLOPE_DOWN].transform.translate.Set(-2,5.9,-24.6);
	drawOrders[DRAW_TRAVELATORSLOPE_DOWN].material.SetTextureTo(textures[TEXTURE_TRAVELATORSLOPE]);
	drawOrders[DRAW_TRAVELATORSLOPE_DOWN].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_TRAVELATORSLOPE_DOWN].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_TRAVELATORSLOPE_DOWN].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_TRAVELATORSLOPE_DOWN].material.SetShininessTo(20);
	drawOrders[DRAW_TRAVELATORSLOPE_DOWN].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_TRAVELATORSLOPE_DOWN].enableLight = true;

	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_1].geometry = meshList[GEO_TRAVELATORHANDLE];
	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_1].transform.translate.Set(-1.8,7.8,-23.4);
	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_1].material.SetTextureTo(textures[TEXTURE_TRAVELATORHANDLE]);
	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_1].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_1].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_1].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_1].material.SetShininessTo(20);
	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_1].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_1].enableLight = true;

	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_2].geometry = meshList[GEO_TRAVELATORHANDLE];
	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_2].transform.translate.Set(-1.8,7.8,-25.65);
	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_2].material.SetTextureTo(textures[TEXTURE_TRAVELATORHANDLE]);
	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_2].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_2].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_2].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_2].material.SetShininessTo(20);
	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_2].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_TRAVELATORHANDLE_DOWN_2].enableLight = true;

	drawOrders[DRAW_TROLLEY].geometry = meshList[GEO_TROLLEY];
	drawOrders[DRAW_TROLLEY].transform.translate.Set(0,0.1,0);
	drawOrders[DRAW_TROLLEY].material.SetTextureTo(textures[TEXTURE_TROLLEY]);
	drawOrders[DRAW_TROLLEY].material.SetAmbientTo(1,1,1);
	drawOrders[DRAW_TROLLEY].material.SetDiffuseTo(1,1,1);
	drawOrders[DRAW_TROLLEY].material.SetSpecularTo(1,1,1);
	drawOrders[DRAW_TROLLEY].material.SetShininessTo(20);
	drawOrders[DRAW_TROLLEY].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_TROLLEY].enableLight = true;

	//main menu
	drawOrders[DRAW_PLAYBUTTON].geometry = meshList[GEO_PLAYBUTTON];
	drawOrders[DRAW_PLAYBUTTON].transform.translate.Set(40,0.1,0);
	drawOrders[DRAW_PLAYBUTTON].material.SetTextureTo(textures[TEXTURE_PLAYBUTTON]);
	drawOrders[DRAW_PLAYBUTTON].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_PLAYBUTTON].enableLight = false;

	drawOrders[DRAW_INSTBUTTON].geometry = meshList[GEO_INSTBUTTON];
	drawOrders[DRAW_INSTBUTTON].transform.translate.Set(40,0.1,0);
	drawOrders[DRAW_INSTBUTTON].material.SetTextureTo(textures[TEXTURE_INSTBUTTON]);
	drawOrders[DRAW_INSTBUTTON].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_INSTBUTTON].enableLight = false;

	drawOrders[DRAW_CREDITSBUTTON].geometry = meshList[GEO_CREDITSBUTTON];
	drawOrders[DRAW_CREDITSBUTTON].transform.translate.Set(40,0.1,0);
	drawOrders[DRAW_CREDITSBUTTON].material.SetTextureTo(textures[TEXTURE_CREDITSBUTTON]);
	drawOrders[DRAW_CREDITSBUTTON].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_CREDITSBUTTON].enableLight = false;

	drawOrders[DRAW_EXITBUTTON].geometry = meshList[GEO_EXITBUTTON];
	drawOrders[DRAW_EXITBUTTON].transform.translate.Set(40,0.1,0);
	drawOrders[DRAW_EXITBUTTON].material.SetTextureTo(textures[TEXTURE_EXITBUTTON]);
	drawOrders[DRAW_EXITBUTTON].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_EXITBUTTON].enableLight = false;

	drawOrders[DRAW_BG].geometry = meshList[GEO_BG];
	drawOrders[DRAW_BG].transform.translate.Set(40,0.1,0);
	drawOrders[DRAW_BG].material.SetTextureTo(textures[TEXTURE_BG]);
	drawOrders[DRAW_BG].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_BG].enableLight = false;

	drawOrders[DRAW_INCREDITS].geometry = meshList[GEO_INCREDITS];
	drawOrders[DRAW_INCREDITS].transform.translate.Set(40,0.1,0);
	drawOrders[DRAW_INCREDITS].material.SetTextureTo(textures[TEXTURE_INCREDITS]);
	drawOrders[DRAW_INCREDITS].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_INCREDITS].enableLight = false;

	drawOrders[DRAW_INSTRUCTIONS].geometry = meshList[GEO_INSTRUCTIONS];
	drawOrders[DRAW_INSTRUCTIONS].transform.translate.Set(40,0.1,0);
	drawOrders[DRAW_INSTRUCTIONS].material.SetTextureTo(textures[TEXTURE_INSTRUCTIONS]);
	drawOrders[DRAW_INSTRUCTIONS].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_INSTRUCTIONS].enableLight = false;

	drawOrders[DRAW_INEXIT].geometry = meshList[GEO_CEREAL3];
	drawOrders[DRAW_INEXIT].transform.translate.Set(40,0.1,0);
	drawOrders[DRAW_INEXIT].material.SetTextureTo(textures[TEXTURE_CEREAL3]);
	drawOrders[DRAW_INEXIT].SetParentAs(&drawOrders[DRAW_MAIN]);
	drawOrders[DRAW_INEXIT].enableLight = false;
}

void SceneMainMenu::InnitVoxels()
{
	drawOrders[DRAW_PLAYER].GenerateVoxels();
	drawOrders[DRAW_GROUND].GenerateVoxels();
}

void SceneMainMenu::InnitForces()
{
	Vector3 accelerationDueToGravity(0, -50.f, 0);
	for(std::vector<drawOrder>::iterator draw = drawOrders.begin(); draw != drawOrders.end(); draw++)
	{
		//draw->AddForce(accelerationDueToGravity * draw->mass);
	}
}

bool SceneMainMenu::Update(const double dt)
{
	float rotationspeed = 2;
	deltaTime = dt;
	accumulatingDT += deltaTime;
	frameCounter++;
	const double undateInterval = 0.2;
	if(accumulatingDT > undateInterval)
	{
		currentFPS = frameCounter / accumulatingDT;
		accumulatingDT -= undateInterval;
		frameCounter = 0;
	}
	if(keyboard.isKeyPressed(VK_ESCAPE))
	{
		return true;
	}

	DoUserInput();
	UpdateDraws();
	UpdateView();
	UpdateLight();
	return gameQuit;
}

void SceneMainMenu::UpdateLogic()
{
	if(state==START)
	{
		gameQuit=false;
	}
	else if(state==INST)
	{
		gameQuit=false;
	}
	else if(state==CREDITS)
	{
		gameQuit=false;
	}
	else if(state==CHOOSETOEXIT)
	{
		gameQuit=false;
	}
	else if(state==MAINMENU)
	{
		
		gameQuit=false;
		if(option==1)
		{
			state=START;
		}
		else if(option==2)
		{
			state=INST;
		}
		else if(option==3)
		{
			state=CREDITS;
		}
		else if(option==4)
		{
			state=CHOOSETOEXIT;
		}
	}
}

void SceneMainMenu::UpdateView()
{
	//positions are offset a little from their proper position because of floating point error
	drawOrders[DRAW_SKYBOX].transform.translate = Vector3(0,0,0) + camera.ReturnPosition();

	if(isFrog == false)
	{
		//camera.Translate(drawOrders[DRAW_PLAYER].transform.translate - camera.ReturnPosition() + Vector3(0, 10, 0));
	}
	else
	{
		//camera.Translate(drawOrders[DRAW_PLAYER].transform.translate - camera.ReturnPosition() + Vector3(0, 3, 0));
	}
	float player_rotationY = camera.GetRotation().y - drawOrders[DRAW_PLAYER].transform.rotate.y;
	float player_current_frame_rotationY = player_rotationY / 25;
	drawOrders[DRAW_PLAYER].transform.rotate.y += player_current_frame_rotationY;
	gfx.SetViewAt(camera);
}

void SceneMainMenu::UpdateLight()
{
	gfx.UpdateLights();
}

void SceneMainMenu::UpdateDraws()
{
	//where forces are applied
	for(std::vector<drawOrder>::iterator draw = drawOrders.begin(); draw != drawOrders.end(); draw++)
	{
		//an object has 0 mass if it is infinitely heavy and forces will barely have any effect on it including gravity. This is totally how physics work
		draw->UpdateVelocity(deltaTime);
		draw->UpdateForcesTo(deltaTime);
	}

	//where we do collision
	//for(std::vector<drawOrder>::iterator draw1 = drawOrders.begin(); draw1 != drawOrders.end(); draw1++)
	//{
	//	//check the object with every other object after it. Objects that came before are skipped to prevent checking collision twice with the same object
	//	for(std::vector<drawOrder>::iterator draw2 = draw1 + 1; draw2 != drawOrders.end(); draw2++)
	//	{
	//		if(draw1->velocity.IsZero() && draw2->velocity.IsZero())
	//		{
	//			continue;
	//		}
	//		bool CollisionIsDone = false;

	//		//check the individual voxel each object has. If one pair collides, collision is applied to the objects as a whole we break out of the loop
	//		for(std::vector<Voxel>::iterator voxel1 = draw1->voxels.begin(); voxel1 != draw1->voxels.end(); voxel1++)
	//		{
	//			for(std::vector<Voxel>::iterator voxel2 = draw2->voxels.begin(); voxel2 != draw2->voxels.end(); voxel2++)
	//			{
	//				CollisionIsDone = collisionSystem.CheckThisCollision(&*voxel1, &*voxel2, deltaTime);
	//			}
	//		}
	//	}
	//}
	collisionSystem.CheckThisCollision(&drawOrders[DRAW_GROUND],&drawOrders[DRAW_PLAYER],deltaTime);
	collisionSystem.ResolveAllCollisionsAccordingTo(deltaTime);

	//draws are finally updated after processing
	for(std::vector<drawOrder>::iterator draw = drawOrders.begin(); draw != drawOrders.end(); draw++)
	{
		draw->UpdateTo(deltaTime);
	}
}

void SceneMainMenu::Render()
{
	//clear depth and color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnableVertexAttribArray(0); // 1st attribute buffer :vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer : colors
	glEnableVertexAttribArray(2); // 3rd attribute : normals
	glEnableVertexAttribArray(3); // 4th attribute : UV coordinates

	if(drawVoxels)
	{
		Material material;
		drawOrder draw_cube;
		draw_cube.geometry = meshList[GEO_CUBE];
		draw_cube.enableLight = false;
		draw_cube.material = material;
		for(std::vector<drawOrder>::iterator draw = drawOrders.begin(); draw != drawOrders.end(); draw++)
		{
			//check the individual voxel each object has. If one pair collides, collision is applied to the objects as a whole we break out of the loop
			for(std::vector<Voxel>::iterator voxel = draw->voxels.begin(); voxel != draw->voxels.end(); voxel++)
			{
				Mtx44 translate, scale;
				translate.SetToTranslation(voxel->GetPosition());
				scale.SetToScale(Voxel::GetSize(), Voxel::GetSize(), Voxel::GetSize());
				gfx.RenderMesh(draw_cube, translate * scale);
			}
		}
	}
	else
	{
		drawOrders[DRAW_MAIN].Execute(gfx);
	}
	gfx.RenderQuadOnScreen(&drawOrders[DRAW_BG]);
	if(state=MAINMENU)
	{
		gfx.RenderQuadOnScreen(&drawOrders[DRAW_PLAYBUTTON]);
		gfx.RenderQuadOnScreen(&drawOrders[DRAW_INSTBUTTON]);
		gfx.RenderQuadOnScreen(&drawOrders[DRAW_CREDITSBUTTON]);
		gfx.RenderQuadOnScreen(&drawOrders[DRAW_EXITBUTTON]);
	}
	else if(state==START)
	{

	}
	else if(state==INST)
	{
		gfx.RenderQuadOnScreen(&drawOrders[DRAW_INSTRUCTIONS]);
	}
	else if(state==CREDITS)
	{
		gfx.RenderQuadOnScreen(&drawOrders[DRAW_INCREDITS]);
	}
	else if(state==CHOOSETOEXIT)
	{
		gfx.RenderQuadOnScreen(&drawOrders[DRAW_INEXIT]);
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

void SceneMainMenu::Exit()
{
	// Cleanup here
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i] != NULL)
		{
			delete meshList[i];
		}
	}

	for(std::vector<unsigned>::iterator textureID = textures.begin(); textureID != textures.end(); ++textureID)
	{
		if(*textureID > 0)
		{
			glDeleteTextures(1, &*textureID);
		}
	}
}

void SceneMainMenu::DoUserInput()
{
	double mouseX;
	double mouseY;
	mouse.Update(mouseX, mouseY);
	const int CAMERA_SPEED = 5;
	camera.Rotate(0, -mouseX, -mouseY);
	playerAcceleration.SetZero();
	double movingSpeed = 5;

	if(keyboard.isKeyPressed('1'))
	{
		glEnable(GL_CULL_FACE);
	}
	if(keyboard.isKeyPressed('2'))
	{
		glDisable(GL_CULL_FACE);
	}
	if(keyboard.isKeyPressed('3'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if(keyboard.isKeyPressed('4'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if(keyboard.isKeyPressed('5'))
	{
		drawVoxels = !drawVoxels;
	}
	if (keyboard.isKeyPressed('I'))
	{
		if(isFrog == false)
		{
			player = new PlayerFrog;
			isFrog = true;
		}
		else
		{
			player = new PlayerHuman;
			isFrog = false;
		}
	}
	if(keyboard.isKeyHold('W') || keyboard.isKeyHold('S') || keyboard.isKeyHold('A') || keyboard.isKeyHold('D'))
	{
		if (keyboard.isKeyHold('W'))
		{
			playerAcceleration += player->MoveForward(camera, movingSpeed);
		}
		if (keyboard.isKeyHold('S'))
		{
			playerAcceleration += player->MoveBackward(camera, movingSpeed);
		}
		if (keyboard.isKeyHold('A'))
		{
			playerAcceleration += player->MoveLeft(camera, movingSpeed);
		}
		if (keyboard.isKeyHold('D'))
		{
			playerAcceleration += player->MoveRight(camera, movingSpeed);
		}
		/*if(isFrog == true && isJumping == false && isFalling == false)
		{
			isJumping = true;
		}*/
	}
	//Jump
	/*if (keyboard.isKeyHold(VK_SPACE) && isJumping == false && isFalling == false && isFrog == false)
	{
		isJumping = true;
	}*/
	/*
	if (keyboard.isKeyHold('O'))
	{	
		Vector3 tempVector;
		tempVector.Set(0, 50, 0);
		playerAcceleration += tempVector;
	}
	if (keyboard.isKeyHold('P'))
	{
		Vector3 tempVector;
		tempVector.Set(0, -50, 0);
		playerAcceleration += tempVector;
	}
	*/
	//Ignore
	if (keyboard.isKeyHold(VK_UP))
	{
		camera.Move(10.0f * deltaTime * CAMERA_SPEED, 0.0f, 0.0f);
	}
	if (keyboard.isKeyHold(VK_LEFT))
	{
		camera.Move(0.0f, 0.0f, -10.0f * deltaTime * CAMERA_SPEED);
	}
	if (keyboard.isKeyHold(VK_DOWN))
	{
		camera.Move(-10.0f * deltaTime * CAMERA_SPEED, 0.0f, 0.0f);
	}
	if (keyboard.isKeyHold(VK_RIGHT))
	{
		camera.Move(0.0f, 0.0f, 10.0f * deltaTime * CAMERA_SPEED);
	}
	if (keyboard.isKeyHold(VK_SPACE))
	{
		camera.Move(0,10 * deltaTime * CAMERA_SPEED,0);
	}
	if (keyboard.isKeyHold(VK_CONTROL))
	{
		camera.Move(0,-10 * deltaTime * CAMERA_SPEED,0);
	}

	//Jump
	if(isJumping == true)
	{
		if(jumpedHeight < 700 && isFalling == false)
		{
			Vector3 tempVector;
			tempVector.Set(0, 100, 0);
			playerAcceleration += tempVector;
			jumpedHeight += 100 - 50;
		}
		else
		{
			isJumping = false;
			isFalling = true;
			jumpedHeight = 700;
		}
	}
	if(isFalling == true)
	{
		if(jumpedHeight > 0)
		{
			jumpedHeight -= 20;
		}
		else
		{
				isFalling = false;
			jumpedHeight = 0;
		}
	}
	//playerAcceleration += player->Update(camera);
	Force playerForce;
	playerForce.SetLifespanTo(0.0001);
	playerForce.SetVector(playerAcceleration);
	drawOrders[DRAW_PLAYER].AddForce(playerForce);
}