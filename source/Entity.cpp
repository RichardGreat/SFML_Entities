#include "Entity.hpp"

Entity::Entity() :
	sf::Sprite()
{
}

void Entity::setOpacity(sf::Uint8 opacity)
{
	sf::Color color = getColor();
	color.a = opacity;
	setColor(color);
}

void Entity::setSize(float width, float height)
{
	if (auto& rect = getTextureRect(); rect.width && rect.height)
	{
		float dx = width / std::abs(rect.width);
		float dy = height / std::abs(rect.height);
		setScale(dx, dy);
	}
}

void Entity::setSize(const sf::Vector2f& size)
{
	setSize(size.x, size.y);
}

sf::Vector2f Entity::getSize() const
{
	const auto& rect = getTextureRect();
	const sf::Vector2f& current_scale = getScale();

	float width = rect.width * current_scale.x;
	float height = rect.height * current_scale.y;

	return sf::Vector2f(width, height);
}
