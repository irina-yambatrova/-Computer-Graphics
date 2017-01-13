#include "stdafx.h"
#include "Window.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
/*
GL_POINTS	 Рисование точек
GL_LINES	 Рисование линий по 2 точкам
GL_LINE_LOOP	 Рисование нескольких связанных линий 1 и последняя точка связываются в линию
GL_LINE_STRIP	 Рисование нескольких связанных линий
GL_TRIANGLES	 Рисование треугольников по 3 точкам
GL_TRIANGLE_STRIP	 Рисование нескольких связанных треугольников
GL_TRIANGLE_FAN	Первый соединяется с последним
GL_QUADS	 Рисование квадратов по 4 точкам
GL_QUAD_STRIP	 Рисование связанных квадратов
GL_POLYGON	 Рисование полигонов от 3 точек.
*/
namespace
{

	// Рисуем контур эллипса
	void StrokeEllipse(float xCenter, float yCenter, float rx, float ry, int pointCount = 360)
	{
		const float step = float(2 * M_PI / pointCount);

		// Эллипс представлен в виде незамкнутой ломаной линии, соединяющей
		// pointCount точек на его границе с шагом 2*PI/pointCount
		glBegin(GL_LINE_STRIP);
		for (float angle = 0; angle < float(2 * M_PI); angle += step)
		{
			const float dx = rx * cosf(angle);
			const float dy = ry * sinf(angle);
			glVertex2f(dx + xCenter, dy + yCenter);
		}
		glEnd();
	}

	// Рисуем закрашенный эллипс
	void FillEllipse(float xCenter, float yCenter, int rx, int ry, int pointCount = 360)
	{
		const float step = float(2 * M_PI) / pointCount;

		// Эллипс представлет в виде "веера" из треугольников
		glBegin(GL_TRIANGLE_FAN);
		// Начальная точка веера располагается в центре эллипса
		glVertex2f(xCenter, yCenter);
		// Остальные точки - равномерно по его границе
		for (float angle = 0; angle <= float(2 * M_PI); angle += step)
		{
			float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
			const float dx = rx * cosf(a);
			const float dy = ry * sinf(a);
			glVertex2f(dx + xCenter, dy + yCenter);
		}
		glEnd();
	}
	//оправа очков
	void FillLinesRight(float xCenter, float yCenter)
	{
		glBegin(GL_LINES);

		glVertex2f(xCenter - 56, yCenter - 40 );
		glVertex2f(xCenter - 68, yCenter - 64);

		glEnd();
	}
	//оправа очков
	void FillLinesLeft(float xCenter, float yCenter)
	{
		glBegin(GL_LINES);

		glVertex2f(xCenter + 56, yCenter - 40);
		glVertex2f(xCenter + 68, yCenter - 64);

		glEnd();
	}
	//рисуем линию носа
	void FillLinesNose(float xCenter, float yCenter)
	{
		glBegin(GL_LINES);

		glVertex2f(xCenter , yCenter + 5);
		glVertex2f(xCenter, yCenter + 25);

		glEnd();
	}
	//рисуем иголки ежика
	void DrawNeedles(float xCenter, float yCenter)
	{
		glBegin(GL_POLYGON);
			glVertex2f(xCenter - 90, yCenter);
			glVertex2f(xCenter - 120, yCenter - 60);
			glVertex2f(xCenter - 80, yCenter - 80);
			glVertex2f(xCenter - 70, yCenter - 120);
			glVertex2f(xCenter - 30, yCenter - 100);

			glVertex2f(xCenter , yCenter - 140);

			glVertex2f(xCenter + 30, yCenter - 100);
			glVertex2f(xCenter + 70, yCenter - 120);
			glVertex2f(xCenter + 80, yCenter - 80);
			glVertex2f(xCenter + 120, yCenter - 60);
			glVertex2f(xCenter + 90, yCenter );
		glEnd();
	}

	//рисуем губы
	void DrawLips(float xCenter, float yCenter)
	{
		glBegin(GL_POLYGON);
		
		glVertex2f(xCenter - 22, yCenter + 30);
		glVertex2f(xCenter, yCenter + 36);
		glVertex2f(xCenter + 22, yCenter + 30);
		glVertex2f(xCenter, yCenter + 44);
		
		glEnd();
	}
}

