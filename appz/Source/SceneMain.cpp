#include "SceneMain.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "PlayerHuman.h"
#include "PlayerFrog.h"
#include "Polygon.h"

SceneMain::SceneMain(Keyboard& keyboard, GLMouse& mouse, Sound& snd, Graphics& gfx)
	:
Scene(keyboard, mouse, snd, gfx)
{
}

SceneMain::~SceneMain(void)
{
}

void SceneMain::Init()
{
	InnitLight();
	InnitTextures();
	InnitMaterials();
	InnitSounds();
	InnitGeometry();
	InnitDraws();
	InnitVoxels();
	InnitForces();
	InnitLogic();
	player = new PlayerHuman;
	isJumping = false;
	isFalling = false;
	jumpedHeight = 0;
	isFrog = false;
	UpdateLv2 = true;
	SWLv2[0].DrawIsEqualTo(globals.GetDraw(L"shopper_wanderer_body0"), globals.GetDraw(L"shopper_wanderer_arm_left0"), globals.GetDraw(L"shopper_wanderer_arm_right0"), globals.GetDraw(L"shopper_wanderer_leg_left0"), globals.GetDraw(L"shopper_wanderer_leg_right0"));
	SWLv2[0].SetPosition(9);
	SWLv2[1].DrawIsEqualTo(globals.GetDraw(L"shopper_wanderer_body1"), globals.GetDraw(L"shopper_wanderer_arm_left1"), globals.GetDraw(L"shopper_wanderer_arm_right1"), globals.GetDraw(L"shopper_wanderer_leg_left1"), globals.GetDraw(L"shopper_wanderer_leg_right1"));
	SWLv2[1].SetPosition(0);

	camera.Init(Vector3(0, 7, 5), Vector3(1, 0, 0), Vector3(0, 1, 0));
	gfx.SetProjectionTo(45.f, 4.f / 3.f, 0.1f, 90000.f);
	gfx.InitText(L"Image//kitten_bri.tga");
}

void SceneMain::InnitSounds()
{
	//snd.loadWave("pure", "sound//pure.wav");
}

void SceneMain::InnitLogic()
{
	frameCounter = 0;
	accumulatingDT = 0;
	currentFPS = 60;
	drawVoxels = false;
}

void SceneMain::InnitTextures()
{
	globals.AddTexture(L"skybox", L"Image//skybox.tga");
	globals.AddTexture(L"ground", L"Image//ground.tga");
	globals.AddTexture(L"building", L"Image//large_forerunner_floor_plate.tga");
	globals.AddTexture(L"cashiertable texture", L"Image//cashiertable_texture.tga");
	globals.AddTexture(L"CabinetTexture", L"Image//CabinetTexture.tga");
	globals.AddTexture(L"can1", L"Image//can1.tga");
	globals.AddTexture(L"can2", L"Image//can2.tga");
	globals.AddTexture(L"can3", L"Image//can3.tga");
	globals.AddTexture(L"cereal1", L"Image//cereal1.tga");
	globals.AddTexture(L"cereal2", L"Image//cereal2.tga");
	globals.AddTexture(L"cereal3", L"Image//cereal3.tga");
	globals.AddTexture(L"packet1", L"Image//packet1.tga");
	globals.AddTexture(L"packet2", L"Image//packet2.tga");
	globals.AddTexture(L"packet3", L"Image//packet3.tga");
	globals.AddTexture(L"dullwhite", L"Image//dullwhite.tga");
	globals.AddTexture(L"lift", L"Image//blue.tga");
	globals.AddTexture(L"liftdoor", L"Image//liftdoor.tga");
	globals.AddTexture(L"door texture", L"Image//door_texture.tga");
	globals.AddTexture(L"travelatorslope texture2", L"Image//travelatorslope_texture2.tga");
	globals.AddTexture(L"travelatorhandle texture", L"Image//travelatorhandle_texture.tga");
	globals.AddTexture(L"trolleytexture", L"Image//TrolleyTexture.tga");
	globals.AddTexture(L"character1", L"Image//character1.tga");
	globals.AddTexture(L"robot", L"Image//robot_texture.tga");
}

