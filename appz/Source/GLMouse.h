#pragma once
#include "GL\glew.h"
#include "GLFW\glfw3.h"
/****************************************************************************/
/*!
\file GLMouse.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class that handles mouse input
*/
/****************************************************************************/

/****************************************************************************/
/*!
Class GLMouse:
\brief
handles mouse input
*/
/****************************************************************************/
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