CWindow::CWindow()
{
	SetBackgroundColor({ 0.f, 0.2f, 0.2f, 1.f });

}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
	m_time += deltaSeconds;
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{

	SetupView(size);

	// Рисуем левую руку
	glColor3f(0.85f, 0.325f, 0.49f);
	FillEllipse(size.x / 2.f + 78, size.y / 2.f + 56, 10, 20);

	// Рисуем правую руку
	glColor3f(0.85f, 0.325f, 0.49f);
	FillEllipse(size.x / 2.f - 78, size.y / 2.f + 56, 10, 20);

	// Рисуем правую ногу
	glColor3f(0.85f, 0.325f, 0.49f);
	FillEllipse(size.x / 2.f + 18, size.y / 2.f + 120, 18, 14);
	FillEllipse(size.x / 2.f + 16, size.y / 2.f + 108, 10, 18);

	// Рисуем левую ногу
	glColor3f(0.85f, 0.325f, 0.49f);
	FillEllipse(size.x / 2.f - 18, size.y / 2.f + 120, 18, 14);
	FillEllipse(size.x / 2.f - 16, size.y / 2.f + 108, 10, 18);

	// Рисуем иголки смешарика
	glColor3f(0.4078f, 0.2862f, 0.5529f);
	DrawNeedles(size.x / 2.f, size.y / 2.f);

	// Рисуем основную часть
	glColor3f(0.85f, 0.325f, 0.49f);
	FillEllipse(size.x / 2.f, size.y / 2.f, 92, 90);

	//обводка основной части
	glColor3f(0.7f, 0.2f, 0.4f);
	glLineWidth(5);
	StrokeEllipse(size.x / 2.f, size.y / 2.f, 90, 90);

	//рисуем левый глаз
	glColor3f(1, 1, 1);
	FillEllipse(size.x / 2.f - 30, size.y / 2.f - 25, 25, 25);

	//рисуем зрачки левого глаза
	glColor3f(0, 0, 0);
	FillEllipse(size.x / 2.f - 15, size.y / 2.f - 25, 8, 10);
	glColor3f(1, 1, 1);
	FillEllipse(size.x / 2.f - 10, size.y / 2.f - 28, 2, 4);

	//рисуем правый глаз
	glColor3f(1, 1, 1);
	FillEllipse(size.x / 2.f + 30, size.y / 2.f - 25, 25, 25);

	//рисуем зрачки правого глаза
	glColor3f(0, 0, 0);
	FillEllipse(size.x / 2.f + 15, size.y / 2.f - 25, 8, 10);
	glColor3f(1, 1, 1);
	FillEllipse(size.x / 2.f + 20, size.y / 2.f - 29, 2, 4);

	//рисуем очки (левый глаз)
	glColor3f(0.3f, 0.2f, 0.4f);
	glLineWidth(9);
	StrokeEllipse(size.x / 2.f - 30, size.y / 2.f - 25, 28, 27);
	FillLinesRight(size.x / 2.f, size.y / 2.f);

	//рисуем очки (правый глаз)
	glColor3f(0.3f, 0.2f, 0.4f);
	glLineWidth(9);
	StrokeEllipse(size.x / 2.f + 30, size.y / 2.f - 25, 28, 27);
	FillLinesLeft(size.x / 2.f, size.y / 2.f);

	//рисуем нос
	glColor3f(0.6f, 0.2f, 0.3f);
	glLineWidth(5);
	FillLinesNose(size.x / 2.f, size.y / 2.f);
	FillEllipse(size.x / 2.f, size.y / 2.f + 5, 13, 6);

	//рисуем рот
	glColor3f(0.3f, 0.2f, 0.5f);
	DrawLips(size.x / 2.f, size.y / 2.f);
}

void CWindow::SetupView(const glm::ivec2 &size)
{
	// Матрица ортографического проецирования изображения в трёхмерном пространстве
	// из параллелипипеда с размером, равным (size.X x size.Y x 2).
	const glm::mat4 matrix = glm::ortho<float>(0, float(size.x), float(size.y), 0);
	glViewport(0, 0, size.x, size.y);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(matrix));
	glMatrixMode(GL_MODELVIEW);
}


