#include "stdafx.h"
#include "Window.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
/*
GL_POINTS	 ��������� �����
GL_LINES	 ��������� ����� �� 2 ������
GL_LINE_LOOP	 ��������� ���������� ��������� ����� 1 � ��������� ����� ����������� � �����
GL_LINE_STRIP	 ��������� ���������� ��������� �����
GL_TRIANGLES	 ��������� ������������� �� 3 ������
GL_TRIANGLE_STRIP	 ��������� ���������� ��������� �������������
GL_TRIANGLE_FAN	������ ����������� � ���������
GL_QUADS	 ��������� ��������� �� 4 ������
GL_QUAD_STRIP	 ��������� ��������� ���������
GL_POLYGON	 ��������� ��������� �� 3 �����.
*/
namespace
{

	// ������ ������ �������
	void StrokeEllipse(float xCenter, float yCenter, float rx, float ry, int pointCount = 360)
	{
		const float step = float(2 * M_PI / pointCount);

		// ������ ����������� � ���� ����������� ������� �����, �����������
		// pointCount ����� �� ��� ������� � ����� 2*PI/pointCount
		glBegin(GL_LINE_STRIP);
		for (float angle = 0; angle < float(2 * M_PI); angle += step)
		{
			const float dx = rx * cosf(angle);
			const float dy = ry * sinf(angle);
			glVertex2f(dx + xCenter, dy + yCenter);
		}
		glEnd();
	}

	// ������ ����������� ������
	void FillEllipse(float xCenter, float yCenter, int rx, int ry, int pointCount = 360)
	{
		const float step = float(2 * M_PI) / pointCount;

		// ������ ����������� � ���� "�����" �� �������������
		glBegin(GL_TRIANGLE_FAN);
		// ��������� ����� ����� ������������� � ������ �������
		glVertex2f(xCenter, yCenter);
		// ��������� ����� - ���������� �� ��� �������
		for (float angle = 0; angle <= float(2 * M_PI); angle += step)
		{
			float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
			const float dx = rx * cosf(a);
			const float dy = ry * sinf(a);
			glVertex2f(dx + xCenter, dy + yCenter);
		}
		glEnd();
	}
	//������ �����
	void FillLinesRight(float xCenter, float yCenter)
	{
		glBegin(GL_LINES);

		glVertex2f(xCenter - 56, yCenter - 40 );
		glVertex2f(xCenter - 68, yCenter - 64);

		glEnd();
	}
	//������ �����
	void FillLinesLeft(float xCenter, float yCenter)
	{
		glBegin(GL_LINES);

		glVertex2f(xCenter + 56, yCenter - 40);
		glVertex2f(xCenter + 68, yCenter - 64);

		glEnd();
	}
	//������ ����� ����
	void FillLinesNose(float xCenter, float yCenter)
	{
		glBegin(GL_LINES);

		glVertex2f(xCenter , yCenter + 5);
		glVertex2f(xCenter, yCenter + 25);

		glEnd();
	}
	//������ ������ �����
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

	//������ ����
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

	// ������ ����� ����
	glColor3f(0.85f, 0.325f, 0.49f);
	FillEllipse(size.x / 2.f + 78, size.y / 2.f + 56, 10, 20);

	// ������ ������ ����
	glColor3f(0.85f, 0.325f, 0.49f);
	FillEllipse(size.x / 2.f - 78, size.y / 2.f + 56, 10, 20);

	// ������ ������ ����
	glColor3f(0.85f, 0.325f, 0.49f);
	FillEllipse(size.x / 2.f + 18, size.y / 2.f + 120, 18, 14);
	FillEllipse(size.x / 2.f + 16, size.y / 2.f + 108, 10, 18);

	// ������ ����� ����
	glColor3f(0.85f, 0.325f, 0.49f);
	FillEllipse(size.x / 2.f - 18, size.y / 2.f + 120, 18, 14);
	FillEllipse(size.x / 2.f - 16, size.y / 2.f + 108, 10, 18);

	// ������ ������ ���������
	glColor3f(0.4078f, 0.2862f, 0.5529f);
	DrawNeedles(size.x / 2.f, size.y / 2.f);

	// ������ �������� �����
	glColor3f(0.85f, 0.325f, 0.49f);
	FillEllipse(size.x / 2.f, size.y / 2.f, 92, 90);

	//������� �������� �����
	glColor3f(0.7f, 0.2f, 0.4f);
	glLineWidth(5);
	StrokeEllipse(size.x / 2.f, size.y / 2.f, 90, 90);

	//������ ����� ����
	glColor3f(1, 1, 1);
	FillEllipse(size.x / 2.f - 30, size.y / 2.f - 25, 25, 25);

	//������ ������ ������ �����
	glColor3f(0, 0, 0);
	FillEllipse(size.x / 2.f - 15, size.y / 2.f - 25, 8, 10);
	glColor3f(1, 1, 1);
	FillEllipse(size.x / 2.f - 10, size.y / 2.f - 28, 2, 4);

	//������ ������ ����
	glColor3f(1, 1, 1);
	FillEllipse(size.x / 2.f + 30, size.y / 2.f - 25, 25, 25);

	//������ ������ ������� �����
	glColor3f(0, 0, 0);
	FillEllipse(size.x / 2.f + 15, size.y / 2.f - 25, 8, 10);
	glColor3f(1, 1, 1);
	FillEllipse(size.x / 2.f + 20, size.y / 2.f - 29, 2, 4);

	//������ ���� (����� ����)
	glColor3f(0.3f, 0.2f, 0.4f);
	glLineWidth(9);
	StrokeEllipse(size.x / 2.f - 30, size.y / 2.f - 25, 28, 27);
	FillLinesRight(size.x / 2.f, size.y / 2.f);

	//������ ���� (������ ����)
	glColor3f(0.3f, 0.2f, 0.4f);
	glLineWidth(9);
	StrokeEllipse(size.x / 2.f + 30, size.y / 2.f - 25, 28, 27);
	FillLinesLeft(size.x / 2.f, size.y / 2.f);

	//������ ���
	glColor3f(0.6f, 0.2f, 0.3f);
	glLineWidth(5);
	FillLinesNose(size.x / 2.f, size.y / 2.f);
	FillEllipse(size.x / 2.f, size.y / 2.f + 5, 13, 6);

	//������ ���
	glColor3f(0.3f, 0.2f, 0.5f);
	DrawLips(size.x / 2.f, size.y / 2.f);
}

void CWindow::SetupView(const glm::ivec2 &size)
{
	// ������� ���������������� ������������� ����������� � ��������� ������������
	// �� ��������������� � ��������, ������ (size.X x size.Y x 2).
	const glm::mat4 matrix = glm::ortho<float>(0, float(size.x), float(size.y), 0);
	glViewport(0, 0, size.x, size.y);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(matrix));
	glMatrixMode(GL_MODELVIEW);
}


