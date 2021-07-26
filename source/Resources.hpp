#pragma once

#include <SFML/Graphics.hpp>

#include <string_view>

sf::Texture* get_texture(const std::string_view filename) noexcept;
sf::Font*    get_font(const std::string_view filename)    noexcept;

// Brief:
//
// auto texture = get_texture("my_texture");
// texture->setRepeated(true);
//
// sf::RectangleShape background(1200, 720);
// background.setTexture(texture)
// ...
// Draw it!
//
//
// #include <cassert>
//
// auto font = get_font("my_font");
// assert(font, "Failed to load font!");
//
// sf::Text my_text;
// my_text.setFont(*font);
// ...
// Draw it!
//
