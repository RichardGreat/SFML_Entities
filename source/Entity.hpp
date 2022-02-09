#pragma once

#include <SFML/Graphics.hpp>

// Демонстрирует второй принцип SOLID - принцип открытости/закрытости:  
// "программные сущности … должны быть открыты для расширения, но закрыты для модификации".
// Расширяет класс sf::Sprite, не затрагивая исходный код SFML

class Entity :
	public sf::Sprite
{
public:
	Entity();
	~Entity() = default;

	void setOpacity(sf::Uint8 opacity);
	void setSize(float width, float height /* value in pixels */);
	void setSize(const sf::Vector2f& size);

	sf::Vector2f getSize() const;
};