void SceneMain::InnitMaterials()
{
	globals.AddMaterial(Material(L"skybox",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"skybox")));
	globals.AddMaterial(Material(L"ground",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"ground")));
	globals.AddMaterial(Material(L"building",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"building")));
	globals.AddMaterial(Material(L"cashiertable",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"cashiertable texture")));
	globals.AddMaterial(Material(L"cabinet",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"CabinetTexture")));
	globals.AddMaterial(Material(L"can1",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"can1")));
	globals.AddMaterial(Material(L"can2",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"can2")));
	globals.AddMaterial(Material(L"can3",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"can3")));
	globals.AddMaterial(Material(L"cereal1",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"cereal1")));
	globals.AddMaterial(Material(L"cereal2",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"cereal2")));
	globals.AddMaterial(Material(L"cereal3",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"cereal3")));
	globals.AddMaterial(Material(L"packet1",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"packet1")));
	globals.AddMaterial(Material(L"packet2",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"packet2")));
	globals.AddMaterial(Material(L"packet3",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"packet3")));
	globals.AddMaterial(Material(L"dullwhite",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"dullwhite")));
	globals.AddMaterial(Material(L"lift",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"lift")));
	globals.AddMaterial(Material(L"liftdoor",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"liftdoor")));
	globals.AddMaterial(Material(L"door texture",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"door texture")));
	globals.AddMaterial(Material(L"travelatorhandle",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"travelatorhandle texture")));
	globals.AddMaterial(Material(L"travelatorslope",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"travelatorslope texture2")));
	globals.AddMaterial(Material(L"trolley",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"trolleytexture")));
	globals.AddMaterial(Material(L"character1",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"character1")));
	globals.AddMaterial(Material(L"robot",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"robot")));
}

void SceneMain::InnitLight()
{
	light[1].type = Light::LIGHT_POINT;
	light[1].position.Set(20, 20, 20);
	light[1].color.Set(1, 1, 1);
	light[1].power = 0.23;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(180));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 1.f;
	light[1].spotDirection.Set(0.f, 1.f, 1.f);

	gfx.AddLight(&light[1]);
}

void SceneMain::InnitGeometry()
{
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"skybox", L"OBJ//skybox.obj"));
	globals.AddMesh(MeshBuilder::GenerateRepeatQuad(L"ground", Color(1, 1, 1), 500.f, 500.f));
	globals.AddMesh(MeshBuilder::GenerateCube(L"cube",Color(),1,1,1));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cashiertable", L"OBJ//cashiertable.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cabinet1", L"OBJ//Cabinet1.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cabinet2", L"OBJ//Cabinet2.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cabinet3", L"OBJ//Cabinet3.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cabinet4", L"OBJ//Cabinet4.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"can1", L"OBJ//can1.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"can2", L"OBJ//can2.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"can3", L"OBJ//can3.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cereal1", L"OBJ//cereal1.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cereal2", L"OBJ//cereal2.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cereal3", L"OBJ//cereal3.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"packet1", L"OBJ//packet1.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"packet2", L"OBJ//packet2.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"packet3", L"OBJ//packet3.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"building", L"OBJ//building.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"lift", L"OBJ//bluelift.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"liftdoor", L"OBJ//liftdoor.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"outerdoor", L"OBJ//outerdoor.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"innerdoor", L"OBJ//innerdoor.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"travelatorsupport", L"OBJ//travelatorsupport.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"travelatorslope", L"OBJ//travelatorslope.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"travelatorhandle", L"OBJ//travelatorhandle.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"trolley", L"OBJ//trolley.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"characterarm", L"OBJ//characterarm.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"characterleg", L"OBJ//characterleg.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"characterbody", L"OBJ//characterbody.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"robotbody", L"OBJ//robotbody.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"robotarm", L"OBJ//robotarm.obj"));
}

