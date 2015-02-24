#include "SceneMain.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "PlayerHuman.h"
#include "PlayerFrog.h"


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

	camera.Init(Vector3(21.7, 5, 68.3), Vector3(1, 0, 0), Vector3(0, 1, 0));
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
	globals.AddTexture(L"TrolleyTexture", L"Image//TrolleyTexture.tga");
	globals.AddTexture(L"character1", L"Image//character1.tga");
}

void SceneMain::InnitMaterials()
{
	globals.AddMaterial(Material(L"skybox",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"skybox")));
	globals.AddMaterial(Material(L"ground",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"ground")));
	globals.AddMaterial(Material(L"building",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"building")));
	globals.AddMaterial(Material(L"cashiertable",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"cashiertable texture")));
	globals.AddMaterial(Material(L"Cabinet",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"CabinetTexture")));
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
	globals.AddMaterial(Material(L"travellatorhandle",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"travelatorhandle texture")));
	globals.AddMaterial(Material(L"travellatorslope",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"travelatorslope texture2")));
	globals.AddMaterial(Material(L"Trolley",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"TrolleyTexture")));
	globals.AddMaterial(Material(L"character1",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"character1")));
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
	globals.AddMesh(MeshBuilder::GenerateRepeatQuad(L"ground", Color(1, 1, 1), 50.f, 50.f));
	globals.AddMesh(MeshBuilder::GenerateCube(L"cube",Color(),1,1,1));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cashiertable", L"OBJ//cashiertable.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"Cabinet1", L"OBJ//Cabinet1.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"Cabinet2", L"OBJ//Cabinet2.obj"));
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
}

