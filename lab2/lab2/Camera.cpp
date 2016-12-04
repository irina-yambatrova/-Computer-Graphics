#include "stdafx.h"
#include "Camera.h"
#include <glm/gtx/rotate_vector.hpp>


namespace
{
	const float ROTATION_SPEED_RADIANS = 1.f;
	const float LINEAR_MOVE_SPEED = 5.f;
	const float MIN_DISTANCE = 1.5f;
	const float MAX_DISTANCE = 30.f;

	bool ShouldTrackKeyPressed(const SDL_Keysym &key)
	{
		switch (key.sym)
		{
		case SDLK_LEFT:
		case SDLK_RIGHT:
		case SDLK_UP:
		case SDLK_DOWN:
		case SDLK_w:
		case SDLK_a:
		case SDLK_s:
		case SDLK_d:
			return true;
		}
		return false;
	}

	float GetRotationSpeedRadians(std::set<unsigned> & keysPressed)
	{
		if (keysPressed.count(SDLK_RIGHT) || keysPressed.count(SDLK_d))
		{
			return ROTATION_SPEED_RADIANS;
		}
		if (keysPressed.count(SDLK_LEFT) || keysPressed.count(SDLK_a))
		{
			return -ROTATION_SPEED_RADIANS;
		}
		return 0;
	}

	float GetLinearMoveSpeed(std::set<unsigned> & keysPressed)
	{
		if (keysPressed.count(SDLK_UP) || keysPressed.count(SDLK_w))
		{
			return -LINEAR_MOVE_SPEED;
		}
		if (keysPressed.count(SDLK_DOWN) || keysPressed.count(SDLK_s))
		{
			return +LINEAR_MOVE_SPEED;
		}
		return 0;
	}
}


CCamera::CCamera(float rotationRadians, float distance)
	: m_rotationRadiansX(rotationRadians)
	, m_distance(distance)
{
	SetDirection({ 0.f, 0.5f, 1.f });
}

void CCamera::Update(float deltaSec)
{
	m_rotationRadiansX += deltaSec * GetRotationSpeedRadians(m_keysPressed);
	m_distance += deltaSec * GetLinearMoveSpeed(m_keysPressed);
	m_distance = glm::clamp(m_distance, MIN_DISTANCE, MAX_DISTANCE);
}

bool CCamera::OnKeyDown(const SDL_KeyboardEvent &event)
{
	if (ShouldTrackKeyPressed(event.keysym))
	{
		m_keysPressed.insert(unsigned(event.keysym.sym));
		return true;
	}
	return false;
}

bool CCamera::OnKeyUp(const SDL_KeyboardEvent &event)
{
	if (ShouldTrackKeyPressed(event.keysym))
	{
		m_keysPressed.erase(unsigned(event.keysym.sym));
		return true;
	}
	return false;
}
void CCamera::OnDragBegin(const glm::vec2 &pos)
{
	m_isRotating = true;
	m_stance = pos;
}
void CCamera::OnDragMotion(const glm::vec2 &pos)
{
	if (m_isRotating)
	{
		glm::vec2 displacment = m_stance - pos;
		m_stance = pos;
		m_rotationRadiansX += displacment.x / 110.f;
		m_rotationRadiansY += displacment.y / 110.f;
	}
}
void CCamera::OnDragEnd(const glm::vec2 &pos)
{
	m_isRotating = false;
}

void CCamera::SetDirection(const glm::vec3 &direction)
{
	// Дополнительно нормализуем вектор (приводим к единичной длине).
	m_direction = glm::normalize(direction);
}

glm::mat4 CCamera::GetViewTransform()
{
	glm::vec3 direction = { 0.f, 0.5f, 1.f };
	// Нормализуем вектор (приводим к единичной длине),
	// затем поворачиваем вокруг оси Y.
	// см. http://glm.g-truc.net/0.9.3/api/a00199.html
	direction = glm::rotateY(glm::normalize(direction), m_rotationRadiansX);
	direction = glm::rotateX(glm::normalize(direction), m_rotationRadiansY);

	const glm::vec3 eye = direction * m_distance;
	const glm::vec3 center = { 0, 0, 0 };
	const glm::vec3 up = { 0, 1, 0 };
	m_position = eye;
	m_direction = center - eye;
	// Матрица моделирования-вида вычисляется функцией glm::lookAt.
	// Она даёт матрицу, действующую так, как будто камера смотрит
	// с позиции eye на точку center, а направление "вверх" камеры равно up.
	return glm::lookAt(eye, center, up);
}

const glm::vec3 & CCamera::GetEyePosition() const
{
	return m_position;
}

const glm::vec3 & CCamera::GetEyeDirection() const
{
	return m_direction;
}