#include "stdafx.h"
#include "Window.h"
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/adaptor/reversed.hpp>

namespace
{
	const glm::vec4 BLACK = { 0, 0, 0, 1 };
	const glm::vec3 YELLOW = { 1.f, 1.f, 0.f };
	const glm::vec4 LIGHT_YELLOW_RGBA = { 1.f, 1.f, 0.5f, 1.f };
	const glm::vec3 ORANGE = { 1.f, 0.5f, 0.f };
	const glm::vec3 BLUE = { 0.f, 0.0043f, 1.f };
	const glm::vec3 GREEN = { 0.f, 1.f, 0.f };
	const glm::vec3 RED = { 1.f, 0.f, 0.f };
	const glm::vec3 WHITE = { 1.f, 1.f, 1.f };
	const glm::vec3 PINK = { 1.f, 0.3f, 0.3f };
	const glm::vec4 WHITE_LIGHT = { 1, 1, 1, 1 };
	const glm::vec3 SUNLIGHT_DIRECTION = { 0.7f, 0.7f, 1.f };
	

	const float CAMERA_INITIAL_ROTATION = 0;
	const float CAMERA_INITIAL_DISTANCE = 5.f;

	// �������� ���������� ������
	// ����� ������� �������������� ���
	void EnableBlending()
	{
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		// src, dest, alpha
		glBlendFunc(GL_ZERO, GL_ZERO);
	}

	// ��������� ���������� ������
	// ����� ������� ������������ ���
	void DisableBlending()
	{
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

	void SetupOpenGLState()
	{
		// �������� ��������� ���������� ����.
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);

		// �������� ������� ���������
		glEnable(GL_LIGHTING);

		// �������� ���������� ������ ������ ��� ����� ���������.
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	}

}


CWindow::CWindow()
	: m_camera(CAMERA_INITIAL_ROTATION, CAMERA_INITIAL_DISTANCE)
	, m_sunlight(GL_LIGHT0)
{

	SetBackgroundColor(LIGHT_YELLOW_RGBA);
	m_Cuboctahedron.SetAlpha(0.8f);
	m_Cuboctahedron.SetFaceColor(CuboctahedronFace::Top, RED);
	m_Cuboctahedron.SetFaceColor(CuboctahedronFace::Bottom, PINK);
	m_Cuboctahedron.SetFaceColor(CuboctahedronFace::Left, ORANGE);
	m_Cuboctahedron.SetFaceColor(CuboctahedronFace::Right, GREEN);
	m_Cuboctahedron.SetFaceColor(CuboctahedronFace::Front, WHITE);
	m_Cuboctahedron.SetFaceColor(CuboctahedronFace::Back, BLUE);

	m_sunlight.SetDirection(SUNLIGHT_DIRECTION);
	m_sunlight.SetDiffuse(WHITE_LIGHT);
	m_sunlight.SetAmbient(0.1f * WHITE_LIGHT);

}

void CWindow::OnWindowInit(const glm::ivec2 &size)
{
	(void)size;
	SetupOpenGLState();
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
	m_time += deltaSeconds;
	m_camera.Update(deltaSeconds);
	m_Cuboctahedron.Update(deltaSeconds);
	
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SetupView(size);
	m_sunlight.Setup();

	EnableBlending();
	m_Cuboctahedron.Draw();
	DisableBlending();

}

void CWindow::SetupView(const glm::ivec2 &size)
{
	glViewport(0, 0, size.x, size.y);

	// ������� ���� ������������ ������� � ����������
	// ��������� �������� ������� GL_MODELVIEW.
	glLoadMatrixf(glm::value_ptr(m_camera.GetViewTransform()));

	// ������� �������������� �������������� ����������� ��������
	// glm::perspective, ����������� ���� ������, ����������� ������
	// � ������ ����, ���������� �� ������� � ������� ���������� ���������.
	const float fieldOfView = glm::radians(70.f);
	const float aspect = float(size.x) / float(size.y);
	const float zNear = 0.01f;
	const float zFar = 100.f;
	const glm::mat4 proj = glm::perspective(fieldOfView, aspect, zNear, zFar);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(proj));
	glMatrixMode(GL_MODELVIEW);
}

void CWindow::SetupFog()
{
	if (m_isFogEnabled)
	{
		const float density = 0.2f;
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, GL_EXP2);
		glFogfv(GL_FOG_COLOR, glm::value_ptr(LIGHT_YELLOW_RGBA));
		glFogf(GL_FOG_DENSITY, density);
	}
	else
	{
		glDisable(GL_FOG);
	}
}

void CWindow::OnKeyDown(const SDL_KeyboardEvent &event)
{
	if (m_camera.OnKeyDown(event))
	{
		return;
	}
	if (event.keysym.sym == SDLK_f)
	{
		m_isFogEnabled = !m_isFogEnabled;
	}
}

void CWindow::OnKeyUp(const SDL_KeyboardEvent &event)
{
	m_camera.OnKeyUp(event);
}

void CWindow::OnDragBegin(const glm::vec2 &pos)
{
	m_camera.OnDragBegin(pos);
}
void CWindow::OnDragMotion(const glm::vec2 &pos)
{
	m_camera.OnDragMotion(pos);
}
void CWindow::OnDragEnd(const glm::vec2 &pos)
{
	m_camera.OnDragEnd(pos);
}