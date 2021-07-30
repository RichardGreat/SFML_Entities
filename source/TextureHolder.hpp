#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <string_view>

// Brief:
//
// TextureHolder t_holder;
// t_holder.load("textures");
//
// ...
//
// sf::Sprite sprite;
// sprite.setTexture(t_holder.get("texture_name"));
// 
// ...
// 
// Draw it!

class TextureHolder:
	private sf::NonCopyable
{
public:
	TextureHolder() = default;
	~TextureHolder() = default;

	void load(const std::string_view folder);
	sf::Texture* get(const std::string& name);

private:
	std::map<std::string, sf::Texture> m_textures;
};