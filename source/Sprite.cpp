#include "Sprite.hpp"

Sprite::Sprite() :
	m_texture(nullptr)
{
}

Sprite::Sprite(sf::Texture* texture) :
	m_texture(nullptr)
{
	setTexture(texture);
}

Sprite::Sprite(sf::Texture* texture, const sf::IntRect& rectangle) :
	m_texture(nullptr)
{
	setTexture(texture);
	setTextureRect(rectangle);
}

Sprite::~Sprite()
{
}

void Sprite::setTexture(sf::Texture* texture)
{
	m_texture = texture;
	setTextureRect(sf::IntRect(sf::Vector2i(), sf::Vector2i(texture->getSize())));
}

void Sprite::setTextureRect(const sf::IntRect& rectangle)
{
	m_size.x = static_cast<float>(rectangle.width);
	m_size.y = static_cast<float>(rectangle.height);

	float left   = static_cast<float>(rectangle.left);
	float top    = static_cast<float>(rectangle.top);
	float width  = static_cast<float>(rectangle.width);
	float height = static_cast<float>(rectangle.height);

	m_vertices[0].texCoords = sf::Vector2f(left, top);
	m_vertices[1].texCoords = sf::Vector2f(left + width, top);
	m_vertices[2].texCoords = sf::Vector2f(left + width, top + height);
	m_vertices[3].texCoords = sf::Vector2f(left, top + height);
}

void Sprite::setColor(sf::Color color)
{
	for (size_t i = 0; i < 4; i++)
		m_vertices[i].color = color;
}

void Sprite::setOpacity(sf::Uint8 opacity)
{
	for (size_t i = 0; i < 4; i++)
		m_vertices[i].color.a = static_cast<sf::Uint8>(opacity);
}

void Sprite::setSize(sf::Vector2f size)
{
	m_size = size;
}

void Sprite::setDefaultSize()
{
	m_size = m_vertices[2].texCoords;
}

void Sprite::setPosition(sf::Vector2f position)
{
	position -= m_size / 2.0f; // offset

	m_vertices[0].position = position;
	m_vertices[1].position = sf::Vector2f(position.x + m_size.x, position.y);
	m_vertices[2].position = sf::Vector2f(position.x + m_size.x, position.y + m_size.y);
	m_vertices[3].position = sf::Vector2f(position.x, position.y + m_size.y);
}

sf::Color Sprite::getColor() const
{
	return m_vertices[0].color;
}

sf::Uint8 Sprite::getOpacity() const
{
	return m_vertices[0].color.a;
}

sf::Vector2f Sprite::getPosition() const
{
	return m_vertices[0].position;
}

sf::Vector2f Sprite::getSize() const
{
	return m_size;
}

const sf::Texture* Sprite::getTexture() const
{
	return m_texture;
}

void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_texture)
	{
		states.texture = m_texture;
		target.draw(m_vertices, 4, sf::Quads, states);
	}
}
