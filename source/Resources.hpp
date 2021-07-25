#pragma once

#include <SFML/Graphics.hpp>

#include <string_view>

sf::Texture* get_texture(const std::string_view filename) noexcept;
sf::Font*    get_font(const std::string_view filename)    noexcept;
