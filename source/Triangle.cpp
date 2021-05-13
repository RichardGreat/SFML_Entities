#define _USE_MATH_DEFINES
#include <cmath>

#include "Triangle.hpp"

constexpr std::size_t point_amount = 360;
constexpr float offset = M_PI * 2 / point_amount;
constexpr float radius = 200.0f;

Triangle::Triangle():
	m_rotation(0)
{
	m_points.reserve(point_amount);

	for (size_t i = 0; i < point_amount; ++i)
	{
		float x = std::cosf(i * offset) * radius + screen.width / 2;
		float y = std::sinf(i * offset) * radius + screen.height / 2;

		m_points.emplace_back(sf::Vector2f(x, y));
	}
	
	for (size_t i = 0; i < std::size(m_vertices); ++i)
		m_vertices[i].position = m_points[i * 120];
	
	m_vertices[0].color = sf::Color::Red;
	m_vertices[1].color = sf::Color::Blue;
	m_vertices[2].color = sf::Color::Green;
}

Triangle::~Triangle()
{
	m_points.clear();
}

void Triangle::rotate()
{	
	for (size_t i = 0; i < std::size(m_vertices); ++i)
		m_vertices[i].position = m_points[(i * 120 + m_rotation) % point_amount];

	m_rotation++;
}

void Triangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_vertices, 3, sf::Triangles, states);
}
