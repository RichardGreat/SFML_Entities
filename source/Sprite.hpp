#pragma once

#include <SFML/Graphics.hpp>

// Демонстрирует упрощённый функционал sf::RectangleShape:
// перемещение, изменение масштаба, цвета и т.д.
// Применение: например, при создании краткоживущих сущностей и анимаций.
// Для сравнения, объект класса sf::Sprite "весит" 288 байт, т.к. включает в себя 
// матрицу трансформации и переменные параметров. Объект класса Sprite весит 96 байт
// и использует упрощённые вычисления

class Sprite : public sf::Drawable
{
public:
	Sprite();
	Sprite(sf::Texture* texture);
	Sprite(sf::Texture* texture, const sf::IntRect& rectangle);
	~Sprite();

	void setTexture(sf::Texture* texture);
	void setTextureRect(const sf::IntRect& rect);
	void setColor(sf::Color color);
	void setOpacity(sf::Uint8 opacity);
	void setSize(sf::Vector2f size);
	void setDefaultSize();
	void setPosition(sf::Vector2f position);

	sf::Color          getColor()    const;
	sf::Uint8          getOpacity()  const;
	sf::Vector2f       getPosition() const;
	sf::Vector2f       getSize()     const;
	const sf::Texture* getTexture()  const;

private:
	void draw(sf::RenderTarget&, sf::RenderStates) const;

	sf::Vertex   m_vertices[4];
	sf::Texture* m_texture;
	sf::Vector2f m_size;
};