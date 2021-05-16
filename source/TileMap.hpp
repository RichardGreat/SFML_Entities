#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

// Класс - загрузчик тайловых карт. Оптимизации посредством ограничения области
// вида камеры не требует, т.к. OpenGl самостоятельно исключает вершины, находящиеся 
// вне окна отображения. Объект класса  позволяет загружать карты из файлов .tmx,
// созданные посредством редактора TiledMapEditor, однако легко может быть адаптирован под
// другие форматы хранения данных

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