#include "stdafx.h"
#include "Bodies.h"
#include <stdint.h>

namespace
{

	typedef glm::vec3 Vertex;

	const Vertex Cuboctahedron_VERTICIES[] = {
		// 12 вершин.
		{ 1.5, 0, 1.5 },
		{ 1.5, 0, -1.5 },
		{ -1.5, 0, 1.5 },
		{ -1.5, 0, -1.5 },

		{ 1.5, 1.5, 0 },
		{ 1.5, -1.5, 0 },
		{ -1.5,1.5, 0 },
		{ -1.5, -1.5, 0 },

		{ 0, 1.5, 1.5 },
		{ 0, 1.5, -1.5 },
		{ 0, -1.5, 1.5 },
		{ 0, -1.5, -1.5 },
	};


	struct STriangleFace
	{
		uint16_t vertexIndex1;
		uint16_t vertexIndex2;
		uint16_t vertexIndex3;
		uint16_t colorIndex;
	};

	// Привыкаем использовать 16-битный unsigned short,
	// чтобы экономить память на фигурах с тысячами вершин.
	const STriangleFace Cuboctahedron_FACES[] = {
		
		{ 4, 1, 5, static_cast<uint16_t>(CuboctahedronFace::Right) }, 
		{ 5, 0, 4, static_cast<uint16_t>(CuboctahedronFace::Right) }, 

		{ 10, 2, 8, static_cast<uint16_t>(CuboctahedronFace::Front) }, 
		{ 8, 0, 10, static_cast<uint16_t>(CuboctahedronFace::Front) }, 

		{ 6, 9, 4, static_cast<uint16_t>(CuboctahedronFace::Top) }, 
		{ 4, 8, 6, static_cast<uint16_t>(CuboctahedronFace::Top) }, 

		{ 3, 6, 2, static_cast<uint16_t>(CuboctahedronFace::Left) }, 
		{ 2, 7, 3, static_cast<uint16_t>(CuboctahedronFace::Left) }, 

		{ 3, 11, 1, static_cast<uint16_t>(CuboctahedronFace::Back) }, 
		{ 1, 9, 3, static_cast<uint16_t>(CuboctahedronFace::Back) }, 

		{ 11, 7, 10, static_cast<uint16_t>(CuboctahedronFace::Bottom) }, 
		{ 10, 5, 11, static_cast<uint16_t>(CuboctahedronFace::Bottom) }, 
		
		{ 11, 3, 7, static_cast<uint16_t>(CuboctahedronFace::Front) }, 
		{ 9, 1, 4, static_cast<uint16_t>(CuboctahedronFace::Left) }, 
		{ 10, 0, 5, static_cast<uint16_t>(CuboctahedronFace::Bottom) },
		{ 11, 5, 1, static_cast<uint16_t>(CuboctahedronFace::Front) }, 
		{ 8, 4, 0, static_cast<uint16_t>(CuboctahedronFace::Back) }, 
		{ 8, 2, 6, static_cast<uint16_t>(CuboctahedronFace::Top) }, 
		{ 10, 7, 2, static_cast<uint16_t>(CuboctahedronFace::Left) },
		{ 9, 6, 3, static_cast<uint16_t>(CuboctahedronFace::Bottom) }, 
	};
}

CIdentityCuboctahedron::CIdentityCuboctahedron()
	: m_alpha(1)
{
	// Используем белый цвет по умолчанию.
	for (glm::vec3 &color : m_colors)
	{
		color.x = 1;
		color.y = 1;
		color.z = 1;
	}
}

void CIdentityCuboctahedron::Update(float deltaTime)
{
	(void)deltaTime;
}

void CIdentityCuboctahedron::Draw() const
{
		glFrontFace(GL_CW);
		OutputFaces();
		glFrontFace(GL_CCW);
	//OutputFaces();
	
}

void CIdentityCuboctahedron::SetFaceColor(CuboctahedronFace face, const glm::vec3 &color)
{
	const size_t index = static_cast<size_t>(face);
	assert(index < COLORS_COUNT);
	m_colors[index] = color;
}


void CIdentityCuboctahedron::SetAlpha(float alpha)
{
	m_alpha = alpha;
}

void CIdentityCuboctahedron::DrawObject()
{

}

void CIdentityCuboctahedron::OutputFaces() const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glBegin(GL_TRIANGLES);
	for (const STriangleFace &face : Cuboctahedron_FACES)
	{
		const Vertex &v1 = Cuboctahedron_VERTICIES[face.vertexIndex1];
		const Vertex &v2 = Cuboctahedron_VERTICIES[face.vertexIndex2];
		const Vertex &v3 = Cuboctahedron_VERTICIES[face.vertexIndex3];
		glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
		glm::vec3 color = m_colors[face.colorIndex];

		glColor4f(color.x, color.y, color.z, m_alpha);
		glNormal3fv(glm::value_ptr(normal));
		glVertex3fv(glm::value_ptr(v1));
		glVertex3fv(glm::value_ptr(v2));
		glVertex3fv(glm::value_ptr(v3));
	}
	glEnd();

	glEnable(GL_LIGHTING);
	glCullFace(GL_FRONT_AND_BACK);
	glBegin(GL_TRIANGLES);
	for (const STriangleFace &face : Cuboctahedron_FACES)
	{
		const Vertex &v1 = Cuboctahedron_VERTICIES[face.vertexIndex1];
		const Vertex &v2 = Cuboctahedron_VERTICIES[face.vertexIndex2];
		const Vertex &v3 = Cuboctahedron_VERTICIES[face.vertexIndex3];
		glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
		glm::vec3 color = m_colors[face.colorIndex];

		glColor4f(color.x, color.y, color.z, m_alpha);
		glNormal3fv(glm::value_ptr(normal));
		glVertex3fv(glm::value_ptr(v1));
		glVertex3fv(glm::value_ptr(v2));
		glVertex3fv(glm::value_ptr(v3));
	}
	glEnd();
	glDisable(GL_LIGHTING);

	// Ребра. 
	glColor4f(0, 0, 0, 1);
	for (const STriangleFace &face : Cuboctahedron_FACES)
	{
		glBegin(GL_LINE_STRIP);
		const Vertex &v1 = Cuboctahedron_VERTICIES[face.vertexIndex1];
		const Vertex &v2 = Cuboctahedron_VERTICIES[face.vertexIndex2];
		const Vertex &v3 = Cuboctahedron_VERTICIES[face.vertexIndex3];

		glVertex3fv(glm::value_ptr(v1));
		glVertex3fv(glm::value_ptr(v2));
		glVertex3fv(glm::value_ptr(v3));
		glEnd();
	}
}


