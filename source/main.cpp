#include "Plume.hpp"
#include "Sprite.hpp"
#include "Animator.hpp"
#include "TileMap.hpp"

#include <string_view>

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

    //if(!create_image("resources/maps/test.tmx"))
    //    return EXIT_FAILURE;

    //TileMap map;

    //if(!map.load("resources/maps/World_1_1.tmx", get_texture("mario_tiles")))
    //    return EXIT_FAILURE;

    //auto t_sky = get_texture("sky");
    //t_sky->setRepeated(true); // GL_REPEAT
    //sf::Sprite s_sky(*t_sky, sf::IntRect(0, 0, map.bounds().x, map.bounds().y));

    //sf::View viewport(sf::FloatRect(0, 0, screen.width, screen.height));

    auto quad_texture =  get_texture("quad");/*
    auto star_texture = get_texture("star1");

    Sprite star(star_texture);
    star.setSize(sf::Vector2f(50, 50));
    star.setPosition(sf::Vector2f(screen.width / 2.0f, screen.height / 2.0f));

    Animator<Sprite> animator(*star_texture, 5, sf::seconds(1.0f / 12));
    animator.set(star);
    */
    sf::Shader shader;

    if (!sf::Shader::isGeometryAvailable())
        return EXIT_FAILURE;

    if (!shader.loadFromFile("resources/shaders/plume.vert", "resources/shaders/plume.geom", "resources/shaders/plume.frag"))
        return EXIT_FAILURE;

    shader.setUniform("resolution", sf::Vector2f((float)screen.width, (float)screen.height));
    shader.setUniform("size", sf::Vector2f(50, 50));
    shader.setUniform("texture", sf::Shader::CurrentTexture);

    sf::BlendMode mode = sf::BlendAdd;
    Plume effect(*quad_texture, shader, mode, 100);

    sf::Clock clock;
    sf::Time delta_time;

    while (window.isOpen())
    {
        static sf::Event event;

        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

        /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            viewport.move(-5, 0);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            viewport.move(5, 0);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            viewport.move(0, -5);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            viewport.move(0, 5);*/

        delta_time = clock.restart();

        sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(window);
        effect.setEmitter(mouse);

        effect.update(delta_time);
        //animator.update(delta_time);

        //window.setView(viewport);

        window.clear();
        //window.draw(s_sky);
        //window.draw(map);
        window.draw(effect);
        //window.draw(star);
        window.display();
    }
    return EXIT_SUCCESS;
}