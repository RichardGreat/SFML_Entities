#define _USE_MATH_DEFINES
#include <cmath>

#include "Splash.hpp"

constexpr std::size_t point_count = 120;
constexpr float offset = M_PI * 2 / point_count;

Splash::Splash(sf::Vector2f start_position, float radius)
{
	m_velocity = radius / 100;

	m_vertices.reserve(point_count);

	sf::Color random_color(rand() % 255, rand() % 255, rand() % 255, 255);
	
	for(std::size_t i = 0; i < point_count; ++i)
	{
		float x = std::cosf(i * offset) * radius + start_position.x;
		float y = std::sinf(i * offset) * radius + start_position.y;

		m_vertices.emplace_back(sf::Vertex(sf::Vector2f(x, y), random_color, sf::Vector2f()));
	}
}	

Splash::~Splash()
{
	m_vertices.clear();
}

void Splash::update()
{
	for (std::size_t i = 0; i < point_count; ++i)
	{
		m_vertices[i].position.x += std::cosf(i * offset) * m_velocity;
		m_vertices[i].position.y += std::sinf(i * offset) * m_velocity;
		m_vertices[i].color.a--;
	}
}

bool Splash::is_alive() const
{
	return m_vertices[0].color.a > 10;
}

void Splash::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(&m_vertices[0], m_vertices.size(), sf::Points, states);
}