void SceneMain::InnitDraws()
{
	//main will be the main draw order that all other draw orders are children of
	globals.AddDraw(drawOrder(L"main"));

	//Draw SkyBox
	globals.AddDraw(drawOrder(L"skybox",globals.GetMesh(L"skybox"), &globals.GetMaterial(L"skybox"), NULL));
	globals.GetDraw(L"skybox").transform.translate.Set(0,0,0);
	globals.GetDraw(L"skybox").transform.scale.Set(10000,10000,10000);

	//Draw Ground
	globals.AddDraw(drawOrder(L"ground",globals.GetMesh(L"ground"), &globals.GetMaterial(L"ground"), NULL, true));
	globals.GetDraw(L"ground").transform.translate.Set(0,0,0);
	globals.GetDraw(L"ground").transform.scale.Set(5,5,5);

	//Draw Building
	globals.AddDraw(drawOrder(L"building",globals.GetMesh(L"building"), &globals.GetMaterial(L"building"), NULL, true));
	globals.GetDraw(L"building").transform.translate.Set(0,0.1,-30);

	//Draw Character
	globals.AddDraw(drawOrder(L"character body",globals.GetMesh(L"characterbody"), &globals.GetMaterial(L"character1"), NULL, true));
	globals.GetDraw(L"character body").transform.translate.Set(0,3,0);

	globals.AddDraw(drawOrder(L"character arm left",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character1"), NULL, true));
	globals.GetDraw(L"character arm left").transform.translate.Set(-1.25,-0.4,0);

	globals.AddDraw(drawOrder(L"character arm right",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character1"), NULL, true));
	globals.GetDraw(L"character arm right").transform.translate.Set(1.25,-0.4,0);

	globals.AddDraw(drawOrder(L"character leg left",globals.GetMesh(L"characterleg"), &globals.GetMaterial(L"character1"), NULL, true));
	globals.GetDraw(L"character leg left").transform.translate.Set(-0.5,-2.5,0);

	globals.AddDraw(drawOrder(L"character leg right",globals.GetMesh(L"characterleg"), &globals.GetMaterial(L"character1"), NULL, true));
	globals.GetDraw(L"character leg right").transform.translate.Set(0.5,-2.5,0);

	//Draw Player
	drawOrder player = globals.GetDraw(L"character body");
	player.SetNameAs(L"player");
	player.transform.translate.Set(10,0.1,0);
	player.SetTerminalVelocityTo(Vector3(60,60,60));
	player.staticFriction = 0.03;
	player.mass = 0;
	globals.AddDraw(player);

	//Draw Lift
	drawOrder lift(L"lift",globals.GetMesh(L"lift"), &globals.GetMaterial(L"lift"), NULL, true);
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

	//Draw Cashier Table
	drawOrder cashiertable(L"cashiertable",globals.GetMesh(L"cashiertable"), &globals.GetMaterial(L"cashiertable"), NULL, true);
	Vector3 cashiertableTranslate(5,1,-88.5);
	for(int i = 0; i < 2; ++i)
	{
	drawOrder buffer(cashiertable);
	wchar_t Namebuffer[64];
	wsprintf(Namebuffer,L"cashiertable%d",i);
	buffer.name = Namebuffer;
	buffer.transform.translate = cashiertableTranslate;
	globals.AddDraw(buffer);
	cashiertableTranslate+= Vector3(-11,0,0);
	}

	//Draw Travelator Support
	drawOrder travelatorsupport(L"travelatorsupport",globals.GetMesh(L"travelatorsupport"), &globals.GetMaterial(L"dullwhite"), NULL, true);
	Vector3 travelatorsupportTranslate(-2,7.1,-21.6);
	for(int i = 0; i < 2; ++i)
	{
	drawOrder buffer(travelatorsupport);
	wchar_t Namebuffer[64];
	wsprintf(Namebuffer,L"travelatorsupport%d",i);
	buffer.name = Namebuffer;
	buffer.transform.translate = travelatorsupportTranslate;
	globals.AddDraw(buffer);
	travelatorsupportTranslate+= Vector3(0,0,-1.19);
	}

	//Setting Parents
	globals.GetDraw(L"skybox").SetParentAs(&globals.GetDraw(L"main"));
	globals.GetDraw(L"ground").SetParentAs(&globals.GetDraw(L"main"));
	globals.GetDraw(L"building").SetParentAs(&globals.GetDraw(L"main"));

	//Character parent setting
	globals.GetDraw(L"character body").SetParentAs(&globals.GetDraw(L"main"));
	globals.GetDraw(L"character arm left").SetParentAs(&globals.GetDraw(L"character body"));
	globals.GetDraw(L"character arm right").SetParentAs(&globals.GetDraw(L"character body"));
	globals.GetDraw(L"character leg left").SetParentAs(&globals.GetDraw(L"character body"));
	globals.GetDraw(L"character leg right").SetParentAs(&globals.GetDraw(L"character body"));

	//player parent setting
	globals.GetDraw(L"player").SetParentAs(&globals.GetDraw(L"main"));

	//lift parent setting
	for(int i = 0; i < 2; ++i)
	{
	wchar_t Namebuffer[64];
	wsprintf(Namebuffer,L"lift%d",i);
	globals.GetDraw(Namebuffer).SetParentAs(&globals.GetDraw(L"main"));
	}

	//cashier table parent setting
	for(int i = 0; i < 2; ++i)
	{
	wchar_t Namebuffer[64];
	wsprintf(Namebuffer,L"cashiertable%d",i);
	globals.GetDraw(Namebuffer).SetParentAs(&globals.GetDraw(L"main"));
	}

	//travelator support parent setting
	for(int i = 0; i < 2; ++i)
	{
	wchar_t Namebuffer[64];
	wsprintf(Namebuffer,L"travelatorsupport%d",i);
	globals.GetDraw(Namebuffer).SetParentAs(&globals.GetDraw(L"main"));
	}

	

	//Draw Items
	//drawOrders[DRAW_CASHIER_TABLE].geometry = meshList[DRAW_CASHIER_TABLE];
	//drawOrders[DRAW_CASHIER_TABLE].transform.translate.Set(5,1,-88.5);

	//drawOrders[DRAW_CABINET1].geometry = meshList[GEO_CABINET1];
	//drawOrders[DRAW_CABINET1].transform.translate.Set(0,1.5,-40);

	//drawOrders[DRAW_CABINET2].geometry = meshList[GEO_CABINET2];
	//drawOrders[DRAW_CABINET2].transform.translate.Set(-10,0.1,0);

	//drawOrders[DRAW_CAN1].geometry = meshList[GEO_CAN1];
	//drawOrders[DRAW_CAN1].transform.translate.Set(15,2,0);

	//drawOrders[DRAW_CAN2].geometry = meshList[GEO_CAN2];
	//drawOrders[DRAW_CAN2].transform.translate.Set(20,0.1,0);

	//drawOrders[DRAW_CAN3].geometry = meshList[GEO_CAN3];
	//drawOrders[DRAW_CAN3].transform.translate.Set(25,0.1,0);

	//drawOrders[DRAW_CEREAL1].geometry = meshList[GEO_CEREAL1];
	//drawOrders[DRAW_CEREAL1].transform.translate.Set(30,0.1,0);

	//drawOrders[DRAW_CEREAL2].geometry = meshList[GEO_CEREAL2];
	//drawOrders[DRAW_CEREAL2].transform.translate.Set(35,0.1,0);

	//drawOrders[DRAW_CEREAL3].geometry = meshList[GEO_CEREAL3];
	//drawOrders[DRAW_CEREAL3].transform.translate.Set(40,0.1,0);

	//drawOrders[DRAW_PACKET1].geometry = meshList[GEO_PACKET1];
	//drawOrders[DRAW_PACKET1].transform.translate.Set(45,0.1,0);

	//drawOrders[DRAW_PACKET2].geometry = meshList[GEO_PACKET2];
	//drawOrders[DRAW_PACKET2].transform.translate.Set(50,0.1,0);

	//drawOrders[DRAW_PACKET3].geometry = meshList[GEO_PACKET3];
	//drawOrders[DRAW_PACKET3].transform.translate.Set(55,0.1,0);

	////Draw Building
	//drawOrders[DRAW_BUILDING].geometry = meshList[GEO_BUILDING];
	//drawOrders[DRAW_BUILDING].transform.translate.Set(0,0.1,-30);
	//
	//drawOrders[DRAW_LIFT_1].geometry = meshList[GEO_LIFT];
	//drawOrders[DRAW_LIFT_1].transform.translate.Set(15.0,5.5,-101.6);

	//drawOrders[DRAW_LIFT_2].geometry = meshList[GEO_LIFT];
	//drawOrders[DRAW_LIFT_2].transform.translate.Set(15.0,15.6,-101.6);

	//drawOrders[DRAW_LIFTDOOR_1_LEFT].geometry = meshList[GEO_LIFTDOOR];
	//drawOrders[DRAW_LIFTDOOR_1_LEFT].transform.translate.Set(14.0,5,-98.6);

	//drawOrders[DRAW_LIFTDOOR_1_RIGHT].geometry = meshList[GEO_LIFTDOOR];
	//drawOrders[DRAW_LIFTDOOR_1_RIGHT].transform.translate.Set(16.0,5,-98.6);

	//drawOrders[DRAW_LIFTDOOR_2_LEFT].geometry = meshList[GEO_LIFTDOOR];
	//drawOrders[DRAW_LIFTDOOR_2_LEFT].transform.translate.Set(14.0,15.1,-98.6);

	//drawOrders[DRAW_LIFTDOOR_2_RIGHT].geometry = meshList[GEO_LIFTDOOR];
	//drawOrders[DRAW_LIFTDOOR_2_RIGHT].transform.translate.Set(16.0,15.1,-98.6);

	////Draw Door
	//drawOrders[DRAW_OUTERDOOR_1_RIGHT].geometry = meshList[GEO_OUTERDOOR];
	//drawOrders[DRAW_OUTERDOOR_1_RIGHT].transform.translate.Set(2,4.5,-8.6);

	//drawOrders[DRAW_OUTERDOOR_1_LEFT].geometry = meshList[GEO_OUTERDOOR];
	//drawOrders[DRAW_OUTERDOOR_1_LEFT].transform.translate.Set(-2,4.5,-8.6);
	//drawOrders[DRAW_OUTERDOOR_1_LEFT].transform.rotate.Set(0,180,0);

	//drawOrders[DRAW_OUTERDOOR_2_RIGHT].geometry = meshList[GEO_OUTERDOOR];
	//drawOrders[DRAW_OUTERDOOR_2_RIGHT].transform.translate.Set(-9,4.5,-105.4);

	//drawOrders[DRAW_OUTERDOOR_2_LEFT].geometry = meshList[GEO_OUTERDOOR];
	//drawOrders[DRAW_OUTERDOOR_2_LEFT].transform.translate.Set(-13,4.5,-105.4);
	//drawOrders[DRAW_OUTERDOOR_2_LEFT].transform.rotate.Set(0,180,0);

	//drawOrders[DRAW_INNERDOOR_1].geometry = meshList[GEO_INNERDOOR];
	//drawOrders[DRAW_INNERDOOR_1].transform.translate.Set(-17.5,4.5,-19.6);
	//drawOrders[DRAW_INNERDOOR_1].transform.rotate.Set(0,180,0);

	//drawOrders[DRAW_INNERDOOR_2].geometry = meshList[GEO_INNERDOOR];
	//drawOrders[DRAW_INNERDOOR_2].transform.translate.Set(-17.5,14.5,-19.6);
	//drawOrders[DRAW_INNERDOOR_2].transform.rotate.Set(0,180,0);

	////Draw Travelator
	//drawOrders[DRAW_TRAVELATORSUPPORT_UP].geometry = meshList[GEO_TRAVELATORSUPPORT];
	//drawOrders[DRAW_TRAVELATORSUPPORT_UP].transform.translate.Set(-2,7.1,-21.6);

	//drawOrders[DRAW_TRAVELATORSLOPE_UP].geometry = meshList[GEO_TRAVELATORSLOPE];
	//drawOrders[DRAW_TRAVELATORSLOPE_UP].transform.translate.Set(-2,5.91,-21.6);

	//drawOrders[DRAW_TRAVELATORHANDLE_UP_1].geometry = meshList[GEO_TRAVELATORHANDLE];
	//drawOrders[DRAW_TRAVELATORHANDLE_UP_1].transform.translate.Set(-1.8,7.8,-20.4);

	//drawOrders[DRAW_TRAVELATORHANDLE_UP_2].geometry = meshList[GEO_TRAVELATORHANDLE];
	//drawOrders[DRAW_TRAVELATORHANDLE_UP_2].transform.translate.Set(-1.8,7.8,-22.65);

	//drawOrders[DRAW_TRAVELATORSUPPORT_DOWN].geometry = meshList[GEO_TRAVELATORSUPPORT];
	//drawOrders[DRAW_TRAVELATORSUPPORT_DOWN].transform.translate.Set(-2,7.1,-24.6);

	//drawOrders[DRAW_TRAVELATORSLOPE_DOWN].geometry = meshList[GEO_TRAVELATORSLOPE];
	//drawOrders[DRAW_TRAVELATORSLOPE_DOWN].transform.translate.Set(-2,5.91,-24.6);

	//drawOrders[DRAW_TRAVELATORHANDLE_DOWN_1].geometry = meshList[GEO_TRAVELATORHANDLE];
	//drawOrders[DRAW_TRAVELATORHANDLE_DOWN_1].transform.translate.Set(-1.8,7.8,-23.4);

	//drawOrders[DRAW_TRAVELATORHANDLE_DOWN_2].geometry = meshList[GEO_TRAVELATORHANDLE];
	//drawOrders[DRAW_TRAVELATORHANDLE_DOWN_2].transform.translate.Set(-1.8,7.8,-25.65);

	//drawOrders[DRAW_TROLLEY].geometry = meshList[GEO_TROLLEY];
	//drawOrders[DRAW_TROLLEY].transform.translate.Set(0,0.1,0);
}

void SceneMain::InnitVoxels()
{
	//drawOrders[DRAW_PLAYER].GenerateVoxels();
	//drawOrders[DRAW_GROUND].GenerateVoxels();
	//drawOrders[DRAW_CABINET1].GenerateVoxels();
	//drawOrders[DRAW_CAN1].GenerateVoxels();
	//drawOrders[DRAW_CAN2].GenerateVoxels();
	//drawOrders[DRAW_CAN3].GenerateVoxels();
	//drawOrders[DRAW_CEREAL1].GenerateVoxels();
	//drawOrders[DRAW_CEREAL2].GenerateVoxels();
	//drawOrders[DRAW_CEREAL3].GenerateVoxels();
	//drawOrders[DRAW_PACKET1].GenerateVoxels();
	//drawOrders[DRAW_PACKET2].GenerateVoxels();
	//drawOrders[DRAW_PACKET3].GenerateVoxels();
	//drawOrders[DRAW_BUILDING].GenerateVoxels();
}

void SceneMain::InnitForces()
{
	Vector3 accelerationDueToGravity(0, -9.8f, 0);
	for(std::map<std::wstring, drawOrder>::iterator draw = globals.GetDrawList().begin(); draw != globals.GetDrawList().end(); ++draw)
	{
		draw->second.AddForce(accelerationDueToGravity * draw->second.mass);
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
		draw_cube.enableLight = false;
		draw_cube.material = &material;
		//for(std::vector<drawOrder>::iterator draw = drawOrders.begin(); draw != drawOrders.end(); draw++)
		//{
		//	//check the individual voxel each object has. If one pair collides, collision is applied to the objects as a whole we break out of the loop
		//	for(std::vector<Voxel>::iterator voxel = draw->voxels.begin(); voxel != draw->voxels.end(); voxel++)
		//	{
		//		//draw_cube.geometry = MeshBuilder::GenerateCube(L"cube", voxel->GetColor(),Voxel::GetSize(),Voxel::GetSize(),Voxel::GetSize());
		//		Mtx44 translate, scale;
		//		voxel->ApplyCurrentMatrix();
		//		translate.SetToTranslation(voxel->GetPosition());
		//		gfx.RenderMesh(draw_cube, translate * scale);
		//		//delete (draw_cube.geometry);
		//	}
		//}
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