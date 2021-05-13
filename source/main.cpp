#include "Triangle.hpp"

#include <string_view>
#include <iostream>

sf::VideoMode screen(800, 600);

sf::Texture* get_texture(const std::string_view name)
{
    static std::map<std::string_view, sf::Texture> textures;

    if (auto found = textures.find(name); found != textures.end())
        return &found->second;
    else
    {
        auto texture = &textures[name];
        std::string filename{ name };

        if (!texture->loadFromFile("resources/textures/" + filename + ".png"))
            if (!texture->loadFromFile("resources/textures/" + filename + ".jpg"))
            {
                sf::Image image;
                image.create(50u, 50u, sf::Color::Red);
                texture->loadFromImage(image);
            }
        texture->setSmooth(true);

        return texture;
    }
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    sf::RenderWindow window(screen, "SFML Entities!");
    window.setFramerateLimit(60);

    Triangle triangle;

    while (window.isOpen())
    {
        static sf::Event event;

        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

        triangle.rotate();
                           
        window.clear();
        window.draw(triangle);
        window.display();
    }
    return EXIT_SUCCESS;
}