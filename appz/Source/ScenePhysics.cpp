#include "ScenePhysics.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "LoadTGA.h"

ScenePhysics::ScenePhysics(Keyboard& keyboard, GLMouse& mouse, Sound& snd, Graphics& gfx)
	:
Scene(keyboard, mouse, snd, gfx)
{
}

ScenePhysics::~ScenePhysics(void)
{
}

void ScenePhysics::Init()
{
	InnitLight();
	InnitTextures();
	InnitSounds();
	InnitGeometry();
	InnitDraws();
	InnitVoxels();
	InnitForces();
	InnitLogic();

	camera.Init(Vector3(21.7, 5, 68.3), Vector3(1, 0, 0), Vector3(0, 1, 0));
	gfx.SetProjectionTo(45.f, 4.f / 3.f, 0.1f, 90000.f);
	gfx.InitText(L"Image//kitten_bri.tga");

	snd.playSound("ready");
}

void ScenePhysics::InnitDitact()
{
}

void ScenePhysics::InnitSounds()
{
	snd.loadWave("ready", "sound//ready.wav");
	snd.loadWave("didact", "sound//didact.wav");
	snd.loadWave("sneaky", "sound//sneaky.wav");
	snd.loadWave("pure", "sound//pure.wav");
}

void ScenePhysics::InnitLogic()
{
	frameCounter = 0;
	accumulatingDT = 0;
	currentFPS = 60;
	drawVoxels = false;
	didactIsSummoned = false;
}

void ScenePhysics::InnitTextures()
{
	textures.resize(NUM_TEXTURES, 0);
	textures[TEXTURE_BACK] = LoadTGA(L"Image//back.tga");
	textures[TEXTURE_BOTTOM] = LoadTGA(L"Image//bottom.tga");
	textures[TEXTURE_DIDACT] = LoadTGA(L"Image//didact.tga");
	textures[TEXTURE_DOOR] = LoadTGA(L"Image//door.tga");
	textures[TEXTURE_ELECTRONIC_CIRCUIT] = LoadTGA(L"Image//electronic_circuit.tga");
	textures[TEXTURE_FOOTBALL_FIELD] = LoadTGA(L"Image//football_field.tga");
	textures[TEXTURE_FRONT] = LoadTGA(L"Image//front.tga");
	textures[TEXTURE_KITTEN_BRI] = LoadTGA(L"Image//kitten_bri.tga");
	textures[TEXTURE_LARGE_FORERUNNER_FLOOR_PLATE] = LoadTGA(L"Image//large_forerunner_floor_plate.tga");
	textures[TEXTURE_LEFT] = LoadTGA(L"Image//left.tga");
	textures[TEXTURE_METALPLATEFLOORFULL] = LoadTGA(L"Image//metalplatefloorfull.tga");
	textures[TEXTURE_METAL_TILE] = LoadTGA(L"Image//metal_tile.tga");
	textures[TEXTURE_PLATE_METAL] = LoadTGA(L"Image//plate_metal.tga");
	textures[TEXTURE_RIGHT] = LoadTGA(L"Image//right.tga");
	textures[TEXTURE_RING] = LoadTGA(L"Image//ring.tga");
	textures[TEXTURE_TOP] = LoadTGA(L"Image//top.tga");
}

void ScenePhysics::InnitLight()
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
	
	light[FOOTBALL_LIGHT].type = Light::LIGHT_SPOT;
	light[FOOTBALL_LIGHT].position.Set(20, 2000, 20);
	light[FOOTBALL_LIGHT].color.Set(1, 1, 1);
	light[FOOTBALL_LIGHT].power = 1;
	light[FOOTBALL_LIGHT].kC = 1.f;
	light[FOOTBALL_LIGHT].kL = 0.01f;
	light[FOOTBALL_LIGHT].kQ = 0.001f;
	light[FOOTBALL_LIGHT].cosCutoff = cos(Math::DegreeToRadian(140));
	light[FOOTBALL_LIGHT].cosInner = cos(Math::DegreeToRadian(30));
	light[FOOTBALL_LIGHT].exponent = 1.f;
	light[FOOTBALL_LIGHT].spotDirection.Set(0.f, -1.f, 0.f);
	
	gfx.AddLight(&light[WORLD_LIGHT]);
	gfx.AddLight(&light[FOOTBALL_LIGHT]);
}

