#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <string_view>

// Brief:
//
// AssetManager<sf::Texture> textures;
// textures.load("textures");
//
// sf::Texture* my_texture = textures.get("myTexture"); 
// assert(my_texture);
// 
// ...
// 
// sf::Sprite sprite;
// sprite.setTexture(*my_texture);
// 
// ...
// 
// Draw it!

template <class Resource>
class AssetManager:
	private sf::NonCopyable
{
public:
	AssetManager() = default;
	~AssetManager() = default;

	void load(const std::string_view folder);
	Resource* get(const std::string& name);

private:
	std::map<std::string, Resource> m_resources;
};
