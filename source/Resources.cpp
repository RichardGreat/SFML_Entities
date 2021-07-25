#include "Resources.hpp"

#include <map>

sf::Texture* get_texture(const std::string_view filename) noexcept
{
	static std::map<std::string_view, sf::Texture> textures;

	if (auto found = textures.find(filename); found != textures.end())
		return &found->second;

	sf::Texture new_texture;

	if (!new_texture.loadFromFile("textures/" + std::string(filename) + ".png"))
		if (!new_texture.loadFromFile("textures/" + std::string(filename) + ".jpg"))
		{ //    При сбое загрузки основных форматов изображений будет создан красный квадрат 50х50 пикселей
			sf::Image image;
			image.create(50, 50, sf::Color::Red);
			new_texture.loadFromImage(image);
		}
	new_texture.setSmooth(true);
	textures[filename] = new_texture;

	return &textures[filename];
}

sf::Font* get_font(const std::string_view filename) noexcept
{
	static std::map<std::string_view, sf::Font> fonts;

	if (auto found = fonts.find(filename); found != fonts.end())
		return &found->second;

	sf::Font new_font;

	if (!new_font.loadFromFile("resources/fonts/" + std::string(filename) + ".ttf"))
		return nullptr;

	fonts[filename] = new_font;

	return &fonts[filename];
}