void ScenePhysics::InnitGeometry()
{

	//Initialize all meshes to NULL
	meshList.resize(NUM_GEOMETRY, NULL);

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad(L"front", Color(1, 1, 1), 10000.f, 10000.f);
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad(L"back", Color(1, 1, 1), 10000.f, 10000.f);
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad(L"left", Color(1, 1, 1), 10000.f, 10000.f);
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad(L"right", Color(1, 1, 1), 10000.f, 10000.f);
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad(L"top", Color(1, 1, 1), 10000.f, 10000.f);
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad(L"bottom", Color(1, 1, 1), 10000.f, 10000.f);

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube(L"Cube",Color(),1,1,1);
	meshList[GEO_SENTINEL] = MeshBuilder::GenerateOBJ(L"OBJ//sentinel.obj");
	meshList[GEO_LIFT] = MeshBuilder::GenerateOBJ(L"OBJ//lift.obj");
	meshList[GEO_GROUND] = MeshBuilder::GenerateOBJ(L"OBJ//Nirvana.obj");
	meshList[GEO_FOOTBALL_FIELD] = MeshBuilder::GenerateOBJ(L"OBJ//football field.obj");
	
	meshList[GEO_DIDACT] = MeshBuilder::GenerateOBJ(L"OBJ//didact.obj");
	meshList[GEO_HALF_DOOR] = MeshBuilder::GenerateOBJ(L"OBJ//door.obj");
	meshList[GEO_RING] = MeshBuilder::GenerateOBJ(L"OBJ//ring.obj");
}

