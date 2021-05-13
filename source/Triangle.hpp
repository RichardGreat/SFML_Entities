#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

extern sf::VideoMode screen;

// Класс Triangle предначен для демонстрации вращения примитива GL_TRIANGLES
// без применения наследования от sf::Transformable

class Triangle: public sf::Drawable
{
public:
	Triangle();
	~Triangle();

	void rotate();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<sf::Vector2f> m_points;
	sf::Vertex                m_vertices[3];
	std::size_t               m_rotation;
};