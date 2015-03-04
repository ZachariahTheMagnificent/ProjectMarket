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
	InnitMaterials();
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
	snd.loadWave("assistance", "sound//assistance.wav");
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
	globals.AddTexture(L"skybox", L"Image//skybox.tga");
	globals.AddTexture(L"didact", L"Image//didact.tga");
	globals.AddTexture(L"door", L"Image//door.tga");
	globals.AddTexture(L"electronic_circuit", L"Image//electronic_circuit.tga");
	globals.AddTexture(L"football_field", L"Image//football_field.tga");
	globals.AddTexture(L"kitten_bri", L"Image//kitten_bri.tga");
	globals.AddTexture(L"large_forerunner_floor_plate", L"Image//large_forerunner_floor_plate.tga");
	globals.AddTexture(L"metalplatefloorfull", L"Image//metalplatefloorfull.tga");
	globals.AddTexture(L"metal_tile", L"Image//metal_tile.tga");
	globals.AddTexture(L"plate_metal", L"Image//plate_metal.tga");
	globals.AddTexture(L"ring", L"Image//ring.tga");
}

void ScenePhysics::InnitMaterials()
{
	globals.AddMaterial(Material(L"skybox",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"skybox")));
	globals.AddMaterial(Material(L"didact",Component(1,1,1),Component(1,1,1),Component(1,1,1),200,globals.GetTexture(L"didact")));
	globals.AddMaterial(Material(L"stone",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"door")));
	globals.AddMaterial(Material(L"corrupted",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"electronic_circuit")));
	globals.AddMaterial(Material(L"football field",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"football_field")));
	globals.AddMaterial(Material(L"kittenbri",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"kitten_bri")));
	globals.AddMaterial(Material(L"forerunner plate",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"large_forerunner_floor_plate")));
	globals.AddMaterial(Material(L"metal floor",Component(1,1,1),Component(1,1,1),Component(1,1,1),200,globals.GetTexture(L"metalplatefloorfull")));
	globals.AddMaterial(Material(L"metal tile",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"metal_tile")));
	globals.AddMaterial(Material(L"plate metal",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"plate_metal")));
	globals.AddMaterial(Material(L"rock",Component(1,1,1),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"ring")));
}

void ScenePhysics::InnitLight()
{
	light[1].type = Light::LIGHT_DIRECTIONAL;
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
	
	light[2].type = Light::LIGHT_SPOT;
	light[2].position.Set(20, 2000, 20);
	light[2].color.Set(1, 1, 1);
	light[2].power = 1;
	light[2].kC = 1.f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(140));
	light[2].cosInner = cos(Math::DegreeToRadian(30));
	light[2].exponent = 1.f;
	light[2].spotDirection.Set(0.f, -1.f, 0.f);
	
	gfx.AddLight(&light[1]);
	gfx.AddLight(&light[2]);
}

void ScenePhysics::InnitGeometry()
{
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"skybox", L"OBJ//skybox.obj"));

	globals.AddMesh(MeshBuilder::GenerateCube(L"Cube", Color(), 1, 1, 1));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"sentinel" ,L"OBJ//sentinel.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"lift", L"OBJ//lift.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"nirvana", L"OBJ//Nirvana.obj"));
	globals.AddMesh(MeshBuilder::GenerateQuad(L"ground", Color(), 100, 100));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"football field", L"OBJ//football field.obj"));
	
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"didact", L"OBJ//didact.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"door", L"OBJ//door.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"ring", L"OBJ//ring.obj"));
}

