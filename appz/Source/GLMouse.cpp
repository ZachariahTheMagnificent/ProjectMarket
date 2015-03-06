#include "GLMouse.h"
/****************************************************************************/
/*!
\file GLMouse.cpp
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class that handles mouse input
*/
/****************************************************************************/

/****************************************************************************/
/*!
\brief
Default constructor
*/
/****************************************************************************/
GLMouse::GLMouse()
{
}
/****************************************************************************/
/*!
\brief
Constructor that specifies the current window
\param m_window
		gives the GLMouse object our current window
*/
/****************************************************************************/
GLMouse::GLMouse(GLFWwindow* m_window)
{
	InitWindow(m_window);
}
/****************************************************************************/
/*!
\brief
Initializes the GLMouse object to our current window
*/
/****************************************************************************/
void GLMouse::InitWindow(GLFWwindow* window)
{
	m_window = window;
	UpdateScreenSize();
	SetToCentre();
}
/****************************************************************************/
/*!
\brief
Default destructor
*/
/****************************************************************************/
GLMouse::~GLMouse()
{
}
/****************************************************************************/
/*!
\brief
returns the current mouse displacement from the centre then locks it to the centre
\param destX
		a reference to a variable where we store the X displacement
\param destY
		a reference to a variable where we store the Y displacement
*/
/****************************************************************************/
void GLMouse::Update(double& destX, double& destY)
{
	double mouseX;
	double mouseY;

	GetPosition(&mouseX, &mouseY);
	destX = mouseX - screenX/2;
	destY = mouseY - screenY/2;

	SetToCentre();
}
/****************************************************************************/
/*!
\brief
Updates the GLMouse to the current screen size
*/
/****************************************************************************/
void GLMouse::UpdateScreenSize()
{
	glfwGetWindowSize(m_window, &screenX, &screenY);
}
/****************************************************************************/
/*!
\brief
Gets the raw position of the mouse in the window
\param destX
		a pointer to the variable where we store the X position
\param destY
		a pointer to the variable where we store the Y position
*/
/****************************************************************************/
void GLMouse::GetPosition(double* destX, double* destY)
{
	glfwGetCursorPos(m_window, destX, destY);
}
/****************************************************************************/
/*!
\brief
Sets the mouse to the centre of the screen
*/
/****************************************************************************/
void GLMouse::SetToCentre()
{
	glfwSetCursorPos(m_window, screenX/2, screenY/2);	
}