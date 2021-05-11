#include "Splash.hpp"

#include <string_view>
#include <list>
#include <iostream>

sf::VideoMode screen(800, 600);

bool create_image(const char* tmx_file_path);

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

    std::list<Splash> splashes;

    sf::Clock clock;
    sf::Time delta_time;
    sf::Time respawn;

    while (window.isOpen())
    {
        static sf::Event event;

        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

        delta_time = clock.restart();
        respawn += delta_time;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && respawn >= sf::seconds(0.3f))
        {
            sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(window);

            splashes.emplace_back(mouse, rand() % 50);
            respawn = sf::Time::Zero;
        }

		if (!splashes.empty())
			for (auto it = splashes.begin(); it != splashes.end();)
				if (it->is_alive())
				{
					it->update();
					it++;
				}
				else				
					it = splashes.erase(it);				
                           
        window.clear();
        for (auto& splash : splashes)
           window.draw(splash);
        window.display();
    }
    return EXIT_SUCCESS;
}