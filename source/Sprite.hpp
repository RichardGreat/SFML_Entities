#pragma once

#include <SFML/Graphics.hpp>

class Sprite : public sf::Drawable
{
public:
	Sprite();
	Sprite(sf::Texture* texture);
	Sprite(sf::Texture* texture, const sf::FloatRect& rectangle);
	~Sprite();

	void setTexture(sf::Texture* texture);
	void setTextureRect(const sf::FloatRect& rect);
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