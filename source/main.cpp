#include "Plume.hpp"

sf::VideoMode screen(800, 600);

int main()
{
    srand(static_cast<unsigned>(time(0)));

    sf::RenderWindow window(screen, "SFML Entities!");
    window.setFramerateLimit(60);

    sf::Texture texture;
    texture.loadFromFile("resources/textures/quad.png");
    texture.setSmooth(true);

    sf::Shader shader;

    if (!sf::Shader::isGeometryAvailable())
        return EXIT_FAILURE;

    if (!shader.loadFromFile("resources/shaders/plume.vert", "resources/shaders/plume.geom", "resources/shaders/plume.frag"))
        return EXIT_FAILURE;

    shader.setUniform("resolution", sf::Vector2f((float)screen.width, (float)screen.height));
    shader.setUniform("size", sf::Vector2f(50, 50));
    shader.setUniform("texture", sf::Shader::CurrentTexture);

    Plume effect(texture, shader, 100);

    sf::Clock clock;
    sf::Time delta_time;

    while (window.isOpen())
    {
        static sf::Event event;

        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

        delta_time = clock.restart();

        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        effect.setEmitter(window.mapPixelToCoords(mouse));

        effect.update(delta_time);

        window.clear();
        window.draw(effect);
        window.display();
    }
    return EXIT_SUCCESS;
}