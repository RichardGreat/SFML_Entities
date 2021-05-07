#include <SFML/Graphics.hpp>
#include "tinyxml2.h"

#include <iostream>
#include <sstream>
#include <algorithm>

#include <string>
#include <vector>

// Функция генерует коллаж из tmx - файла. Поддерживает загрузку нескольких тайлсетов.
// Примечательно, что в самом TME тоже есть подобная опция импорта изображения.
// Применение: создавать статичные изображения, например, заднего плана сцены - 
// отрисовка цельным спрайтом оптимальнее массива тайлов

struct Tileset
{
	sf::Image image;
	std::size_t first_tile_id;
	std::size_t tile_width;
	std::size_t tile_height;
	std::size_t tile_count;
	std::size_t columns;
};

bool create_image(const char* tmx_file_path)
{
	tinyxml2::XMLDocument document;

	if (document.LoadFile(tmx_file_path) != tinyxml2::XML_SUCCESS)
	{
		std::cerr << "Loading file " << tmx_file_path << " failed...\n";
		return false;
	}

	tinyxml2::XMLElement* map = document.FirstChildElement("map");

	std::size_t COLUMNS = std::stoul(map->Attribute("width"));
	std::size_t ROWS    = std::stoul(map->Attribute("height"));

	std::vector<sf::IntRect>           tiles;
	std::vector<std::vector<uint32_t>> layers;
	std::vector<Tileset>               tilesets;

	for (auto tileset = map->FirstChildElement("tileset");
		      tileset != nullptr;
		      tileset = tileset->NextSiblingElement("tileset"))
	{
		Tileset data;
		data.first_tile_id = std::stoul(tileset->Attribute("firstgid"));
		data.tile_width = std::stoul(tileset->Attribute("tilewidth"));
		data.tile_height = std::stoul(tileset->Attribute("tileheight"));
		data.tile_count = std::stoul(tileset->Attribute("tilecount"));
		data.columns = std::stoul(tileset->Attribute("columns"));

		std::size_t rows = data.tile_count / data.columns;
		std::size_t columns = data.columns;

		for (size_t y = 0u; y < rows; ++y)
			for (size_t x = 0u; x < columns; ++x) // index of the tile vector is a tile id + 1
				tiles.emplace_back(sf::IntRect(x * data.tile_width, y * data.tile_height, data.tile_width, data.tile_height));

		auto img = tileset->FirstChildElement("image");
		std::string source = img->Attribute("source");

		while (!isalpha(source.front()))
			source.erase(0, 1);

		if (!data.image.loadFromFile(source))
			data.image.create(columns * data.tile_width, rows * data.tile_height, sf::Color::Red);

		tilesets.push_back(std::move(data));
	}
	tiles.shrink_to_fit();
	//                  Parse the layers, define the max size of the image in pixels
	for (auto element = map->FirstChildElement("layer");
		      element != nullptr;
		      element = element->NextSiblingElement("layer"))
	{
		COLUMNS = std::stoul(element->Attribute("width"));
		ROWS    = std::stoul(element->Attribute("height"));

		tinyxml2::XMLElement* data = element->FirstChildElement("data");

		std::string cvs_data = data->GetText();
		std::replace(cvs_data.begin(), cvs_data.end(), ',', ' ');

		std::vector<unsigned> csv_vector;
		csv_vector.reserve(cvs_data.size());

		unsigned id = 0;
		std::istringstream sstream(cvs_data);

		while (sstream >> id)
			csv_vector.push_back(id);

		csv_vector.shrink_to_fit();
		layers.push_back(std::move(csv_vector));
	}

	std::size_t WIDTH = COLUMNS * tilesets[0].tile_width;
	std::size_t HEIGHT = ROWS * tilesets[0].tile_height;

	sf::Image image_out;
	image_out.create(WIDTH, HEIGHT);

	for (auto& layer : layers)
		for (auto& tileset : tilesets)
		{
			std::size_t first_tile = tileset.first_tile_id;
			std::size_t last_tile = first_tile + tileset.tile_count;

			for (std::size_t i = 0, index = 0; i < ROWS; ++i)
				for (std::size_t j = 0; j < COLUMNS; ++j, ++index)
				{
					std::size_t tile_id = layer[index];

					if (tile_id >= first_tile && tile_id < last_tile)
					{
						std::size_t y = i * tileset.tile_height;
						std::size_t x = j * tileset.tile_width;

						image_out.copy(tileset.image, x, y, tiles[tile_id - 1]);
					}
				}
		}
	image_out.saveToFile("tilemap.png");

	return true;
}