void ScenePhysics::InnitDraws()
{
	drawOrders.resize(NUM_DRAWS + meshList.size() - NUM_GEOMETRY);

	//skybox will be the main draw order that all other draw orders are children of
	drawOrders[DRAW_SKYBOX].geometry = NULL;
	drawOrders[DRAW_SKYBOX].enableLight = false;

	drawOrders[DRAW_SKYBOX].children.push_back(&drawOrders[DRAW_FRONT]);
	drawOrders[DRAW_SKYBOX].children.push_back(&drawOrders[DRAW_BACK]);
	drawOrders[DRAW_SKYBOX].children.push_back(&drawOrders[DRAW_LEFT]);
	drawOrders[DRAW_SKYBOX].children.push_back(&drawOrders[DRAW_RIGHT]);
	drawOrders[DRAW_SKYBOX].children.push_back(&drawOrders[DRAW_TOP]);
	drawOrders[DRAW_SKYBOX].children.push_back(&drawOrders[DRAW_BOTTOM]);
	drawOrders[DRAW_SKYBOX].children.push_back(&drawOrders[DRAW_GROUND]);
	drawOrders[DRAW_SKYBOX].children.push_back(&drawOrders[DRAW_PLAYER]);
	drawOrders[DRAW_SKYBOX].children.push_back(&drawOrders[DRAW_LEFT_LIFT]);
	drawOrders[DRAW_SKYBOX].children.push_back(&drawOrders[DRAW_THING_AT_CENTRE]);

	drawOrders[DRAW_SKYBOX].children.push_back(&drawOrders[DRAW_CORRUPTED_SENTINEL]);
	drawOrders[DRAW_SKYBOX].children.push_back(&drawOrders[DRAW_ROCK_SENTINEL]);
	drawOrders[DRAW_SKYBOX].children.push_back(&drawOrders[DRAW_STONE_SENTINEL]);
	drawOrders[DRAW_SKYBOX].children.push_back(&drawOrders[DRAW_WISE_SENTINEL]);
	drawOrders[DRAW_SKYBOX].children.push_back(&drawOrders[DRAW_SNEAKY_SENTINEL]);
	drawOrders[DRAW_SKYBOX].children.push_back(&drawOrders[DRAW_PURE_SENTINEL]);

	//positions are offset a little from their proper position because of floating point error
	drawOrders[DRAW_FRONT].geometry = meshList[GEO_FRONT];
	drawOrders[DRAW_FRONT].transform.translate.Set(-4996,0,0);
	drawOrders[DRAW_FRONT].transform.rotate.z = 270;
	drawOrders[DRAW_FRONT].enableLight = false;
	drawOrders[DRAW_FRONT].material.SetTextureTo(textures[TEXTURE_FRONT]);

	drawOrders[DRAW_BACK].geometry = meshList[GEO_BACK];
	drawOrders[DRAW_BACK].transform.translate.Set(4998,0,0);
	drawOrders[DRAW_BACK].transform.rotate.z = 90;
	drawOrders[DRAW_BACK].transform.rotate.x = 180;
	drawOrders[DRAW_BACK].enableLight = false;
	drawOrders[DRAW_BACK].material.SetTextureTo(textures[TEXTURE_BACK]);

	drawOrders[DRAW_LEFT].geometry = meshList[GEO_LEFT];
	drawOrders[DRAW_LEFT].transform.translate.Set(0,0,4998);
	drawOrders[DRAW_LEFT].transform.rotate.x = 270;
	drawOrders[DRAW_LEFT].transform.rotate.y = 90;
	drawOrders[DRAW_LEFT].enableLight = false;
	drawOrders[DRAW_LEFT].material.SetTextureTo(textures[TEXTURE_LEFT]);

	drawOrders[DRAW_RIGHT].geometry = meshList[GEO_RIGHT];
	drawOrders[DRAW_RIGHT].transform.translate.Set(0,0,-4998);
	drawOrders[DRAW_RIGHT].transform.rotate.x = 90;
	drawOrders[DRAW_RIGHT].transform.rotate.y = 270;
	drawOrders[DRAW_RIGHT].enableLight = false;
	drawOrders[DRAW_RIGHT].material.SetTextureTo(textures[TEXTURE_RIGHT]);

	drawOrders[DRAW_TOP].geometry = meshList[GEO_TOP];
	drawOrders[DRAW_TOP].transform.translate.Set(0,4998,0);
	drawOrders[DRAW_TOP].transform.rotate.z = 180;
	drawOrders[DRAW_TOP].transform.rotate.y = 0;
	drawOrders[DRAW_TOP].enableLight = false;
	drawOrders[DRAW_TOP].material.SetTextureTo(textures[TEXTURE_TOP]);

	drawOrders[DRAW_BOTTOM].geometry = meshList[GEO_BOTTOM];
	drawOrders[DRAW_BOTTOM].transform.translate.Set(0,-4998,0);
	drawOrders[DRAW_BOTTOM].transform.rotate.y = 270;
	drawOrders[DRAW_BOTTOM].enableLight = false;
	drawOrders[DRAW_BOTTOM].material.SetTextureTo(textures[TEXTURE_BOTTOM]);

	drawOrders[DRAW_PLAYER].geometry = meshList[GEO_SENTINEL];
	drawOrders[DRAW_PLAYER].transform.translate.Set(21.7, 5, 68.3);
	drawOrders[DRAW_PLAYER].enableLight = false;
	drawOrders[DRAW_PLAYER].SetTerminalVelocityTo(Vector3(60,60,60));
	drawOrders[DRAW_PLAYER].mass = 75;
	drawOrders[DRAW_PLAYER].bounce = 0.5;
	drawOrders[DRAW_PLAYER].material.SetTextureTo(textures[TEXTURE_LARGE_FORERUNNER_FLOOR_PLATE]);

	drawOrders[DRAW_LEFT_LIFT].geometry = meshList[GEO_LIFT];
	drawOrders[DRAW_LEFT_LIFT].transform.translate.Set(0, 100, 0);
	drawOrders[DRAW_LEFT_LIFT].enableLight = true;
	drawOrders[DRAW_LEFT_LIFT].SetTerminalVelocityTo(Vector3(60,60,60));
	drawOrders[DRAW_LEFT_LIFT].mass = 100;
	drawOrders[DRAW_LEFT_LIFT].material.SetTextureTo(textures[TEXTURE_METALPLATEFLOORFULL]);

	drawOrders[DRAW_GROUND].geometry = meshList[GEO_GROUND];
	drawOrders[DRAW_GROUND].material.SetTextureTo(textures[TEXTURE_METALPLATEFLOORFULL]);

	drawOrders[DRAW_FOOTBALL_FIELD].geometry = meshList[GEO_FOOTBALL_FIELD];
	drawOrders[DRAW_FOOTBALL_FIELD].transform.translate.Set(0,0,0);
	drawOrders[DRAW_FOOTBALL_FIELD].enableLight = false;
	drawOrders[DRAW_FOOTBALL_FIELD].SetTerminalVelocityTo(Vector3(60,60,60));
	drawOrders[DRAW_FOOTBALL_FIELD].material.SetTextureTo(textures[TEXTURE_FOOTBALL_FIELD]);

	drawOrders[DRAW_THING_AT_CENTRE].geometry = meshList[GEO_RING];
	drawOrders[DRAW_THING_AT_CENTRE].transform.translate.Set(-1000,0,0);
	drawOrders[DRAW_THING_AT_CENTRE].enableLight = false;
	drawOrders[DRAW_THING_AT_CENTRE].SetTerminalVelocityTo(Vector3(60,60,60));
	drawOrders[DRAW_THING_AT_CENTRE].material.SetTextureTo(textures[TEXTURE_RING]);

	drawOrders[DRAW_CORRUPTED_SENTINEL].geometry = meshList[GEO_SENTINEL];
	drawOrders[DRAW_CORRUPTED_SENTINEL].material.SetTextureTo(textures[TEXTURE_ELECTRONIC_CIRCUIT]);
	drawOrders[DRAW_CORRUPTED_SENTINEL].transform.translate.Set(-23.3,3.7,69.9);
	drawOrders[DRAW_CORRUPTED_SENTINEL].enableLight = false;

	drawOrders[DRAW_ROCK_SENTINEL].geometry = meshList[GEO_SENTINEL];
	drawOrders[DRAW_ROCK_SENTINEL].material.SetTextureTo(textures[TEXTURE_DOOR]);
	drawOrders[DRAW_ROCK_SENTINEL].transform.translate.Set(-1000,0,0);
	drawOrders[DRAW_ROCK_SENTINEL].enableLight = false;

	drawOrders[DRAW_STONE_SENTINEL].geometry = meshList[GEO_SENTINEL];
	drawOrders[DRAW_STONE_SENTINEL].material.SetTextureTo(textures[TEXTURE_RING]);
	drawOrders[DRAW_STONE_SENTINEL].transform.translate.Set(-1000,0,0);
	drawOrders[DRAW_STONE_SENTINEL].enableLight = false;

	drawOrders[DRAW_WISE_SENTINEL].geometry = meshList[GEO_SENTINEL];
	drawOrders[DRAW_WISE_SENTINEL].material.SetTextureTo(textures[TEXTURE_PLATE_METAL]);
	drawOrders[DRAW_WISE_SENTINEL].transform.translate.Set(-1000,0,0);
	drawOrders[DRAW_WISE_SENTINEL].enableLight = false;

	drawOrders[DRAW_SNEAKY_SENTINEL].geometry = meshList[GEO_SENTINEL];
	drawOrders[DRAW_SNEAKY_SENTINEL].material.SetTextureTo(textures[TEXTURE_METALPLATEFLOORFULL]);
	drawOrders[DRAW_SNEAKY_SENTINEL].transform.translate.Set(-1000,0,0);
	drawOrders[DRAW_SNEAKY_SENTINEL].enableLight = false;

	drawOrders[DRAW_PURE_SENTINEL].geometry = meshList[GEO_SENTINEL];
	drawOrders[DRAW_PURE_SENTINEL].material.SetTextureTo(textures[TEXTURE_METAL_TILE]);
	drawOrders[DRAW_PURE_SENTINEL].transform.translate.Set(-23.2, 4.25, -69.8);
	drawOrders[DRAW_PURE_SENTINEL].enableLight = false;
}