void SceneMain::InnitDraws()
{
	//main will be the main draw order that all other draw orders are children of
	globals.AddDraw(drawOrder(L"main"));

	//Draw SkyBox
	globals.AddDraw(drawOrder(L"skybox",globals.GetMesh(L"skybox"), &globals.GetMaterial(L"skybox"), &globals.GetDraw(L"main")));
	globals.GetDraw(L"skybox").transform.translate.Set(0,0,0);
	globals.GetDraw(L"skybox").transform.scale.Set(10000,10000,10000);

	//Draw Ground
	globals.AddDraw(drawOrder(L"ground",globals.GetMesh(L"ground"), &globals.GetMaterial(L"ground"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"ground").transform.translate.Set(0,0,-40);

	//Draw Building
	globals.AddDraw(drawOrder(L"building",globals.GetMesh(L"building"), &globals.GetMaterial(L"building"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"building").transform.translate.Set(0,0.1,-30);

	//Draw Character
	globals.AddDraw(drawOrder(L"character body",globals.GetMesh(L"characterbody"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"main"), true));
	//globals.GetDraw(L"character body").transform.translate.Set(0,3.8,0);

	globals.AddDraw(drawOrder(L"character arm left",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"character body"), true));
	//globals.GetDraw(L"character arm left").transform.translate.Set(1.25,0.6,0);
	//globals.GetDraw(L"character arm left").selfTransform.rotate.x = -5;

	globals.AddDraw(drawOrder(L"character arm right",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"character body"), true));
	//globals.GetDraw(L"character arm right").transform.translate.Set(-1.25,0.6,0);
	//globals.GetDraw(L"character arm right").selfTransform.rotate.x = -5;

	globals.AddDraw(drawOrder(L"character leg left",globals.GetMesh(L"characterleg"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"character body"), true));
	//globals.GetDraw(L"character leg left").transform.translate.Set(0.5,-1.5,0);
	//globals.GetDraw(L"character leg left").selfTransform.rotate.x = -2.5;

	globals.AddDraw(drawOrder(L"character leg right",globals.GetMesh(L"characterleg"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"character body"), true));
	//globals.GetDraw(L"character leg right").transform.translate.Set(-0.5,-1.5,0);
	//globals.GetDraw(L"character leg right").selfTransform.rotate.x = 2.5;

	//Draw Player
	drawOrder player = globals.GetDraw(L"character body");
	player.SetNameAs(L"player");
	player.transform.translate.Set(10,0.1,0);
	player.SetTerminalVelocityTo(Vector3(60,60,60));
	player.staticFriction = 0.03;
	player.mass = 0;
	globals.AddDraw(player);

	//Draw Shopper Wanderers at level 2
	drawOrder shopperwandererbody = globals.GetDraw(L"character body");
	Vector3 shopperwandererbodyTranslate(0,3.8,0);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(shopperwandererbody);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"shopper_wanderer_body%d",i);
		buffer.name = Namebuffer;
		buffer.transform.translate = shopperwandererbodyTranslate;
		globals.AddDraw(buffer);
		buffer.SetParentAs(&globals.GetDraw(L"main"));
	}
	drawOrder shopperwandererarmleft = globals.GetDraw(L"character arm left");
	Vector3 shopperwandererarmleftTranslate(1.25,0.6,0);
	float shopperwandererarmleftRotateX= -5;
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(shopperwandererarmleft);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"shopper_wanderer_arm_left%d",i);
		buffer.name = Namebuffer;
		wchar_t SWParentNamebuffer[64];
		wsprintf(SWParentNamebuffer,L"shopper_wanderer_body%d",i);
		buffer.SetParentAs(&globals.GetDraw(SWParentNamebuffer));
		buffer.transform.translate = shopperwandererarmleftTranslate;
		buffer.transform.rotate.x = shopperwandererarmleftRotateX;
		globals.AddDraw(buffer);
		//shopperwandererarmleftTranslate+= Vector3(0,15,0);
	}
	drawOrder shopperwandererarmright = globals.GetDraw(L"character arm right");
	Vector3 shopperwandererarmrightTranslate(-1.25,0.6,0);
	float shopperwandererarmrightRotateX= -5;
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(shopperwandererarmright);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"shopper_wanderer_arm_right%d",i);
		buffer.name = Namebuffer;
		wchar_t SWParentNamebuffer[64];
		wsprintf(SWParentNamebuffer,L"shopper_wanderer_body%d",i);
		buffer.SetParentAs(&globals.GetDraw(SWParentNamebuffer));
		buffer.transform.translate = shopperwandererarmrightTranslate;
		buffer.transform.rotate.x = shopperwandererarmrightRotateX;
		globals.AddDraw(buffer);
		//shopperwandererarmrightTranslate+= Vector3(0,15,0);
	}
	drawOrder shopperwandererlegleft = globals.GetDraw(L"character leg left");
	Vector3 shopperwandererlegleftTranslate(0.5,-1.5,0);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(shopperwandererlegleft);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"shopper_wanderer_leg_left%d",i);
		buffer.name = Namebuffer;
		wchar_t SWParentNamebuffer[64];
		wsprintf(SWParentNamebuffer,L"shopper_wanderer_body%d",i);
		buffer.SetParentAs(&globals.GetDraw(SWParentNamebuffer));
		buffer.transform.translate = shopperwandererlegleftTranslate;
		globals.AddDraw(buffer);
		//shopperwandererlegleftTranslate+= Vector3(0,15,0);
	}
	drawOrder shopperwandererlegright = globals.GetDraw(L"character leg right");
	Vector3 shopperwandererlegrightTranslate(-0.5,-1.5,0);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(shopperwandererlegright);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"shopper_wanderer_leg_right%d",i);
		buffer.name = Namebuffer;
		wchar_t SWParentNamebuffer[64];
		wsprintf(SWParentNamebuffer,L"shopper_wanderer_body%d",i);
		buffer.SetParentAs(&globals.GetDraw(SWParentNamebuffer));
		buffer.transform.translate = shopperwandererlegrightTranslate;
		globals.AddDraw(buffer);
		//shopperwandererlegrightTranslate+= Vector3(0,15,0);
	}

	//Draw Lift
	drawOrder lift(L"lift",globals.GetMesh(L"lift"), &globals.GetMaterial(L"lift"), &globals.GetDraw(L"main"), true);
	Vector3 liftTranslate(15.0,5.5,-101.6);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(lift);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"lift%d",i);
		buffer.name = Namebuffer;
		buffer.transform.translate = liftTranslate;
		globals.AddDraw(buffer);
		liftTranslate+= Vector3(0,10.1,0);
	}

	//Draw liftdoor
	globals.AddDraw(drawOrder(L"liftdoor_1_left",globals.GetMesh(L"liftdoor"), &globals.GetMaterial(L"liftdoor"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"liftdoor_1_left").transform.translate.Set(14.0,5,-98.6);

	globals.AddDraw(drawOrder(L"liftdoor_1_right",globals.GetMesh(L"liftdoor"), &globals.GetMaterial(L"liftdoor"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"liftdoor_1_right").transform.translate.Set(16.0,5,-98.6);

	globals.AddDraw(drawOrder(L"liftdoor_2_left",globals.GetMesh(L"liftdoor"), &globals.GetMaterial(L"liftdoor"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"liftdoor_2_left").transform.translate.Set(14.0,15.1,-98.6);

	globals.AddDraw(drawOrder(L"liftdoor_2_right",globals.GetMesh(L"liftdoor"), &globals.GetMaterial(L"liftdoor"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"liftdoor_2_right").transform.translate.Set(16.0,15.1,-98.6);

	//Draw Cashier Table
	drawOrder cashiertable(L"cashiertable",globals.GetMesh(L"cashiertable"), &globals.GetMaterial(L"cashiertable"), &globals.GetDraw(L"main"), true);
	Vector3 cashiertableTranslate(5,1,-84.2);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(cashiertable);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"cashiertable%d",i);
		buffer.name = Namebuffer;
		buffer.transform.translate = cashiertableTranslate;
		globals.AddDraw(buffer);
		cashiertableTranslate+= Vector3(-15,0,0);
	}

	//Draw cashier robot0
	globals.AddDraw(drawOrder(L"robotbody0",globals.GetMesh(L"robotbody"), &globals.GetMaterial(L"robot"), &globals.GetDraw(L"cashiertable0"), true));
	globals.GetDraw(L"robotbody0").transform.translate.Set(1,4,-4);

	globals.AddDraw(drawOrder(L"robotarm_left0",globals.GetMesh(L"robotarm"), &globals.GetMaterial(L"robot"), &globals.GetDraw(L"robotbody0"), true));
	globals.GetDraw(L"robotarm_left0").transform.translate.Set(-1,1,0);

	globals.AddDraw(drawOrder(L"robotarm_right0",globals.GetMesh(L"robotarm"), &globals.GetMaterial(L"robot"), &globals.GetDraw(L"robotbody0"), true));
	globals.GetDraw(L"robotarm_right0").transform.translate.Set(1,1,0);

	//Draw cashier robot1
	globals.AddDraw(drawOrder(L"robotbody1",globals.GetMesh(L"robotbody"), &globals.GetMaterial(L"robot"), &globals.GetDraw(L"cashiertable1"), true));
	globals.GetDraw(L"robotbody1").transform.translate.Set(1,4,-4);

	globals.AddDraw(drawOrder(L"robotarm_left1",globals.GetMesh(L"robotarm"), &globals.GetMaterial(L"robot"), &globals.GetDraw(L"robotbody1"), true));
	globals.GetDraw(L"robotarm_left1").transform.translate.Set(-1,1,0);

	globals.AddDraw(drawOrder(L"robotarm_right1",globals.GetMesh(L"robotarm"), &globals.GetMaterial(L"robot"), &globals.GetDraw(L"robotbody1"), true));
	globals.GetDraw(L"robotarm_right1").transform.translate.Set(1,1,0);

	//Draw Travelator Support
	drawOrder travelatorsupport(L"travelatorsupport",globals.GetMesh(L"travelatorsupport"), &globals.GetMaterial(L"dullwhite"), &globals.GetDraw(L"main"), true);
	Vector3 travelatorsupportTranslate(-2,7.1,-21.6);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(travelatorsupport);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"travelatorsupport%d",i);
		buffer.name = Namebuffer;
		buffer.transform.translate = travelatorsupportTranslate;
		globals.AddDraw(buffer);
		travelatorsupportTranslate+= Vector3(0,0,-3.14);
	}
	//Draw Travelator Slope
	drawOrder travelatorslope(L"travelatorslope",globals.GetMesh(L"travelatorslope"), &globals.GetMaterial(L"travelatorslope"), &globals.GetDraw(L"main"), true);
	Vector3 travelatorslopeTranslate(-2,5.91,-21.5);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(travelatorslope);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"travelatorslope%d",i);
		buffer.name = Namebuffer;
		buffer.transform.translate = travelatorslopeTranslate;
		globals.AddDraw(buffer);
		travelatorslopeTranslate+= Vector3(0,0,-3.05);
	}
	//Draw Travelator Handle 1 AND 2
	drawOrder travelatorhandle(L"travelatorhandle",globals.GetMesh(L"travelatorhandle"), &globals.GetMaterial(L"travelatorhandle"), &globals.GetDraw(L"main"), true);
	Vector3 travelatorhandleTranslate(-1.8,7.8,-20.4);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(travelatorhandle);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"travelatorhandle%d",i);
		buffer.name = Namebuffer;
		buffer.transform.translate = travelatorhandleTranslate;
		globals.AddDraw(buffer);
		travelatorhandleTranslate+= Vector3(0,0,-2.25);
	}
	//Draw Travelator Handle 3 AND 4
	drawOrder travelatorhandle2(L"travelatorhandle",globals.GetMesh(L"travelatorhandle"), &globals.GetMaterial(L"travelatorhandle"), &globals.GetDraw(L"main"), true);
	Vector3 travelatorhandleTranslate2(-1.8,7.8,-23.6);
	for(int i = 3; i < 5; ++i)
	{
		drawOrder buffer(travelatorhandle2);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"travelatorhandle%d",i);
		buffer.name = Namebuffer;
		buffer.transform.translate = travelatorhandleTranslate2;
		globals.AddDraw(buffer);
		travelatorhandleTranslate2+= Vector3(0,0,-2.10);
	}

	//Draw Outer Door
	globals.AddDraw(drawOrder(L"outer_door_1_right",globals.GetMesh(L"outerdoor"), &globals.GetMaterial(L"door texture"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"outer_door_1_right").transform.translate.Set(2,4.5,-8.6);

	globals.AddDraw(drawOrder(L"outer_door_1_left",globals.GetMesh(L"outerdoor"), &globals.GetMaterial(L"door texture"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"outer_door_1_left").transform.translate.Set(-2,4.5,-8.6);
	globals.GetDraw(L"outer_door_1_left").transform.rotate.Set(0,180,0);

	globals.AddDraw(drawOrder(L"outer_door_2_right",globals.GetMesh(L"outerdoor"), &globals.GetMaterial(L"door texture"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"outer_door_2_right").transform.translate.Set(-9,4.5,-105.4);

	globals.AddDraw(drawOrder(L"outer_door_2_left",globals.GetMesh(L"outerdoor"), &globals.GetMaterial(L"door texture"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"outer_door_2_left").transform.translate.Set(-13,4.5,-105.4);
	globals.GetDraw(L"outer_door_2_left").transform.rotate.Set(0,180,0);

	globals.AddDraw(drawOrder(L"inner_door_1",globals.GetMesh(L"innerdoor"), &globals.GetMaterial(L"door texture"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"inner_door_1").transform.translate.Set(-17.5,4.5,-19.6);
	globals.GetDraw(L"inner_door_1").transform.rotate.Set(0,180,0);

	globals.AddDraw(drawOrder(L"inner_door_2",globals.GetMesh(L"innerdoor"), &globals.GetMaterial(L"door texture"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"inner_door_2").transform.translate.Set(-17.5,14.5,-19.6);
	globals.GetDraw(L"inner_door_2").transform.rotate.Set(0,180,0);

	//Draw Trolley First Row
	drawOrder trolley(L"trolley",globals.GetMesh(L"trolley"), &globals.GetMaterial(L"trolley"), &globals.GetDraw(L"main"), true);
	Vector3 trolleyTranslate(16,1.2,-16);
	for(int i = 0; i < 3; ++i)
	{
		drawOrder buffer(trolley);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"trolley%d",i);
		buffer.name = Namebuffer;
		buffer.transform.translate = trolleyTranslate;
		globals.AddDraw(buffer);
		trolleyTranslate+= Vector3(-1.5,0,0);
	}

	//Draw Trolley Second Row
	drawOrder trolley2(L"trolley",globals.GetMesh(L"trolley"), &globals.GetMaterial(L"trolley"), &globals.GetDraw(L"main"), true);
	Vector3 trolleyTranslate2(16,1.2,-12);
	for(int i = 3; i < 6; ++i)
	{
		drawOrder buffer(trolley2);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"trolley%d",i);
		buffer.name = Namebuffer;
		buffer.transform.translate = trolleyTranslate2;
		globals.AddDraw(buffer);
		trolleyTranslate2+= Vector3(-1.5,0,0);
	}

	//Draw lv1Cabinet3_column1
	drawOrder lv1cabinet3_column1(L"lv1cabinet3_column1",globals.GetMesh(L"cabinet3"), &globals.GetMaterial(L"cabinet"), &globals.GetDraw(L"main"), true);
	Vector3 lv1cabinet3_column1Translate(-3.5,1,-42);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(lv1cabinet3_column1);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"lv1cabinet3_column1_%d",i);
		buffer.name = Namebuffer;
		buffer.transform.translate = lv1cabinet3_column1Translate; 
		globals.AddDraw(buffer);
		lv1cabinet3_column1Translate+= Vector3(0,0,-18);
	}

	//Draw lv2Cabinet1_column1
	drawOrder lv2cabinet1_column1(L"lv2cabinet1_column1",globals.GetMesh(L"cabinet1"), &globals.GetMaterial(L"cabinet"), &globals.GetDraw(L"main"), true);
	Vector3 lv2cabinet1_column1Translate(-18,11,-43);
	for(int i = 0; i < 5; ++i)
	{
		drawOrder buffer(lv2cabinet1_column1);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"lv2cabinet1_column1_%d",i);
		buffer.name = Namebuffer;
		buffer.transform.translate = lv2cabinet1_column1Translate; 
		buffer.transform.rotate.Set(0,90,0);
		globals.AddDraw(buffer);
		lv2cabinet1_column1Translate+= Vector3(0,0,-13);
	}

	//Draw lv2Cabinet2_column1
	drawOrder lv2cabinet2_column1(L"lv2cabinet2_column1",globals.GetMesh(L"cabinet2"), &globals.GetMaterial(L"cabinet"), &globals.GetDraw(L"main"), true);
	Vector3 lv2cabinet2_column1Translate(-2,11,-43);
	for(int i = 0; i < 4; ++i)
	{
		drawOrder buffer(lv2cabinet2_column1);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"lv2cabinet2_column1_%d",i);
		buffer.name = Namebuffer;
		buffer.transform.translate = lv2cabinet2_column1Translate; 
		buffer.transform.rotate.Set(0,-90,0);
		globals.AddDraw(buffer);
		lv2cabinet2_column1Translate+= Vector3(0,0,-16);
	}

	//Draw lv2Cabinet2_column2
	drawOrder lv2cabinet2_column2(L"lv2cabinet2_column2",globals.GetMesh(L"cabinet2"), &globals.GetMaterial(L"cabinet"), &globals.GetDraw(L"main"), true);
	Vector3 lv2cabinet2_column2Translate(1.5,11,-43);
	for(int i = 0; i < 4; ++i)
	{
		drawOrder buffer(lv2cabinet2_column2);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"lv2cabinet2_column2_%d",i);
		buffer.name = Namebuffer;
		buffer.transform.translate = lv2cabinet2_column2Translate; 
		buffer.transform.rotate.Set(0,90,0);
		globals.AddDraw(buffer);
		lv2cabinet2_column2Translate+= Vector3(0,0,-16);
	}
	//Draw Hidden room cabinets
	drawOrder lv2cabinet4_hiddenroom(L"lv2cabinet4_hiddenroom",globals.GetMesh(L"cabinet4"), &globals.GetMaterial(L"cabinet"), &globals.GetDraw(L"main"), true);
	Vector3 lv2cabinet4_hiddenroomTranslate(3,11,-16);
	for(int i = 0; i < 2; ++i)
	{
	drawOrder buffer(lv2cabinet4_hiddenroom);
	wchar_t Namebuffer[64];
	wsprintf(Namebuffer,L"lv2cabinet4_hiddenroom_%d",i);
	buffer.name = Namebuffer;
	buffer.transform.translate = lv2cabinet4_hiddenroomTranslate; 
	buffer.transform.rotate.y=90;
	globals.AddDraw(buffer);
	lv2cabinet4_hiddenroomTranslate+= Vector3(-14,0,0);
	}
	drawOrder lv2cabinet5_hiddenroom(L"lv2cabinet5_hiddenroom",globals.GetMesh(L"cabinet4"), &globals.GetMaterial(L"cabinet"), &globals.GetDraw(L"main"), true);
	Vector3 lv2cabinet5_hiddenroomTranslate(10,11,-12);
	for(int i = 0; i < 2; ++i)
	{
	drawOrder buffer(lv2cabinet5_hiddenroom);
	wchar_t Namebuffer[64];
	wsprintf(Namebuffer,L"lv2cabinet5_hiddenroom_%d",i);
	buffer.name = Namebuffer;
	buffer.transform.translate = lv2cabinet5_hiddenroomTranslate; 
	buffer.transform.rotate.y=90;
	globals.AddDraw(buffer);
	lv2cabinet5_hiddenroomTranslate+= Vector3(-14,0,0);
	}

	CreateItems(drawOrder(L"can1_cabinet1_",globals.GetMesh(L"can1"), &globals.GetMaterial(L"can1"), NULL, true),Vector3(-3.25,5.5,1), L"lv2cabinet1_column1_0", 6, 6, 1, 0.5, -0.4, 2, 5, Vector3(1.5,0,0), Vector3(6.5,0,0));
	CreateItems(drawOrder(L"can2_cabinet1_",globals.GetMesh(L"can2"), &globals.GetMaterial(L"can2"), NULL, true),Vector3(-3.25,3.2,1), L"lv2cabinet1_column1_0", 2, 3, 0.45, 1.2, -0.9, 2, 5, Vector3(1.7,0,0), Vector3(6.5,0,0));
	CreateItems(drawOrder(L"can3_cabinet1_",globals.GetMesh(L"can3"), &globals.GetMaterial(L"can3"), NULL, true),Vector3(-3.2,0.4,1), L"lv2cabinet1_column1_0", 5, 5, 1, 0.6, -0.5, 2, 5, Vector3(1.55,0,0), Vector3(6.65,0,0));
}

void SceneMain::InnitItems(const drawOrder& basedraw, const Vector3 offset, Vector3 increment)
{
	Vector3 individualOffset = offset;
	for(int i = 0; i < 2; ++i, individualOffset += increment)
	{
		drawOrder buffer(basedraw);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"lv2cabinet5_hiddenroom_%d",i);
		buffer.name = Namebuffer;
		buffer.transform.translate = individualOffset; 
		buffer.transform.rotate.y=90;
		globals.AddDraw(buffer);
	}
}

void SceneMain::CreateItems(drawOrder& item, Vector3 offset, std::wstring parentname, int ItemPerColumn, int ColumnPerCompartment,float defaultZ, float ItemDistanceX,float ItemDistanceZ, int NumBunch, int NumCabinet, Vector3 BunchOffset, Vector3 CabinetOffset)
{	
	int item_count = 0;

	for(int i = 0; i < NumCabinet; i++) // place in 5 cabinet
	{
		if (i>0)
		{
			offset += CabinetOffset;
		}

		for(int i = 0; i < NumBunch; i++) // 2 bunch for one cabinet
		{	
			if (i>0)
			{
				offset += BunchOffset;
			}

			for(int i = 0; i < ColumnPerCompartment; ++i) // 6 column for one compartment
			{
				offset.z = defaultZ;
				if(i>0)
				{
					offset+= Vector3(ItemDistanceX,0,0);
				}

				for(int i = 0; i < ItemPerColumn; ++i) //6 cans in one column
				{
					drawOrder buffer(item);
					std::wstring name(item.name);
					name += item_count;
					buffer.name = name;
					buffer.transform.translate = offset; 
					globals.AddDraw(buffer);
					offset+= Vector3(0,0,ItemDistanceZ);
					globals.GetDraw(name).SetParentAs(&globals.GetDraw(parentname));
				}
			}
		}
	}
}

void SceneMain::InnitVoxels()
{
	StopWatch timer;
	timer.startTimer();
	Vertex Vertex1;
	Vertex1.pos.Set(24,59,85);
	Vertex Vertex2;
	Vertex2.pos.Set(76,95,31);
	Vertex Vertex3;
	Vertex3.pos.Set(75,98,91);
	for(int index = 0; index < 1000000; ++index)
	{
		Polygonn::Polygonn(Vertex1, Vertex2, Vertex3);
	}
	const double elapsed = timer.getElapsedTime();
	for(std::map<std::wstring, drawOrder*>::iterator draw = globals.GetDrawList().begin(); draw != globals.GetDrawList().end(); ++draw)
	{
		draw->second->GenerateVoxels();
	}
}

void SceneMain::InnitForces()
{
	Vector3 accelerationDueToGravity(0, -9.8f, 0);
	for(std::map<std::wstring, drawOrder*>::iterator draw = globals.GetDrawList().begin(); draw != globals.GetDrawList().end(); ++draw)
	{
		draw->second->AddForce(accelerationDueToGravity * draw->second->mass);
	}
}

bool SceneMain::Update(const double dt)
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
	if(UpdateLv2 == true)
	{
		for(int i = 0; i < 2; ++i)
		{
			SWLv2[i].Update(dt);
		}
	}
	return false;
}

void SceneMain::UpdateLogic()
{
}

void SceneMain::UpdateView()
{
	//positions are offset a little from their proper position because of floating point error
	globals.GetDraw(L"skybox").transform.translate = Vector3(0,0,0) + camera.ReturnPosition();

	if(isFrog == false)
	{
		//camera.Translate(globals.GetDraw(L"player").transform.translate - camera.ReturnPosition() + Vector3(0, 10, 0));
	}
	else
	{
		//camera.Translate(globals.GetDraw(L"player").transform.translate - camera.ReturnPosition() + Vector3(0, 3, 0));
	}
	float player_rotationY = camera.GetRotation().y - globals.GetDraw(L"player").transform.rotate.y;
	float player_current_frame_rotationY = player_rotationY / 25;
	globals.GetDraw(L"player").transform.rotate.y += player_current_frame_rotationY;
	gfx.SetViewAt(camera);
}

void SceneMain::UpdateLight()
{
	gfx.UpdateLights();
}

void SceneMain::UpdateDraws()
{
	//where forces are applied
	//for(std::vector<drawOrder>::iterator draw = drawOrders.begin(); draw != drawOrders.end(); draw++)
	//{
	//	//an object has 0 mass if it is infinitely heavy and forces will barely have any effect on it including gravity. This is totally how physics work
	//	draw->UpdateVelocity(deltaTime);
	//	draw->UpdateForcesTo(deltaTime);
	//}

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
	//collisionSystem.CheckThisCollision(&drawOrders[DRAW_GROUND],&drawOrders[DRAW_PLAYER],deltaTime);
	//collisionSystem.ResolveAllCollisionsAccordingTo(deltaTime);

	//draws are finally updated after processing
	//for(std::vector<drawOrder>::iterator draw = drawOrders.begin(); draw != drawOrders.end(); draw++)
	//{
	//	draw->UpdateTo(deltaTime);
	//}
}

void SceneMain::Render()
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
		drawOrder draw_cube(L"cube");
		draw_cube.geometry = globals.GetMesh(L"cube");
		draw_cube.enableLight = true;
		draw_cube.material = &material;
		material.SetShininessTo(20);
		for(std::map<std::wstring, drawOrder*>::iterator draw = globals.GetDrawList().begin(); draw != globals.GetDrawList().end(); ++draw)
		{
			Mtx44 matrix(draw->second->GetMatrix());
			for(std::vector<Voxel>::iterator voxel = draw->second->voxels.begin(); voxel != draw->second->voxels.end(); voxel++)
			{
				voxel->ApplyToMatrix(matrix);
				Mtx44 translate;
				translate.SetToTranslation(voxel->GetPosition());
				gfx.RenderMesh(draw_cube, translate);
			}
		}
	}
	else
	{
		globals.GetDraw(L"main").Execute(gfx);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

void SceneMain::Exit()
{
}

void SceneMain::DoUserInput()
{
	double mouseX;
	double mouseY;
	mouse.Update(mouseX, mouseY);
	const int CAMERA_SPEED = 2.5;
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
	if (keyboard.isKeyPressed('Y'))
	{
		for(int i = 0; i < 2; ++i)
		{
			SWLv2[i].Reset();
		}
		UpdateLv2 = false;
	}
	if (keyboard.isKeyPressed('U'))
	{
		UpdateLv2 = true;
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
		if(isFrog == true && isJumping == false && isFalling == false)
		{
			isJumping = true;
		}
	}
	//Jump
	if (keyboard.isKeyHold(VK_SPACE) && isJumping == false && isFalling == false && isFrog == false)
	{
		isJumping = true;
	}
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
	//
	//if (keyboard.isKeyHold('O'))
	//{	
	//	Vector3 tempVector;
	//	tempVector.Set(0, 50, 0);
	//	playerAcceleration += tempVector;
	//}
	//if (keyboard.isKeyHold('P'))
	//{
	//	Vector3 tempVector;
	//	tempVector.Set(0, -50, 0);
	//	playerAcceleration += tempVector;
	//}
	//
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
	playerAcceleration += player->Update(camera);
	Force playerForce;
	playerForce.SetLifespanTo(0.0001);
	playerForce.SetVector(playerAcceleration);
	globals.GetDraw(L"player").AddForce(playerForce);
}