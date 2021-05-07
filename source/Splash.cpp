#define _USE_MATH_DEFINES
#include <cmath>

#include "Splash.hpp"

constexpr std::size_t point_count = 12;

Splash::Splash(sf::Vector2f start_position, float radius)
{
	m_offset = M_PI * 2 / point_count;
	
	m_vertices.reserve(point_count);
	
	for(std::size_t i = 0; i < point_count; ++i)
	{
		float x = std::cosf(i * m_offset) * m_radius + start_position.x;
		float y = std::sinf(i * m_offset) * m_radius + start_position.y;

		m_vertices.emplace_back(sf::Vertex(sf::Vector2f(x, y), sf::Color::Cyan, sf::Vector2f()));
	}
	m_lifetime = sf::milliseconds((std::rand() % 2000) + 1000);
}	

Splash::~Splash()
{
	m_vertices.clear();
}

void Splash::update(sf::Time delta)
{
	m_radius++;

	for (std::size_t i = 0; i < point_count; ++i)
	{
		m_vertices[i].position.x = std::cosf(i * m_offset) * m_radius + m_vertices[i].position.x;
		m_vertices[i].position.y = std::sinf(i * m_offset) * m_radius + m_vertices[i].position.y;
		//m_vertices[i].color.a--;
	}
	m_lifetime -= delta;
}

bool Splash::is_alive() const
{
	return m_lifetime > sf::Time::Zero;
}

void Splash::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(&m_vertices[0], m_vertices.size(), sf::Points, states);
}
