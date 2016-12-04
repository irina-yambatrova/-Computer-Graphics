#pragma once

#include <glm/vec3.hpp>
#include <glm/fwd.hpp>
#include <boost/noncopyable.hpp>

enum class CuboctahedronFace
{
	Front = 0,
	Back,
	Top,
	Bottom,
	Left,
	Right,

	NumFaces
};

class CIdentityCuboctahedron
{
public:
	CIdentityCuboctahedron();
	void Update(float deltaTime);
	void Draw()const;

	void SetFaceColor(CuboctahedronFace face, const glm::vec3 &color);
	void SetAlpha(float alpha);

	void DrawObject();



private:
	void OutputFaces()const;

	static const size_t COLORS_COUNT = static_cast<size_t>(CuboctahedronFace::NumFaces);
	glm::vec3 m_colors[COLORS_COUNT];
	float m_alpha;
};
