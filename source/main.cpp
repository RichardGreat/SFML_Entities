#include "Plume.hpp"
#include "Sprite.hpp"
#include "Animator.hpp"

#include <string_view>

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

    auto quad_texture =  get_texture("quad");
    auto star_texture = get_texture("star1");

    Sprite star(star_texture);
    star.setSize(sf::Vector2f(50, 50));
    star.setPosition(sf::Vector2f(screen.width / 2.0f, screen.height / 2.0f));

    Animator<Sprite> animator(*star_texture, 5, sf::seconds(1.0f / 12));
    animator.set(star);

    sf::Shader shader;

    if (!sf::Shader::isGeometryAvailable())
        return EXIT_FAILURE;

    if (!shader.loadFromFile("resources/shaders/plume.vert", "resources/shaders/plume.geom", "resources/shaders/plume.frag"))
        return EXIT_FAILURE;

    shader.setUniform("resolution", sf::Vector2f((float)screen.width, (float)screen.height));
    shader.setUniform("size", sf::Vector2f(50, 50));
    shader.setUniform("texture", sf::Shader::CurrentTexture);

    Plume effect(*quad_texture, shader, 100);

    sf::Clock clock;
    sf::Time delta_time;

    while (window.isOpen())
    {
        static sf::Event event;

        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

        delta_time = clock.restart();

        sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(window);
        effect.setEmitter(mouse);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {

        }

        effect.update(delta_time);
        animator.update(delta_time);

        window.clear();
        window.draw(effect);
        window.draw(star);
        window.display();
    }
    return EXIT_SUCCESS;
}