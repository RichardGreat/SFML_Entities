#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class TileMap : public sf::Drawable
{
public:
	TileMap():
		m_tileset(nullptr) {};

	~TileMap() = default;

	bool load(const char* tmx_file_path, const sf::Texture* tileset);
	sf::Vector2u bounds() const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	const sf::Texture*                   m_tileset;
	sf::Vector2u                         m_bounds;
	std::vector<std::vector<sf::Vertex>> m_tile_layers;
};