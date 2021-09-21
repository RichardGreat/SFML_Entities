#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>

// Brief:
//
// #include <cassert>
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
class AssetManager :
    private sf::NonCopyable
{
public:
    AssetManager() = default;
    ~AssetManager() = default;

    void loadFromDirectory(const std::string& folder);
    Resource* get(const std::string& name) const;
    void release();

private:
    std::map<std::string, Resource> m_resources;
};

#include "AssetManager.inl"
