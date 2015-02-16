#pragma once
#include "GL\glew.h"
#include "GLFW\glfw3.h"

class GLMouse
{
public:
	GLMouse();
	GLMouse(GLFWwindow* m_window);
	~GLMouse();
	void InitWindow(GLFWwindow* window);
	void Update(double& destX, double& destY);
	void UpdateScreenSize();
	void GetPosition(double* destX, double* destY);
	void SetToCentre();
private:
	GLFWwindow* m_window;
	int screenX;
	int screenY;
};