void ScenePhysics::InnitDraws()
{
	
	//main will be the main draw order that all other draw orders are children of
	globals.AddDraw(drawOrder(L"main"));

	globals.AddDraw(drawOrder(L"skybox", globals.GetMesh(L"skybox"), &globals.GetMaterial(L"skybox"), &globals.GetDraw(L"main"), false));
	globals.GetDraw(L"skybox").transform.scale.Set(10000,10000,10000);

	globals.AddDraw(drawOrder(L"player", globals.GetMesh(L"sentinel"), &globals.GetMaterial(L"forerunner plate"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"player").transform.translate.Set(21.7, 1, 68.3);
	globals.GetDraw(L"player").SetTerminalVelocityTo(Vector3(60,60,60));
	globals.GetDraw(L"player").SetMassTo(0.5);
	globals.GetDraw(L"player").SetFrictionTo(0.1,0);
	
	globals.AddDraw(drawOrder(L"left lift", globals.GetMesh(L"lift"), &globals.GetMaterial(L"forerunner plate"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"left lift").transform.translate.Set(0, 100, 0);
	globals.GetDraw(L"left lift").SetTerminalVelocityTo(Vector3(60,60,60));
	globals.GetDraw(L"left lift").SetMassTo(100);
	
	globals.AddDraw(drawOrder(L"nirvana", globals.GetMesh(L"nirvana"), &globals.GetMaterial(L"metal floor"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"nirvana").SetTerminalVelocityTo(Vector3(60,60,60));
	globals.GetDraw(L"nirvana").SetFrictionTo(0, 0.5);
	
	globals.AddDraw(drawOrder(L"football field", globals.GetMesh(L"football field"), &globals.GetMaterial(L"football field"), &globals.GetDraw(L"nirvana"), true));
	globals.GetDraw(L"football field").SetTerminalVelocityTo(Vector3(60,60,60));
	
	globals.AddDraw(drawOrder(L"summoning place", globals.GetMesh(L"ring"), &globals.GetMaterial(L"rock"), &globals.GetDraw(L"main"), false));
	globals.GetDraw(L"summoning place").transform.translate.Set(-1000,0,0);
	globals.GetDraw(L"summoning place").SetTerminalVelocityTo(Vector3(60,60,60));
	
	globals.AddDraw(drawOrder(L"currupted sentinel", globals.GetMesh(L"sentinel"), &globals.GetMaterial(L"corrupted"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"currupted sentinel").transform.translate.Set(-23.3,3.7,69.9);
	
	globals.AddDraw(drawOrder(L"rock sentinel", globals.GetMesh(L"sentinel"), &globals.GetMaterial(L"rock"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"rock sentinel").transform.translate.Set(-1000,0,0);
	
	globals.AddDraw(drawOrder(L"stone sentinel", globals.GetMesh(L"sentinel"), &globals.GetMaterial(L"stone"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"stone sentinel").transform.translate.Set(-1000,0,0);
	
	globals.AddDraw(drawOrder(L"wise sentinel", globals.GetMesh(L"sentinel"), &globals.GetMaterial(L"plate metal"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"wise sentinel").transform.translate.Set(-1000,0,0);
	
	globals.AddDraw(drawOrder(L"sneaky sentinel", globals.GetMesh(L"sentinel"), &globals.GetMaterial(L"forerunner plate"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"sneaky sentinel").transform.translate.Set(-1000,0,0);
	
	globals.AddDraw(drawOrder(L"pure sentinel", globals.GetMesh(L"sentinel"), &globals.GetMaterial(L"plate metal"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"pure sentinel").transform.translate.Set(-23.2, 4.25, -69.8);
}

void ScenePhysics::InnitVoxels()
{
	//for(std::map<std::wstring, drawOrder*>::iterator draw = globals.GetDrawList().begin(); draw != globals.GetDrawList().end(); ++draw)
	//{
	//	draw->second->GenerateVoxels();
	//}
	globals.GetDraw(L"nirvana").GenerateVoxels();
	globals.GetDraw(L"player").GenerateVoxels();
}

void ScenePhysics::InnitForces()
{
	//Vector3 accelerationDueToGravity(0, -.8f, 0);
	Vector3 accelerationDueToGravity(0, -9.8f, 0);
	//Vector3 accelerationDueToGravity(0, 0, 0);
	for(std::map<std::wstring, drawOrder*>::iterator draw = globals.GetDrawList().begin(), end = globals.GetDrawList().end(); draw != end; ++draw)
	{
		//draw->second->AddForce(accelerationDueToGravity * draw->second->GetMass());
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
		globals.GetDraw(L"summoning place").geometry = globals.GetMesh(L"ring");
		globals.GetDraw(L"summoning place").transform.rotate.y = 0;
	}
	else
	{
		globals.GetDraw(L"summoning place").transform.rotate.y += rotationspeed * deltaTime;
	}
	DoUserInput();
	UpdateLogic();
	UpdateDraws();
	UpdateView();
	UpdateLight();
	return false;
}

void ScenePhysics::UpdateLogic()
{
	Vector3 playerPosition = globals.GetDraw(L"player").GetTranslationMatrix() * Vector3(0,0,0);
	Range<int> rangeX(-10000,0);
	Range<int> rangeY(-30,30);
	Range<int> rangeZ(-4,4);
	if(rangeX.IsInRange(playerPosition.x) && rangeY.IsInRange(playerPosition.y) && rangeZ.IsInRange(playerPosition.z))
	{
		if(globals.GetDraw(L"summoning place").geometry == globals.GetMesh(L"ring"))
		{
			snd.playSound("assistance");
		}

		globals.GetDraw(L"summoning place").geometry = globals.GetMesh(L"didact");
		globals.GetDraw(L"summoning place").material = &globals.GetMaterial(L"didact");
		globals.GetDraw(L"summoning place").transform.rotate.y = 0;
		globals.GetDraw(L"rock sentinel").transform.translate.Set(-17.2, 5.25, -6.6);
		globals.GetDraw(L"stone sentinel").transform.translate.Set(-17.2, 5.25, 6.6);
	}
	else
	{
		globals.GetDraw(L"summoning place").geometry = globals.GetMesh(L"ring");
		globals.GetDraw(L"summoning place").material = &globals.GetMaterial(L"rock");
		globals.GetDraw(L"rock sentinel").transform.translate.Set(-1000,0,0);
		globals.GetDraw(L"stone sentinel").transform.translate.Set(-1000,0,0);
	}
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
	globals.GetDraw(L"skybox").transform.translate = camera.ReturnPosition();

	camera.Translate(globals.GetDraw(L"player").transform.translate - camera.ReturnPosition() + Vector3(0, 4, 0));
	float player_rotationY = camera.GetRotation().y - globals.GetDraw(L"player").transform.rotate.y;
	float player_current_frame_rotationY = player_rotationY / 25;
	globals.GetDraw(L"player").transform.rotate.y += player_current_frame_rotationY;
	gfx.SetViewAt(camera);
}

void ScenePhysics::UpdateLight()
{
	gfx.UpdateLights();

}

void ScenePhysics::UpdateDraws()
{
	//where forces are applied
	for(std::map<std::wstring, drawOrder*>::iterator draw = globals.GetDrawList().begin(), end = globals.GetDrawList().end(); draw != end; ++draw)
	{
		//an object has 0 mass if it is infinitely heavy and forces will barely have any effect on it including gravity. This is totally how physics work
		draw->second->UpdateVelocity(deltaTime);
		draw->second->UpdateForcesTo(deltaTime);
	}

	//where we do collision

	//draws are finally updated after processing
	for(std::map<std::wstring, drawOrder*>::iterator draw = globals.GetDrawList().begin(), end = globals.GetDrawList().end(); draw != end; ++draw)
	{
		draw->second->UpdateTo(deltaTime);
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

	char buffer1[126];
	char buffer2[126];
	Vector3 position = globals.GetDraw(L"player").GetTranslationMatrix() * Vector3(0,0,0);
	sprintf(buffer1,"fps:%.3f",1.0/deltaTime);
	sprintf(buffer2,"position:%.3f, %.3f, %.3f",position.x, position.y, position.z);

	//if(drawVoxels)
	//{
	//	Material material(L"meep", Component(1,1,1), Component(1,1,1), Component(1,1,1),20,globals.GetTexture(L"building"));
	//	drawOrder draw_cube(L"cube", globals.GetMesh(L"Cube"), &material, NULL, true);
	//	for(std::map<std::wstring, drawOrder*>::iterator draw = globals.GetDrawList().begin(); draw != globals.GetDrawList().end(); ++draw)
	//	{
	//		Mtx44 matrix(draw->second->GetMatrix());
	//		for(std::vector<Voxel>::iterator voxel = draw->second->voxels.begin(); voxel != draw->second->voxels.end(); voxel++)
	//		{
	//			voxel->ApplyToMatrix(matrix);
	//			Mtx44 translate;
	//			translate.SetToTranslation(voxel->GetPosition());
	//			gfx.RenderMesh(draw_cube, translate);
	//		}
	//	}
	//}
	//else
	//{
		globals.GetDraw(L"main").Execute(gfx);
	//}
	gfx.RenderTextOnScreen(buffer1,Color(1,0,0),30,30,650);
	gfx.RenderTextOnScreen(buffer2,Color(1,0,0),30,30,600);
	MS matrixStack;
	matrixStack.Translate(200,100,0);
	matrixStack.Scale(50,50,50);
	matrixStack.MultMatrix(globals.GetDraw(L"player").GetRotationMatrix());
	gfx.RenderMeshOnScreen(globals.GetDraw(L"player"), matrixStack.Top());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

void ScenePhysics::Exit()
{
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
		tempVector.Set(0, 5000, 0);
		playerAcceleration += tempVector;
	}
	if (keyboard.isKeyHold('P'))
	{
		Vector3 tempVector;
		tempVector.Set(0, -5000, 0);
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
	Force playerForce;
	playerForce.SetLifespanTo(0.0001);
	playerForce.SetVector(playerAcceleration);
	globals.GetDraw(L"player").AddForce(playerForce);
}