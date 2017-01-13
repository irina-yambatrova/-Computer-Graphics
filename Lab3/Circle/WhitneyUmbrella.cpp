#include "stdafx.h"
#include "WhitneyUmbrella.h"
#include <algorithm>

namespace
{
	const unsigned MIN_PRECISION = 4;
	const float UV_DELTA = 0.05f;

	void CalculateTriangleStripIndicies(std::vector<uint32_t> &indicies,
		unsigned count)
	{
		indicies.clear();
		indicies.reserve(count);
		for (unsigned ci = 0; ci <= count; ++ci)
		{
			indicies.push_back(ci);
		}
	}

	/// Привязывает вершины к состоянию OpenGL,
	/// затем вызывает 'callback'.
	template <class T>
	void DoWithBindedArrays(const std::vector<SVertexP3N> &vertices, T && callback)
	{
		// Включаем режим vertex array и normal array.
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		// Выполняем привязку vertex array и normal array
		const size_t stride = sizeof(SVertexP3N);
		glNormalPointer(GL_FLOAT, stride, glm::value_ptr(vertices[0].normal));
		glVertexPointer(3, GL_FLOAT, stride, glm::value_ptr(vertices[0].position));

		// Выполняем внешнюю функцию.
		callback();

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}

	glm::vec3 GetSurfacePoint(float u)
	{
		// Приводим параметры из диапазона [0..1] к диапазону [-3..3]
		return{ u , 0.f, 0.f };
	}
}

CCircle::CCircle(float count)
{
	//glLineWidth(2);
	Tesselate(count);
}

void CCircle::Draw() const
{
	DoWithBindedArrays(m_vertices, [this] {
		glDrawElements(GL_TRIANGLE_STRIP, GLsizei(m_indicies.size()),
			GL_UNSIGNED_INT, m_indicies.data());
	});
}

void CCircle::Tesselate(float count)
{
	m_vertices.reserve(count);
	// вычисляем позиции вершин.
	glm::vec3 normal = { 0.f, 0.f, 1.f };
	for (float ci = 0; ci <= count; ci += 0.01)
	{
		SVertexP3N vertex;
		vertex.position = GetSurfacePoint(ci);
		vertex.normal = normal;

		m_vertices.push_back(vertex);
	}
	CalculateTriangleStripIndicies(m_indicies, (2 * 100 * M_PI));
}