void ScenePhysics::InnitVoxels()
{
	drawOrders[DRAW_PLAYER].AddVoxel(4,5,4, drawOrders[DRAW_PLAYER].transform.translate, Color());
	drawOrders[DRAW_LEFT_LIFT].AddVoxel(10,10,10, drawOrders[DRAW_LEFT_LIFT].transform.translate, Color());

	//voxel for football field
	drawOrders[DRAW_GROUND].AddVoxel(362.9, 2, 589.3, drawOrders[DRAW_GROUND].transform.translate + Vector3(-250.54, -662.6, 0), Color());
	drawOrders[DRAW_GROUND].AddVoxel(3.3, 112.7, 589.3, drawOrders[DRAW_GROUND].transform.translate + Vector3(-433.7, -622.4, 0), Color());
	drawOrders[DRAW_GROUND].AddVoxel(362.9, 109.7, 7.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(-251.1, -615.5, -291.2), Color());
	drawOrders[DRAW_GROUND].AddVoxel(362.9, 109.7, 7.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(-251.1, -615.5, 291.2), Color());
	drawOrders[DRAW_GROUND].AddVoxel(3.1, 92.1, 589.3, drawOrders[DRAW_GROUND].transform.translate + Vector3(-67.9, -606.6, 0), Color());
	drawOrders[DRAW_GROUND].AddVoxel(3.1, 112.7, 214.8, drawOrders[DRAW_GROUND].transform.translate + Vector3(-67.9, -622.4, -180.2), Color());
	drawOrders[DRAW_GROUND].AddVoxel(3.1, 112.7, 133.5, drawOrders[DRAW_GROUND].transform.translate + Vector3(-67.9, -622.4, 0), Color());
	drawOrders[DRAW_GROUND].AddVoxel(3.1, 112.7, 214.8, drawOrders[DRAW_GROUND].transform.translate + Vector3(-67.9, -622.4, 180.2), Color());
	drawOrders[DRAW_GROUND].AddVoxel(362.9, 1, 589.3, drawOrders[DRAW_GROUND].transform.translate + Vector3(-250.54, -565.6, 0), Color());

	//tunnel to football field
	drawOrders[DRAW_GROUND].AddVoxel(72.2, 11.9, 0.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(-31.0, -656.9, 66.7), Color());
	drawOrders[DRAW_GROUND].AddVoxel(72.2, 11.9, 0.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(-31.0, -656.9, 72.9), Color());
	drawOrders[DRAW_GROUND].AddVoxel(79.2, 1.1, 6.3, drawOrders[DRAW_GROUND].transform.translate + Vector3(-31.0, -662.3, 69.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(71.0, 1.9, 6.3, drawOrders[DRAW_GROUND].transform.translate + Vector3(-31.0, -650.9, 69.8), Color());

	drawOrders[DRAW_GROUND].AddVoxel(72.2, 11.9, 0.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(-31.0, -656.9, -66.7), Color());
	drawOrders[DRAW_GROUND].AddVoxel(72.2, 11.9, 0.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(-31.0, -656.9, -72.9), Color());
	drawOrders[DRAW_GROUND].AddVoxel(79.2, 1.1, 6.3, drawOrders[DRAW_GROUND].transform.translate + Vector3(-31.0, -662.3, -69.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(71.0, 1.9, 6.3, drawOrders[DRAW_GROUND].transform.translate + Vector3(-31.0, -650.9, -69.8), Color());

	//elevator shaft
	drawOrders[DRAW_GROUND].AddVoxel(7.0, 665.4, 0.3, drawOrders[DRAW_GROUND].transform.translate + Vector3(7.5, -331.2, -66.5), Color());
	drawOrders[DRAW_GROUND].AddVoxel(7.0, 665.4, 0.3, drawOrders[DRAW_GROUND].transform.translate + Vector3(7.5, -331.2, -73.1), Color());
	drawOrders[DRAW_GROUND].AddVoxel(0.3, 665.4, 7.0, drawOrders[DRAW_GROUND].transform.translate + Vector3(10.7, -331.2, -69.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(0.3, 653.4, 7.0, drawOrders[DRAW_GROUND].transform.translate + Vector3(4.4, -325.2, -69.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(6.3, 1.2, 7.0, drawOrders[DRAW_GROUND].transform.translate + Vector3(7.3, -662.3, -69.8), Color());
	
	drawOrders[DRAW_GROUND].AddVoxel(7.0, 665.4, 0.3, drawOrders[DRAW_GROUND].transform.translate + Vector3(7.5, -331.2, 66.5), Color());
	drawOrders[DRAW_GROUND].AddVoxel(7.0, 665.4, 0.3, drawOrders[DRAW_GROUND].transform.translate + Vector3(7.5, -331.2, 73.1), Color());
	drawOrders[DRAW_GROUND].AddVoxel(0.3, 665.4, 7.0, drawOrders[DRAW_GROUND].transform.translate + Vector3(10.7, -331.2, 69.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(0.3, 653.4, 7.0, drawOrders[DRAW_GROUND].transform.translate + Vector3(4.4, -325.2, 69.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(6.3, 1.2, 7.0, drawOrders[DRAW_GROUND].transform.translate + Vector3(7.3, -662.3, 69.8), Color());

	///walls that surround the tunnels

	drawOrders[DRAW_GROUND].AddVoxel(1, 619.7, 52, drawOrders[DRAW_GROUND].transform.translate + Vector3(-19.0, -340.9, 69.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(1, 619.7, 52, drawOrders[DRAW_GROUND].transform.translate + Vector3(33.8, -340.9, 69.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(52, 619.7, 1, drawOrders[DRAW_GROUND].transform.translate + Vector3(4.3, -340.9, 43.4), Color());
	drawOrders[DRAW_GROUND].AddVoxel(52, 619.7, 1, drawOrders[DRAW_GROUND].transform.translate + Vector3(4.3, -340.9, 96.2), Color());

	drawOrders[DRAW_GROUND].AddVoxel(1, 619.7, 52, drawOrders[DRAW_GROUND].transform.translate + Vector3(-19.0, -340.9, -69.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(1, 619.7, 52, drawOrders[DRAW_GROUND].transform.translate + Vector3(33.8, -340.9, -69.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(52, 619.7, 1, drawOrders[DRAW_GROUND].transform.translate + Vector3(4.3, -340.9, -43.4), Color());
	drawOrders[DRAW_GROUND].AddVoxel(52, 619.7, 1, drawOrders[DRAW_GROUND].transform.translate + Vector3(4.3, -340.9, -96.2), Color());

	//outside platform

	drawOrders[DRAW_GROUND].AddVoxel(40.1, 1, 133.0, drawOrders[DRAW_GROUND].transform.translate + Vector3(54.5, -30.4, 69.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(40.1, 1, 133.0, drawOrders[DRAW_GROUND].transform.translate + Vector3(-39.5, -30.4, 69.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(133.0, 1, 40.1, drawOrders[DRAW_GROUND].transform.translate + Vector3(7.3, -30.4, 118.0), Color());
	drawOrders[DRAW_GROUND].AddVoxel(133.0, 1, 40.1, drawOrders[DRAW_GROUND].transform.translate + Vector3(7.3, -30.4, 21.3), Color());
	
	drawOrders[DRAW_GROUND].AddVoxel(40.1, 1, 133.0, drawOrders[DRAW_GROUND].transform.translate + Vector3(54.5, -30.4, -69.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(40.1, 1, 133.0, drawOrders[DRAW_GROUND].transform.translate + Vector3(-39.5, -30.4, -69.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(133.0, 1, 40.1, drawOrders[DRAW_GROUND].transform.translate + Vector3(7.3, -30.4, -118.0), Color());
	drawOrders[DRAW_GROUND].AddVoxel(133.0, 1, 40.1, drawOrders[DRAW_GROUND].transform.translate + Vector3(7.3, -30.4, -21.3), Color());

	//base main floor
	drawOrders[DRAW_GROUND].AddVoxel(57.2, 1, 24.6, drawOrders[DRAW_GROUND].transform.translate + Vector3(5.3, -0.5, 85.3), Color());
	drawOrders[DRAW_GROUND].AddVoxel(57.2, 1, 24.6, drawOrders[DRAW_GROUND].transform.translate + Vector3(5.3, -0.5, 53.7), Color());
	drawOrders[DRAW_GROUND].AddVoxel(24.6, 1, 57.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(21.6, -0.5, 69.0), Color());
	drawOrders[DRAW_GROUND].AddVoxel(24.6, 1, 57.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(-11, -0.5, 69.0), Color());
	
	drawOrders[DRAW_GROUND].AddVoxel(57.2, 1, 24.6, drawOrders[DRAW_GROUND].transform.translate + Vector3(5.3, -0.5, -85.3), Color());
	drawOrders[DRAW_GROUND].AddVoxel(57.2, 1, 24.6, drawOrders[DRAW_GROUND].transform.translate + Vector3(5.3, -0.5, -53.7), Color());
	drawOrders[DRAW_GROUND].AddVoxel(24.6, 1, 57.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(21.6, -0.5, -69.0), Color());
	drawOrders[DRAW_GROUND].AddVoxel(24.6, 1, 57.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(-11, -0.5, -69.0), Color());

	//walls of main bases
	drawOrders[DRAW_GROUND].AddVoxel(46.4, 99.5, 5.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(7.4, 36.3, 96.7), Color());
	drawOrders[DRAW_GROUND].AddVoxel(19.4, 99.5, 5.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(21, 36.3, 42.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(19.4, 99.5, 5.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(-6.2, 36.3, 42.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(46.4, 62.0, 5.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(7.4, 40.3, 42.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(5.2, 99.5, 46.4, drawOrders[DRAW_GROUND].transform.translate + Vector3(34.3, 36.3, 69.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(5.2, 99.5, 46.4, drawOrders[DRAW_GROUND].transform.translate + Vector3(-19.6, 36.3, 69.8), Color());

	drawOrders[DRAW_GROUND].AddVoxel(46.4, 99.5, 5.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(7.4, 36.3, -96.7), Color());
	drawOrders[DRAW_GROUND].AddVoxel(19.4, 99.5, 5.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(21, 36.3, -42.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(19.4, 99.5, 5.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(-6.2, 36.3, -42.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(46.4, 62.0, 5.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(7.4, 40.3, -42.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(5.2, 99.5, 46.4, drawOrders[DRAW_GROUND].transform.translate + Vector3(34.3, 36.3, -69.8), Color());
	drawOrders[DRAW_GROUND].AddVoxel(5.2, 99.5, 46.4, drawOrders[DRAW_GROUND].transform.translate + Vector3(-19.6, 36.3, -69.8), Color());

	//platform connecting the 2 main bases
	drawOrders[DRAW_GROUND].AddVoxel(10.8, 1, 86.3, drawOrders[DRAW_GROUND].transform.translate + Vector3(7.5, -0.5, 0), Color());
	drawOrders[DRAW_GROUND].AddVoxel(1.9, 1000, 86.3, drawOrders[DRAW_GROUND].transform.translate + Vector3(11.9, 0, 0), Color());
	drawOrders[DRAW_GROUND].AddVoxel(1.9, 1000, 38.5, drawOrders[DRAW_GROUND].transform.translate + Vector3(3.0, 0, 23.9), Color());
	drawOrders[DRAW_GROUND].AddVoxel(1.9, 1000, 38.5, drawOrders[DRAW_GROUND].transform.translate + Vector3(3.0, 0, -23.9), Color());
	drawOrders[DRAW_GROUND].AddVoxel(14.8, 1, 7.2, drawOrders[DRAW_GROUND].transform.translate + Vector3(-5.0, -0.5, 0), Color());
	drawOrders[DRAW_GROUND].AddVoxel(18.8, 1000, 1.03, drawOrders[DRAW_GROUND].transform.translate + Vector3(-6.0, 0, 4), Color());
	drawOrders[DRAW_GROUND].AddVoxel(18.8, 1000, 1.03, drawOrders[DRAW_GROUND].transform.translate + Vector3(-6.0, 0, -4), Color());
	drawOrders[DRAW_GROUND].AddVoxel(1, 1000, 10.1, drawOrders[DRAW_GROUND].transform.translate + Vector3(-13.5, 0, 0), Color());

	//invisible wall that blocks the player from flying out of the map
	drawOrders[DRAW_GROUND].AddVoxel(1000, 1, 1000, drawOrders[DRAW_GROUND].transform.translate + Vector3(0, 60, 0), Color());

	//platforms going towards didact
}

void ScenePhysics::InnitForces()
{
	//Vector3 accelerationDueToGravity(0, -.8f, 0);
	Vector3 accelerationDueToGravity(0, -9.8f, 0);
	//Vector3 accelerationDueToGravity(0, 0, 0);
	for(std::vector<drawOrder>::iterator draw = drawOrders.begin(); draw != drawOrders.end(); draw++)
	{
		draw->AddForce(accelerationDueToGravity * draw->mass);
	}
}

bool ScenePhysics::Update(const double dt)
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

	if(didactIsSummoned)
	{
		drawOrders[DRAW_THING_AT_CENTRE].geometry = meshList[GEO_DIDACT];
		drawOrders[DRAW_THING_AT_CENTRE].transform.rotate.y = 0;
	}
	else
	{
		drawOrders[DRAW_THING_AT_CENTRE].transform.rotate.y += rotationspeed * deltaTime;
	}
	DoUserInput();
	UpdateDraws();
	UpdateView();
	UpdateLight();
	return false;
}

void ScenePhysics::UpdateLogic()
{
}

void ScenePhysics::UpdateDidact()
{
}

void ScenePhysics::UpdateRing()
{
}

void ScenePhysics::UpdateView()
{
	//positions are offset a little from their proper position because of floating point error
	drawOrders[DRAW_FRONT].transform.translate = Vector3(-5000,0,0) + camera.ReturnPosition();
	drawOrders[DRAW_BACK].transform.translate = Vector3(5000,0,0) + camera.ReturnPosition();
	drawOrders[DRAW_LEFT].transform.translate = Vector3(0,0,5000) + camera.ReturnPosition();
	drawOrders[DRAW_RIGHT].transform.translate = Vector3(0,0,-5000) + camera.ReturnPosition();
	drawOrders[DRAW_TOP].transform.translate = Vector3(0,4999,0) + camera.ReturnPosition();
	drawOrders[DRAW_BOTTOM].transform.translate = Vector3(0,-5000,0) + camera.ReturnPosition();

	camera.Translate(drawOrders[DRAW_PLAYER].transform.translate - camera.ReturnPosition() + Vector3(0, 4, 0));
	float player_rotationY = camera.GetRotation().y - drawOrders[DRAW_PLAYER].transform.rotate.y;
	float player_current_frame_rotationY = player_rotationY / 25;
	drawOrders[DRAW_PLAYER].transform.rotate.y += player_current_frame_rotationY;
	gfx.SetViewAt(camera);
}

void ScenePhysics::UpdateLight()
{
	gfx.UpdateLights();

}

void ScenePhysics::UpdateDraws()
{
	//where forces are applied
	for(std::vector<drawOrder>::iterator draw = drawOrders.begin(); draw != drawOrders.end(); draw++)
	{
		//an object has 0 mass if it is infinitely heavy and forces will barely have any effect on it including gravity. This is totally how physics work
		if(&(*draw) == &drawOrders[DRAW_PLAYER])
		{
			draw->velocity.x  = playerAcceleration.x * deltaTime;
			draw->velocity.y  += playerAcceleration.y * deltaTime;
			draw->velocity.z  = playerAcceleration.z * deltaTime;
		}
		draw->UpdateVelocity(deltaTime);
	}

	//where we do collision
	for(std::vector<drawOrder>::iterator draw1 = drawOrders.begin(); draw1 != drawOrders.end(); draw1++)
	{
		//check the object with every other object after it. Objects that came before are skipped to prevent checking collision twice with the same object
		for(std::vector<drawOrder>::iterator draw2 = draw1 + 1; draw2 != drawOrders.end(); draw2++)
		{
			if(draw1->velocity.IsZero() && draw2->velocity.IsZero())
			{
				continue;
			}
			bool CollisionIsDone = false;

			//check the individual voxel each object has. If one pair collides, collision is applied to the objects as a whole we break out of the loop
			for(std::vector<Voxel>::iterator voxel1 = draw1->voxels.begin(); voxel1 != draw1->voxels.end(); voxel1++)
			{
				for(std::vector<Voxel>::iterator voxel2 = draw2->voxels.begin(); voxel2 != draw2->voxels.end(); voxel2++)
				{
					CollisionIsDone = collisionSystem.CheckThisCollision(&*voxel1, &*voxel2, deltaTime);
				}
			}
		}
	}
	collisionSystem.ResolveAllCollisionsAccordingTo(deltaTime);

	//draws are finally updated after processing
	for(std::vector<drawOrder>::iterator draw = drawOrders.begin(); draw != drawOrders.end(); draw++)
	{
		draw->UpdateTo(deltaTime);
	}
}

void ScenePhysics::Render()
{
	//clear depth and color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnableVertexAttribArray(0); // 1st attribute buffer :vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer : colors
	glEnableVertexAttribArray(2); // 3rd attribute : normals
	glEnableVertexAttribArray(3); // 4th attribute : UV coordinates

	if(drawVoxels)
	{
		for(std::vector<drawOrder>::iterator draw = drawOrders.begin(); draw != drawOrders.end(); draw++)
		{
			Material material;
			drawOrder draw_cube;
			draw_cube.geometry = meshList[GEO_CUBE];
			draw_cube.enableLight = false;
			draw_cube.material = material;
			//check the individual voxel each object has. If one pair collides, collision is applied to the objects as a whole we break out of the loop
			for(std::vector<Voxel>::iterator voxel = draw->voxels.begin(); voxel != draw->voxels.end(); voxel++)
			{
				modelStack.PushMatrix();
				Mtx44 translate, scale;
				translate.SetToTranslation(voxel->GetPosition());
				scale.SetToScale(voxel->GetSize().x, voxel->GetSize().y, voxel->GetSize().z);
				modelStack.LoadMatrix(translate * scale);
				gfx.RenderMesh(draw_cube, modelStack.Top());
				modelStack.PopMatrix();
			}
		}
	}
	else
	{
		ExecuteDrawOrder(drawOrders[DRAW_SKYBOX]);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

void ScenePhysics::Exit()
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

void ScenePhysics::DoUserInput()
{
	double mouseX;
	double mouseY;
	mouse.Update(mouseX, mouseY);
	const int CAMERA_SPEED = 5;
	camera.Rotate(0, -mouseX, -mouseY);
	playerAcceleration.SetZero();

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
	if (keyboard.isKeyHold(VK_UP))
	{
		Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
		Vector3 tempVector;
		tempVector.Set(600, 0, 0);
		tempVector = rotationMatrix * tempVector;
		playerAcceleration += tempVector;
	}
	if (keyboard.isKeyHold(VK_DOWN))
	{
		Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
		Vector3 tempVector;
		tempVector.Set(-600, 0, 0);
		tempVector = rotationMatrix * tempVector;
		playerAcceleration += tempVector;
	}
	if (keyboard.isKeyHold(VK_LEFT))
	{
		Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
		Vector3 tempVector;
		tempVector.Set(0, 0, -600);
		tempVector = rotationMatrix * tempVector;
		playerAcceleration += tempVector;
	}
	if (keyboard.isKeyHold(VK_RIGHT))
	{
		Mtx44 rotationMatrix = camera.GetRotationMatrix(false, true, false);
		Vector3 tempVector;tempVector.Set(0, 0, 600);
		tempVector = rotationMatrix * tempVector;
		playerAcceleration += tempVector;
	}
	if (keyboard.isKeyHold('O'))
	{	
		Vector3 tempVector;
		tempVector.Set(0, 50, 0);
		playerAcceleration += tempVector;
		playerAcceleration += tempVector;
	}
	if (keyboard.isKeyHold('P'))
	{
		Vector3 tempVector;
		tempVector.Set(0, -50, 0);
		playerAcceleration += tempVector;
	}
	if (keyboard.isKeyHold('W'))
	{
		camera.Move(-10.0f * deltaTime * CAMERA_SPEED, 0.0f, 0.0f);
	}
	if (keyboard.isKeyHold('A'))
	{
		camera.Move(0.0f, 0.0f, 10.0f * deltaTime * CAMERA_SPEED);
	}
	if (keyboard.isKeyHold('S'))
	{
		camera.Move(10.0f * deltaTime * CAMERA_SPEED, 0.0f, 0.0f);
	}
	if (keyboard.isKeyHold('D'))
	{
		camera.Move(0.0f, 0.0f, -10.0f * deltaTime * CAMERA_SPEED);
	}
	if (keyboard.isKeyHold(VK_SPACE))
	{
		camera.Move(0,10 * deltaTime * CAMERA_SPEED,0);
	}
	if (keyboard.isKeyHold(VK_CONTROL))
	{
		camera.Move(0,-10 * deltaTime * CAMERA_SPEED,0);
	}
}

void ScenePhysics::ExecuteDrawOrder(drawOrder& draw)
{
	modelStack.PushMatrix();
	modelStack.MultMatrix(draw.transform.Matrix());
	for(std::vector<drawOrder*>::iterator child = draw.children.begin(); child != draw.children.end(); child++)
	{
		ExecuteDrawOrder(**child);
	}
	modelStack.MultMatrix(draw.selfTransform.Matrix());
	//a small check to see weather the draw order is pointing to a geometry before drawing it.
	if(draw.geometry)
	{
		gfx.RenderMesh(draw, modelStack.Top());
	}
	modelStack.PopMatrix();
}