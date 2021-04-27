#include "TileMap.hpp"
#include "tinyxml2.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

bool TileMap::load(const char* tmx_file_path, const sf::Texture* tileset)
{
	if (!tileset)
	{
		std::cerr << "Error. Texture was nullptr\n";
		return false;
	}
		
	m_tileset = tileset;

	tinyxml2::XMLDocument document;

	if (document.LoadFile(tmx_file_path) != tinyxml2::XML_SUCCESS)
	{
		std::cerr << "Loading file " << tmx_file_path << " failed...\n";
		return false;
	}

	tinyxml2::XMLElement* root = document.FirstChildElement("map");

	const std::size_t tile_width  = std::stoul(root->Attribute("tilewidth"));
	const std::size_t tile_height = std::stoul(root->Attribute("tileheight"));

	const std::size_t rows    = tileset->getSize().x / tile_width;
	const std::size_t columns = tileset->getSize().y / tile_height;

	const std::size_t map_width  = std::stoul(root->Attribute("width"));
	const std::size_t map_height = std::stoul(root->Attribute("height"));

	m_bounds = sf::Vector2u(map_width * tile_width, map_height * tile_height);

	std::vector<sf::Vector2f> texture_grid;
	texture_grid.reserve(rows * columns);

	for (size_t y = 0; y < columns; ++y)
		for (size_t x = 0; x < rows; ++x)
			texture_grid.emplace_back(sf::Vector2f(x * tile_width, y * tile_height));

	for (auto layer = root->FirstChildElement("layer");
		      layer;
		      layer = layer->NextSiblingElement("layer"))
	{
		tinyxml2::XMLElement* data = layer->FirstChildElement("data");

		std::string cvs_data = data->GetText();
		std::replace(cvs_data.begin(), cvs_data.end(), ',', ' ');

		std::vector<unsigned> current_layer;
		current_layer.reserve(cvs_data.size());

		unsigned id = 0;
		std::istringstream sstream(cvs_data);

		while (sstream >> id)
			current_layer.push_back(id);

		current_layer.shrink_to_fit();

		std::size_t tile_count = std::count_if(current_layer.begin(), current_layer.end(),
			[](unsigned id)
			{
				return id > 0;
			});

		std::vector<sf::Vertex> vertices;
		vertices.reserve(tile_count * 4);		

		for (std::size_t y = 0; y < map_height; ++y)	
			for (std::size_t x = 0; x < map_width; ++x)
			{
				std::size_t index = x + y * map_width;
				unsigned tile_id = current_layer[index];

				if (tile_id) 
				{
					tile_id--;
					sf::Vertex quad[4];

					quad[0].position = sf::Vector2f(x * tile_width,              y * tile_height);
					quad[1].position = sf::Vector2f(x * tile_width + tile_width, y * tile_height);
					quad[2].position = sf::Vector2f(x * tile_width + tile_width, y * tile_height + tile_height);
					quad[3].position = sf::Vector2f(x * tile_width,              y * tile_height + tile_height);

					quad[0].texCoords = sf::Vector2f(texture_grid[tile_id].x,              texture_grid[tile_id].y);
					quad[1].texCoords = sf::Vector2f(texture_grid[tile_id].x + tile_width, texture_grid[tile_id].y);
					quad[2].texCoords = sf::Vector2f(texture_grid[tile_id].x + tile_width, texture_grid[tile_id].y + tile_height);
					quad[3].texCoords = sf::Vector2f(texture_grid[tile_id].x,              texture_grid[tile_id].y + tile_height);

					for (auto& vertex : quad)
						vertices.push_back(vertex);
				}
			}		
		vertices.shrink_to_fit();
		m_tile_layers.push_back(std::move(vertices));
	}
	return true;
}

sf::Vector2u TileMap::bounds() const
{
	return m_bounds;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& layer : m_tile_layers)
		target.draw(&layer[0], layer.size(), sf::Quads, m_tileset);
}
