#include "stdafx.h"
#include "Window.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace
{
	const glm::vec4 WHITE_BACKGROUND = { 1.0f, 1.0f, 1.0f, 1.0f };

	//шкала
	void DrawSegmentation( float xCenter, float yCenter) 
	{
		// TODO: use camel case
		float lengthX = xCenter / 10;
		float beginDivisionX = xCenter -10 * lengthX;

		float lengthY = yCenter / 10;
		float beginDivisionY = yCenter - 10 * lengthY;

		glBegin(GL_LINES);
		for (int i = 0; i <= 20; i++)
		{
			glVertex2f(lengthX * i + beginDivisionX, yCenter - 5);
			glVertex2f(lengthX * i + beginDivisionX, yCenter + 5);
			glVertex2f(xCenter - 5, lengthY * i + beginDivisionY);
			glVertex2f(xCenter + 5, lengthY * i + beginDivisionY);
		}
		glEnd();
	}


	void DrawCoordinateSystem(const glm::ivec2 & size)
	{
		glBegin(GL_LINES);
		glVertex2f(0.0f, size.y / 2.0f);
		glVertex2f(float(size.x), size.y / 2.0f);

		glVertex2f(size.x / 2.0f, 0.0f);
		glVertex2f(size.x / 2.0f, float(size.y));

		glEnd();
	}

	void DrawArrows(const glm::ivec2 & size) 
	{
		// TODO: move comments above code lines
		glBegin(GL_LINES);

		//левая вертикльная
		glVertex2f(size.x / 2.0f, 0.0f ); 
		glVertex2f(size.x / 2.0f - 6.0f, 20.0f);

		//правая вертикльная
		glVertex2f(size.x / 2.0f, 0.0f); 
		glVertex2f(size.x / 2.0f + 6.0f, 20.0f);

		//нижняя горизонтальная
		glVertex2f(float(size.x), size.y / 2.0f); 
		glVertex2f(size.x - 20.0f, size.y / 2.0f + 6.0f);

		//верхняя горизонтальная
		glVertex2f(float(size.x), size.y / 2.0f);
		glVertex2f(size.x - 20.0f, size.y / 2.0f - 6.0f);

		glEnd();
	}
	

	void DrawParabola(float xCenter, float yCenter) 
	{
		float lengthx = xCenter / 10;
		glBegin(GL_LINE_STRIP);
		for (float i = -2 * lengthx;  i < 3 * lengthx; i += 0.1) 
		{
			float y = - (2 * i * i - 3 * i - 8) * 0.01;
			glVertex2f(i + xCenter,y+ yCenter);
		}
		glEnd();
	}
}

CWindow::CWindow()
{
	SetBackgroundColor(WHITE_BACKGROUND);
}

void CWindow::OnWindowEvent(const SDL_Event & event)
{
	(void)event;
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
	(void)deltaSeconds;
}

void CWindow::OnDrawWindow(const glm::ivec2 & size)
{
	glColor3f(0.5, 0.5, 0.5);
	DrawSegmentation(size.x / 2, size.y / 2);

	SetupView(size);
	glColor3f(0, 0, 0);
	DrawCoordinateSystem(size);

	glColor3f(0, 0, 0);
	DrawArrows(size);

	glColor3f(1, 0, 0);
	DrawParabola(size.x / 2, size.y / 2);
}

void CWindow::SetupView(const glm::ivec2 & size)
{
	// Матрица ортографического проецирования изображения в трёхмерном пространстве
	// из параллелипипеда с размером, равным (size.X x size.Y x 2).
	const glm::mat4 matrix = glm::ortho<float>(0, float(size.x), float(size.y), 0);
	glViewport(0, 0, size.x, size.y);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(matrix));
	glMatrixMode(GL_MODELVIEW);
}