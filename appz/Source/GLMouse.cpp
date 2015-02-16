#include "GLMouse.h"

GLMouse::GLMouse()
{
}

GLMouse::GLMouse(GLFWwindow* m_window)
{
	InitWindow(m_window);
}

void GLMouse::InitWindow(GLFWwindow* window)
{
	m_window = window;
	UpdateScreenSize();
	SetToCentre();
}

GLMouse::~GLMouse()
{
}

void GLMouse::Update(double& destX, double& destY)
{
	double mouseX;
	double mouseY;

	GetPosition(&mouseX, &mouseY);
	destX = mouseX - screenX/2;
	destY = mouseY - screenY/2;

	SetToCentre();
}

void GLMouse::UpdateScreenSize()
{
	glfwGetWindowSize(m_window, &screenX, &screenY);
}

void GLMouse::GetPosition(double* destX, double* destY)
{
	glfwGetCursorPos(m_window, destX, destY);
}

void GLMouse::SetToCentre()
{
	glfwSetCursorPos(m_window, screenX/2, screenY/2);	
}