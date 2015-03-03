#include "Application.h"

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "Keyboard.h"
#include "GLMouse.h"

#include "SceneMain.h"
#include "SceneMainMenu.h"
#include "ScenePhysics.h"
#include "Sound.h"
#include "Graphics.h"

GLFWwindow* m_window;
GLMouse mouse;
Keyboard keyboard;
Sound snd;
Graphics gfx;
const unsigned char FPS = 60;
const unsigned int frameTime = 1000 / FPS;
const unsigned screenX = 700;
const unsigned screenY = 500;

static void error_callback(const int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

static void key_callback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void resize_callback(GLFWwindow* window, const int w, const int h)
{
	glViewport(0, 0, w, h); //update opengl the new window size
}

Application::Application()
{
}

Application::~Application()
{
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(screenX, screenY, "Computer Graphics", NULL, NULL);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
	glfwSetWindowSizeCallback(m_window, resize_callback);

	mouse.InitWindow(m_window);
	gfx.Init(m_window);
	ShowCursor(FALSE);
}

void Application::Run()
{
	//Main Loop
	bool gameQuit = false;
	Scene* pScene = new SceneMain(keyboard, mouse, snd, gfx);
	pScene->Init();
	pScene->SetWindowSize(screenX, screenY);
	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !gameQuit)
	{
		keyboard.updateinput();
		gameQuit = pScene->Update(m_timer.getElapsedTime());
		pScene->Render();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
	pScene->Exit();
	delete pScene;
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
