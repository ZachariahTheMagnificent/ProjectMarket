//#include "SceneMainMenu.h"
//#include "GL\glew.h"
//#include "Application.h"
//#include "shader.hpp"
//#include "MeshBuilder.h"
//#include "LoadTGA.h"
//#include "PlayerHuman.h"
//#include "PlayerFrog.h"
//
//SceneMainMenu::SceneMainMenu(Keyboard& keyboard, GLMouse& mouse, Sound& snd, Graphics& gfx)
//	:
//Scene(keyboard, mouse, snd, gfx)
//{
//}
//
//SceneMainMenu::~SceneMainMenu(void)
//{
//}
//
//void SceneMainMenu::Init()
//{
//	InnitLight();
//	InnitTextures();
//	InnitSounds();
//	InnitGeometry();
//	InnitDraws();
//	InnitVoxels();
//	InnitForces();
//	InnitLogic();
//	gfx.InitText(L"Image//kitten_bri.tga");
//	player = new PlayerHuman;
//	isJumping = false;
//	isFalling = false;
//	jumpedHeight = 0;
//	isFrog = false;
//
//	camera.Init(Vector3(21.7, 5, 68.3), Vector3(1, 0, 0), Vector3(0, 1, 0));
//	gfx.SetProjectionTo(45.f, 4.f / 3.f, 0.1f, 90000.f);
//	gfx.InitText(L"Image//kitten_bri.tga");
//}
//
//
//void SceneMainMenu::InnitSounds()
//{
//	//snd.loadWave("pure", "sound//pure.wav");
//}
//
//void SceneMainMenu::InnitLogic()
//{
//	frameCounter = 0;
//	accumulatingDT = 0;
//	currentFPS = 60;
//	drawVoxels = false;
//}
//
//void SceneMainMenu::InnitTextures()
//{
//	textures.resize(NUM_TEXTURES, 0);
//	textures[TEXTURE_SKYBOX] = LoadTGA(L"Image//skybox.tga");
//	textures[TEXTURE_GROUND] = LoadTGA(L"Image//ground.tga");
//	textures[TEXTURE_CABINET1] = LoadTGA(L"Image//Cabinet1Texture.tga");
//	textures[TEXTURE_CAN1] = LoadTGA(L"Image//can1.tga");
//	textures[TEXTURE_CAN2] = LoadTGA(L"Image//can2.tga");
//	textures[TEXTURE_CAN3] = LoadTGA(L"Image//can3.tga");
//	textures[TEXTURE_CEREAL1] = LoadTGA(L"Image//cereal1.tga");
//	textures[TEXTURE_CEREAL2] = LoadTGA(L"Image//cereal2.tga");
//	textures[TEXTURE_CEREAL3] = LoadTGA(L"Image//cereal3.tga");
//	textures[TEXTURE_PACKET1] = LoadTGA(L"Image//packet1.tga");
//	textures[TEXTURE_PACKET2] = LoadTGA(L"Image//packet2.tga");
//	textures[TEXTURE_PACKET3] = LoadTGA(L"Image//packet3.tga");
//	textures[TEXTURE_BUILDING] = LoadTGA(L"Image//dullwhite.tga");
//	textures[TEXTURE_LIFT] = LoadTGA(L"Image//blue.tga");
//	textures[TEXTURE_LIFTDOOR] = LoadTGA(L"Image//liftdoor.tga");
//	textures[TEXTURE_OUTERDOOR] = LoadTGA(L"Image//glassdoor_texture.tga");
//	textures[TEXTURE_INNERDOOR] = LoadTGA(L"Image//glassdoor_texture.tga");
//	textures[TEXTURE_TRAVELATORSUPPORT] = LoadTGA(L"Image//dullwhite.tga");
//	textures[TEXTURE_TRAVELATORSLOPE] = LoadTGA(L"Image//travelatorslope_texture.tga");
//	textures[TEXTURE_TRAVELATORHANDLE] = LoadTGA(L"Image//travelatorhandle_texture.tga");
//	textures[TEXTURE_LARGE_FORERUNNER_FLOOR_PLATE] = LoadTGA(L"Image//large_forerunner_floor_plate.tga");
//}
//
//void SceneMainMenu::InnitLight()
//{
//	light[WORLD_LIGHT].type = Light::LIGHT_DIRECTIONAL;
//	light[WORLD_LIGHT].position.Set(20, 20, 20);
//	light[WORLD_LIGHT].color.Set(1, 1, 1);
//	light[WORLD_LIGHT].power = 0.23;
//	light[WORLD_LIGHT].kC = 1.f;
//	light[WORLD_LIGHT].kL = 0.01f;
//	light[WORLD_LIGHT].kQ = 0.001f;
//	light[WORLD_LIGHT].cosCutoff = cos(Math::DegreeToRadian(180));
//	light[WORLD_LIGHT].cosInner = cos(Math::DegreeToRadian(30));
//	light[WORLD_LIGHT].exponent = 1.f;
//	light[WORLD_LIGHT].spotDirection.Set(0.f, 1.f, 1.f);
//
//	gfx.AddLight(&light[WORLD_LIGHT]);
//}
//
//void SceneMainMenu::InnitGeometry()
//{
//	//Initialize all meshes to NULL
//	meshList.resize(NUM_GEOMETRY, NULL);
//
//	meshList[GEO_SKYBOX] = MeshBuilder::GenerateOBJ(L"OBJ//skybox.obj");
//	meshList[GEO_GROUND] = MeshBuilder::GenerateRepeatQuad(L"ground", Color(1, 1, 1), 50.f, 50.f);
//	meshList[GEO_CUBE] = MeshBuilder::GenerateCube(L"Cube",Color(),1,1,1);
//	meshList[GEO_CABINET1] = MeshBuilder::GenerateOBJ(L"OBJ//Cabinet1.obj");
//	meshList[GEO_CAN1] = MeshBuilder::GenerateOBJ(L"OBJ//can1.obj");
//	meshList[GEO_CAN2] = MeshBuilder::GenerateOBJ(L"OBJ//can2.obj");
//	meshList[GEO_CAN3] = MeshBuilder::GenerateOBJ(L"OBJ//can3.obj");
//	meshList[GEO_CEREAL1] = MeshBuilder::GenerateOBJ(L"OBJ//cereal1.obj");
//	meshList[GEO_CEREAL2] = MeshBuilder::GenerateOBJ(L"OBJ//cereal2.obj");
//	meshList[GEO_CEREAL3] = MeshBuilder::GenerateOBJ(L"OBJ//cereal3.obj");
//	meshList[GEO_PACKET1] = MeshBuilder::GenerateOBJ(L"OBJ//packet1.obj");
//	meshList[GEO_PACKET2] = MeshBuilder::GenerateOBJ(L"OBJ//packet2.obj");
//	meshList[GEO_PACKET3] = MeshBuilder::GenerateOBJ(L"OBJ//packet3.obj");
//	meshList[GEO_BUILDING] = MeshBuilder::GenerateOBJ(L"OBJ//building.obj");
//	meshList[GEO_LIFT] = MeshBuilder::GenerateOBJ(L"OBJ//bluelift.obj");
//	meshList[GEO_LIFTDOOR] = MeshBuilder::GenerateOBJ(L"OBJ//liftdoor.obj");
//	meshList[GEO_OUTERDOOR] = MeshBuilder::GenerateOBJ(L"OBJ//outerdoor.obj");
//	meshList[GEO_INNERDOOR] = MeshBuilder::GenerateOBJ(L"OBJ//innerdoor.obj");
//	meshList[GEO_TRAVELATORSUPPORT] = MeshBuilder::GenerateOBJ(L"OBJ//travelatorsupport.obj");
//	meshList[GEO_TRAVELATORSLOPE] = MeshBuilder::GenerateOBJ(L"OBJ//travelatorslope.obj");
//	meshList[GEO_TRAVELATORHANDLE] = MeshBuilder::GenerateOBJ(L"OBJ//travelatorhandle.obj");
//}
//
//void SceneMainMenu::InnitDraws()
//{
//	drawOrders.resize(NUM_DRAWS + meshList.size() - NUM_GEOMETRY);
//
//	//skybox will be the main draw order that all other draw orders are children of
//	drawOrders[DRAW_MAIN].geometry = NULL;
//	drawOrders[DRAW_MAIN].enableLight = false;
//
//	//positions are offset a little from their proper position because of floating point error
//
//	drawOrders[DRAW_SKYBOX].geometry = meshList[GEO_SKYBOX];
//	drawOrders[DRAW_SKYBOX].transform.translate.Set(0,0,0);
//	drawOrders[DRAW_SKYBOX].transform.scale.Set(10000,10000,10000);
//	drawOrders[DRAW_SKYBOX].material.SetTextureTo(textures[TEXTURE_SKYBOX]);
//	drawOrders[DRAW_SKYBOX].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_SKYBOX].enableLight = false;
//
//	drawOrders[DRAW_GROUND].geometry = meshList[GEO_GROUND];
//	drawOrders[DRAW_GROUND].transform.translate.Set(0,0,0);
//	drawOrders[DRAW_GROUND].material.SetTextureTo(textures[TEXTURE_GROUND]);
//	drawOrders[DRAW_GROUND].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_GROUND].enableLight = false;
//
//	drawOrders[DRAW_PLAYER].geometry = meshList[GEO_CUBE];
//	drawOrders[DRAW_PLAYER].transform.translate.Set(0,0.1,0);
//	drawOrders[DRAW_PLAYER].material.SetTextureTo(textures[TEXTURE_LARGE_FORERUNNER_FLOOR_PLATE]);
//	drawOrders[DRAW_PLAYER].SetTerminalVelocityTo(Vector3(60,60,60));
//	drawOrders[DRAW_PLAYER].staticFriction = 0.03;
//	drawOrders[DRAW_PLAYER].mass = 1;
//	drawOrders[DRAW_PLAYER].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_PLAYER].enableLight = false;
//
//	drawOrders[DRAW_CABINET1].geometry = meshList[GEO_CABINET1];
//	drawOrders[DRAW_CABINET1].transform.translate.Set(10,0.1,0);
//	drawOrders[DRAW_CABINET1].material.SetTextureTo(textures[TEXTURE_CABINET1]);
//	drawOrders[DRAW_CABINET1].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_CABINET1].enableLight = false;
//
//	drawOrders[DRAW_CAN1].geometry = meshList[GEO_CAN1];
//	drawOrders[DRAW_CAN1].transform.translate.Set(15,0.1,0);
//	drawOrders[DRAW_CAN1].material.SetTextureTo(textures[TEXTURE_CAN1]);
//	drawOrders[DRAW_CAN1].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_CAN1].enableLight = false;
//
//	drawOrders[DRAW_CAN2].geometry = meshList[GEO_CAN2];
//	drawOrders[DRAW_CAN2].transform.translate.Set(20,0.1,0);
//	drawOrders[DRAW_CAN2].material.SetTextureTo(textures[TEXTURE_CAN2]);
//	drawOrders[DRAW_CAN2].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_CAN2].enableLight = false;
//
//	drawOrders[DRAW_CAN3].geometry = meshList[GEO_CAN3];
//	drawOrders[DRAW_CAN3].transform.translate.Set(25,0.1,0);
//	drawOrders[DRAW_CAN3].material.SetTextureTo(textures[TEXTURE_CAN3]);
//	drawOrders[DRAW_CAN3].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_CAN3].enableLight = false;
//
//	drawOrders[DRAW_CEREAL1].geometry = meshList[GEO_CEREAL1];
//	drawOrders[DRAW_CEREAL1].transform.translate.Set(30,0.1,0);
//	drawOrders[DRAW_CEREAL1].material.SetTextureTo(textures[TEXTURE_CEREAL1]);
//	drawOrders[DRAW_CEREAL1].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_CEREAL1].enableLight = false;
//
//	drawOrders[DRAW_CEREAL2].geometry = meshList[GEO_CEREAL2];
//	drawOrders[DRAW_CEREAL2].transform.translate.Set(35,0.1,0);
//	drawOrders[DRAW_CEREAL2].material.SetTextureTo(textures[TEXTURE_CEREAL2]);
//	drawOrders[DRAW_CEREAL2].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_CEREAL2].enableLight = false;
//
//	drawOrders[DRAW_CEREAL3].geometry = meshList[GEO_CEREAL3];
//	drawOrders[DRAW_CEREAL3].transform.translate.Set(40,0.1,0);
//	drawOrders[DRAW_CEREAL3].material.SetTextureTo(textures[TEXTURE_CEREAL3]);
//	drawOrders[DRAW_CEREAL3].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_CEREAL3].enableLight = false;
//
//	drawOrders[DRAW_PACKET1].geometry = meshList[GEO_PACKET1];
//	drawOrders[DRAW_PACKET1].transform.translate.Set(45,0.1,0);
//	drawOrders[DRAW_PACKET1].material.SetTextureTo(textures[TEXTURE_PACKET1]);
//	drawOrders[DRAW_PACKET1].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_PACKET1].enableLight = false;
//
//	drawOrders[DRAW_PACKET2].geometry = meshList[GEO_PACKET2];
//	drawOrders[DRAW_PACKET2].transform.translate.Set(50,0.1,0);
//	drawOrders[DRAW_PACKET2].material.SetTextureTo(textures[TEXTURE_PACKET2]);
//	drawOrders[DRAW_PACKET2].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_PACKET2].enableLight = false;
//
//	drawOrders[DRAW_PACKET3].geometry = meshList[GEO_PACKET3];
//	drawOrders[DRAW_PACKET3].transform.translate.Set(55,0.1,0);
//	drawOrders[DRAW_PACKET3].material.SetTextureTo(textures[TEXTURE_PACKET3]);
//	drawOrders[DRAW_PACKET3].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_PACKET3].enableLight = false;
//
//	drawOrders[DRAW_BUILDING].geometry = meshList[GEO_BUILDING];
//	drawOrders[DRAW_BUILDING].transform.translate.Set(0,0.1,-30);
//	drawOrders[DRAW_BUILDING].material.SetTextureTo(textures[TEXTURE_BUILDING]);
//	drawOrders[DRAW_BUILDING].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_BUILDING].enableLight = false;
//
//	drawOrders[DRAW_LIFT].geometry = meshList[GEO_LIFT];
//	drawOrders[DRAW_LIFT].transform.translate.Set(-20,0.1,0);
//	drawOrders[DRAW_LIFT].material.SetTextureTo(textures[TEXTURE_LIFT]);
//	drawOrders[DRAW_LIFT].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_LIFT].enableLight = false;
//
//	drawOrders[DRAW_LIFTDOOR].geometry = meshList[GEO_LIFTDOOR];
//	drawOrders[DRAW_LIFTDOOR].transform.translate.Set(-30,0.1,0);
//	drawOrders[DRAW_LIFTDOOR].material.SetTextureTo(textures[TEXTURE_LIFTDOOR]);
//	drawOrders[DRAW_LIFTDOOR].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_LIFTDOOR].enableLight = false;
//
//	drawOrders[DRAW_OUTERDOOR].geometry = meshList[GEO_OUTERDOOR];
//	drawOrders[DRAW_OUTERDOOR].transform.translate.Set(-40,0.1,0);
//	drawOrders[DRAW_OUTERDOOR].material.SetTextureTo(textures[TEXTURE_OUTERDOOR]);
//	drawOrders[DRAW_OUTERDOOR].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_OUTERDOOR].enableLight = false;
//
//	drawOrders[DRAW_INNERDOOR].geometry = meshList[GEO_INNERDOOR];
//	drawOrders[DRAW_INNERDOOR].transform.translate.Set(-50,0.1,0);
//	drawOrders[DRAW_INNERDOOR].material.SetTextureTo(textures[TEXTURE_INNERDOOR]);
//	drawOrders[DRAW_INNERDOOR].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_INNERDOOR].enableLight = false;
//
//	drawOrders[DRAW_TRAVELATORSUPPORT].geometry = meshList[GEO_TRAVELATORSUPPORT];
//	drawOrders[DRAW_TRAVELATORSUPPORT].transform.translate.Set(-70,0.1,0);
//	drawOrders[DRAW_TRAVELATORSUPPORT].material.SetTextureTo(textures[TEXTURE_TRAVELATORSUPPORT]);
//	drawOrders[DRAW_TRAVELATORSUPPORT].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_TRAVELATORSUPPORT].enableLight = false;
//
//	drawOrders[DRAW_TRAVELATORSLOPE].geometry = meshList[GEO_TRAVELATORSLOPE];
//	drawOrders[DRAW_TRAVELATORSLOPE].transform.translate.Set(-90,0.1,0);
//	drawOrders[DRAW_TRAVELATORSLOPE].material.SetTextureTo(textures[TEXTURE_TRAVELATORSLOPE]);
//	drawOrders[DRAW_TRAVELATORSLOPE].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_TRAVELATORSLOPE].enableLight = false;
//
//	drawOrders[DRAW_TRAVELATORHANDLE].geometry = meshList[GEO_TRAVELATORHANDLE];
//	drawOrders[DRAW_TRAVELATORHANDLE].transform.translate.Set(-110,0.1,0);
//	drawOrders[DRAW_TRAVELATORHANDLE].material.SetTextureTo(textures[TEXTURE_TRAVELATORHANDLE]);
//	drawOrders[DRAW_TRAVELATORHANDLE].SetParentAs(&drawOrders[DRAW_MAIN]);
//	drawOrders[DRAW_TRAVELATORHANDLE].enableLight = false;
//}
//
//void SceneMainMenu::InnitVoxels()
//{
//	drawOrders[DRAW_PLAYER].GenerateVoxels();
//	drawOrders[DRAW_GROUND].GenerateVoxels();
//}
//
//void SceneMainMenu::InnitForces()
//{
//	Vector3 accelerationDueToGravity(0, -50.f, 0);
//	for(std::vector<drawOrder>::iterator draw = drawOrders.begin(); draw != drawOrders.end(); draw++)
//	{
//		//draw->AddForce(accelerationDueToGravity * draw->mass);
//	}
//}
//
//bool SceneMainMenu::Update(const double dt)
//{
//	float rotationspeed = 2;
//	deltaTime = dt;
//	accumulatingDT += deltaTime;
//	frameCounter++;
//	const double undateInterval = 0.2;
//	if(accumulatingDT > undateInterval)
//	{
//		currentFPS = frameCounter / accumulatingDT;
//		accumulatingDT -= undateInterval;
//		frameCounter = 0;
//	}
//	if(keyboard.isKeyPressed(VK_ESCAPE))
//	{
//		return true;
//	}
//
//	DoUserInput();
//	UpdateDraws();
//	UpdateView();
//	UpdateLight();
//	return gameQuit;
//}
//
//void SceneMainMenu::UpdateLogic()
//{
//	if(mainmenu==START)
//	{
//		gameQuit=false;
//	}
//	else if(mainmenu==INST)
//	{
//		gameQuit=false;
//	}
//	else if(mainmenu==CREDITS)
//	{
//		gameQuit=false;
//	}
//	else if(mainmenu==EXIT)
//	{
//		gameQuit=true;
//	}
//	else if(mainmenu==CHOOSETOEXIT)
//	{
//		gameQuit=false;
//	}
//	else if(mainmenu==MAINMENU)
//	{
//		
//		gameQuit=false;
//		if(option==1)
//		{
//			mainmenu=START;
//		}
//		else if(option==2)
//		{
//			mainmenu=INST;
//		}
//		else if(option==3)
//		{
//			mainmenu=CREDITS;
//		}
//		else if(option==4)
//		{
//			mainmenu=CHOOSETOEXIT;
//		}
//	}
//}
//
//void SceneMainMenu::UpdateView()
//{
//	//positions are offset a little from their proper position because of floating point error
//	drawOrders[DRAW_SKYBOX].transform.translate = Vector3(0,0,0) + camera.ReturnPosition();
//
//	if(isFrog == false)
//	{
//		//camera.Translate(drawOrders[DRAW_PLAYER].transform.translate - camera.ReturnPosition() + Vector3(0, 10, 0));
//	}
//	else
//	{
//		//camera.Translate(drawOrders[DRAW_PLAYER].transform.translate - camera.ReturnPosition() + Vector3(0, 3, 0));
//	}
//	float player_rotationY = camera.GetRotation().y - drawOrders[DRAW_PLAYER].transform.rotate.y;
//	float player_current_frame_rotationY = player_rotationY / 25;
//	drawOrders[DRAW_PLAYER].transform.rotate.y += player_current_frame_rotationY;
//	gfx.SetViewAt(camera);
//}
//
//void SceneMainMenu::UpdateLight()
//{
//	gfx.UpdateLights();
//}
//
//void SceneMainMenu::UpdateDraws()
//{
//	//where forces are applied
//	for(std::vector<drawOrder>::iterator draw = drawOrders.begin(); draw != drawOrders.end(); draw++)
//	{
//		//an object has 0 mass if it is infinitely heavy and forces will barely have any effect on it including gravity. This is totally how physics work
//		draw->UpdateVelocity(deltaTime);
//		draw->UpdateForcesTo(deltaTime);
//	}
//
//	//where we do collision
//	//for(std::vector<drawOrder>::iterator draw1 = drawOrders.begin(); draw1 != drawOrders.end(); draw1++)
//	//{
//	//	//check the object with every other object after it. Objects that came before are skipped to prevent checking collision twice with the same object
//	//	for(std::vector<drawOrder>::iterator draw2 = draw1 + 1; draw2 != drawOrders.end(); draw2++)
//	//	{
//	//		if(draw1->velocity.IsZero() && draw2->velocity.IsZero())
//	//		{
//	//			continue;
//	//		}
//	//		bool CollisionIsDone = false;
//
//	//		//check the individual voxel each object has. If one pair collides, collision is applied to the objects as a whole we break out of the loop
//	//		for(std::vector<Voxel>::iterator voxel1 = draw1->voxels.begin(); voxel1 != draw1->voxels.end(); voxel1++)
//	//		{
//	//			for(std::vector<Voxel>::iterator voxel2 = draw2->voxels.begin(); voxel2 != draw2->voxels.end(); voxel2++)
//	//			{
//	//				CollisionIsDone = collisionSystem.CheckThisCollision(&*voxel1, &*voxel2, deltaTime);
//	//			}
//	//		}
//	//	}
//	//}
//	collisionSystem.CheckThisCollision(&drawOrders[DRAW_GROUND],&drawOrders[DRAW_PLAYER],deltaTime);
//	collisionSystem.ResolveAllCollisionsAccordingTo(deltaTime);
//
//	//draws are finally updated after processing
//	for(std::vector<drawOrder>::iterator draw = drawOrders.begin(); draw != drawOrders.end(); draw++)
//	{
//		draw->UpdateTo(deltaTime);
//	}
//}
//
//void SceneMainMenu::Render()
//{
//	//clear depth and color buffer
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	
//	glEnableVertexAttribArray(0); // 1st attribute buffer :vertices
//	glEnableVertexAttribArray(1); // 2nd attribute buffer : colors
//	glEnableVertexAttribArray(2); // 3rd attribute : normals
//	glEnableVertexAttribArray(3); // 4th attribute : UV coordinates
//
//	if(drawVoxels)
//	{
//		Material material;
//		drawOrder draw_cube;
//		draw_cube.geometry = meshList[GEO_CUBE];
//		draw_cube.enableLight = false;
//		draw_cube.material = material;
//		for(std::vector<drawOrder>::iterator draw = drawOrders.begin(); draw != drawOrders.end(); draw++)
//		{
//			//check the individual voxel each object has. If one pair collides, collision is applied to the objects as a whole we break out of the loop
//			for(std::vector<Voxel>::iterator voxel = draw->voxels.begin(); voxel != draw->voxels.end(); voxel++)
//			{
//				Mtx44 translate, scale;
//				translate.SetToTranslation(voxel->GetPosition());
//				scale.SetToScale(Voxel::GetSize(), Voxel::GetSize(), Voxel::GetSize());
//				gfx.RenderMesh(draw_cube, translate * scale);
//			}
//		}
//	}
//	else
//	{
//		drawOrders[DRAW_MAIN].Execute(gfx);
//	}
//
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//	glDisableVertexAttribArray(2);
//	glDisableVertexAttribArray(3);
//}
//
//void SceneMainMenu::Exit()
//{
//	// Cleanup here
//	for(int i = 0; i < NUM_GEOMETRY; ++i)
//	{
//		if(meshList[i] != NULL)
//		{
//			delete meshList[i];
//		}
//	}
//
//	for(std::vector<unsigned>::iterator textureID = textures.begin(); textureID != textures.end(); ++textureID)
//	{
//		if(*textureID > 0)
//		{
//			glDeleteTextures(1, &*textureID);
//		}
//	}
//}
//
//void SceneMainMenu::DoUserInput()
//{
//	double mouseX;
//	double mouseY;
//	mouse.Update(mouseX, mouseY);
//	const int CAMERA_SPEED = 5;
//	camera.Rotate(0, -mouseX, -mouseY);
//	playerAcceleration.SetZero();
//	double movingSpeed = 5;
//
//	if(keyboard.isKeyPressed('1'))
//	{
//		glEnable(GL_CULL_FACE);
//	}
//	if(keyboard.isKeyPressed('2'))
//	{
//		glDisable(GL_CULL_FACE);
//	}
//	if(keyboard.isKeyPressed('3'))
//	{
//		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	}
//	if(keyboard.isKeyPressed('4'))
//	{
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	}
//	if(keyboard.isKeyPressed('5'))
//	{
//		drawVoxels = !drawVoxels;
//	}
//	if (keyboard.isKeyPressed('I'))
//	{
//		if(isFrog == false)
//		{
//			player = new PlayerFrog;
//			isFrog = true;
//		}
//		else
//		{
//			player = new PlayerHuman;
//			isFrog = false;
//		}
//	}
//	if(keyboard.isKeyHold('W') || keyboard.isKeyHold('S') || keyboard.isKeyHold('A') || keyboard.isKeyHold('D'))
//	{
//		if (keyboard.isKeyHold('W'))
//		{
//			playerAcceleration += player->MoveForward(camera, movingSpeed);
//		}
//		if (keyboard.isKeyHold('S'))
//		{
//			playerAcceleration += player->MoveBackward(camera, movingSpeed);
//		}
//		if (keyboard.isKeyHold('A'))
//		{
//			playerAcceleration += player->MoveLeft(camera, movingSpeed);
//		}
//		if (keyboard.isKeyHold('D'))
//		{
//			playerAcceleration += player->MoveRight(camera, movingSpeed);
//		}
//		/*if(isFrog == true && isJumping == false && isFalling == false)
//		{
//			isJumping = true;
//		}*/
//	}
//	//Jump
//	/*if (keyboard.isKeyHold(VK_SPACE) && isJumping == false && isFalling == false && isFrog == false)
//	{
//		isJumping = true;
//	}*/
//	/*
//	if (keyboard.isKeyHold('O'))
//	{	
//		Vector3 tempVector;
//		tempVector.Set(0, 50, 0);
//		playerAcceleration += tempVector;
//	}
//	if (keyboard.isKeyHold('P'))
//	{
//		Vector3 tempVector;
//		tempVector.Set(0, -50, 0);
//		playerAcceleration += tempVector;
//	}
//	*/
//	//Ignore
//	if (keyboard.isKeyHold(VK_UP))
//	{
//		camera.Move(10.0f * deltaTime * CAMERA_SPEED, 0.0f, 0.0f);
//	}
//	if (keyboard.isKeyHold(VK_LEFT))
//	{
//		camera.Move(0.0f, 0.0f, -10.0f * deltaTime * CAMERA_SPEED);
//	}
//	if (keyboard.isKeyHold(VK_DOWN))
//	{
//		camera.Move(-10.0f * deltaTime * CAMERA_SPEED, 0.0f, 0.0f);
//	}
//	if (keyboard.isKeyHold(VK_RIGHT))
//	{
//		camera.Move(0.0f, 0.0f, 10.0f * deltaTime * CAMERA_SPEED);
//	}
//	if (keyboard.isKeyHold(VK_SPACE))
//	{
//		camera.Move(0,10 * deltaTime * CAMERA_SPEED,0);
//	}
//	if (keyboard.isKeyHold(VK_CONTROL))
//	{
//		camera.Move(0,-10 * deltaTime * CAMERA_SPEED,0);
//	}
//
//	//Jump
//	if(isJumping == true)
//	{
//		if(jumpedHeight < 700 && isFalling == false)
//		{
//			Vector3 tempVector;
//			tempVector.Set(0, 100, 0);
//			playerAcceleration += tempVector;
//			jumpedHeight += 100 - 50;
//		}
//		else
//		{
//			isJumping = false;
//			isFalling = true;
//			jumpedHeight = 700;
//		}
//	}
//	if(isFalling == true)
//	{
//		if(jumpedHeight > 0)
//		{
//			jumpedHeight -= 20;
//		}
//		else
//		{
//				isFalling = false;
//			jumpedHeight = 0;
//		}
//	}
//	//playerAcceleration += player->Update(camera);
//	Force playerForce;
//	playerForce.SetLifespanTo(0.0001);
//	playerForce.SetVector(playerAcceleration);
//	drawOrders[DRAW_PLAYER].AddForce(playerForce);
//}