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
	textures.resize(NUM_TEXTURES, 0);
	textures[TEXTURE_SKYBOX] = LoadTGA(L"Image//skybox.tga");
	textures[TEXTURE_GROUND] = LoadTGA(L"Image//ground.tga");
	textures[TEXTURE_LARGE_FORERUNNER_FLOOR_PLATE] = LoadTGA(L"Image//large_forerunner_floor_plate.tga");
}

void SceneMain::InnitLight()
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

void SceneMain::InnitGeometry()
{
	//Initialize all meshes to NULL
	meshList.resize(NUM_GEOMETRY, NULL);

	meshList[GEO_SKYBOX] = MeshBuilder::GenerateOBJ(L"OBJ//skybox.obj");
	meshList[GEO_GROUND] = MeshBuilder::GenerateRepeatQuad(L"ground", Color(1, 1, 1), 4.f, 4.f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube(L"Cube",Color(),1,1,1);
}

void SceneMain::InnitDraws()
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
}

void SceneMain::InnitVoxels()
{
	drawOrders[DRAW_PLAYER].GenerateVoxels();

	//voxel for football field
	drawOrders[DRAW_GROUND].GenerateVoxels();
}

void SceneMain::InnitForces()
{
	Vector3 accelerationDueToGravity(0, -50.f, 0);
	for(std::vector<drawOrder>::iterator draw = drawOrders.begin(); draw != drawOrders.end(); draw++)
	{
		//draw->AddForce(accelerationDueToGravity * draw->mass);
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
	drawOrders[DRAW_SKYBOX].transform.translate = Vector3(0,0,0) + camera.ReturnPosition();

	if(isFrog == false)
	{
		camera.Translate(drawOrders[DRAW_PLAYER].transform.translate - camera.ReturnPosition() + Vector3(0, 10, 0));
	}
	else
	{
		camera.Translate(drawOrders[DRAW_PLAYER].transform.translate - camera.ReturnPosition() + Vector3(0, 3, 0));
	}
	float player_rotationY = camera.GetRotation().y - drawOrders[DRAW_PLAYER].transform.rotate.y;
	float player_current_frame_rotationY = player_rotationY / 25;
	drawOrders[DRAW_PLAYER].transform.rotate.y += player_current_frame_rotationY;
	gfx.SetViewAt(camera);
}

void SceneMain::UpdateLight()
{
	gfx.UpdateLights();
}

void SceneMain::UpdateDraws()
{
	//where forces are applied
	for(std::vector<drawOrder>::iterator draw = drawOrders.begin(); draw != drawOrders.end(); draw++)
	{
		//an object has 0 mass if it is infinitely heavy and forces will barely have any effect on it including gravity. This is totally how physics work
		draw->UpdateVelocity(deltaTime);
		draw->UpdateForcesTo(deltaTime);
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

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

void SceneMain::Exit()
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

void SceneMain::DoUserInput()
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
	if (keyboard.isKeyHold('I'))
	{
		player = new PlayerFrog;
		isFrog = true;
	}
	if (keyboard.isKeyHold('U'))
	{
		player = new PlayerHuman;
		isFrog = false;
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
	//if (keyboard.isKeyHold('W'))
	//{
	//	camera.Move(10.0f * deltaTime * CAMERA_SPEED, 0.0f, 0.0f);
	//}
	//if (keyboard.isKeyHold('A'))
	//{
	//	camera.Move(0.0f, 0.0f, -10.0f * deltaTime * CAMERA_SPEED);
	//}
	//if (keyboard.isKeyHold('S'))
	//{
	//	camera.Move(-10.0f * deltaTime * CAMERA_SPEED, 0.0f, 0.0f);
	//}
	//if (keyboard.isKeyHold('D'))
	//{
	//	camera.Move(0.0f, 0.0f, 10.0f * deltaTime * CAMERA_SPEED);
	//}
	//if (keyboard.isKeyHold(VK_SPACE))
	//{
	//	camera.Move(0,10 * deltaTime * CAMERA_SPEED,0);
	//}
	//if (keyboard.isKeyHold(VK_CONTROL))
	//{
	//	camera.Move(0,-10 * deltaTime * CAMERA_SPEED,0);
	//}

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