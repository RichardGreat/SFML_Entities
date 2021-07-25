#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

//                                                      Запуск тестового примера
// int main()
//{
//
//    sf::RenderWindow window(screen, "Simple shaders!");
//    window.setFramerateLimit(60);
//
//    sf::Texture texture;
//    texture.loadFromFile("textures/quad.png");
//    texture.setSmooth(true);
//
//    sf::Shader shader;
//
//    if (!sf::Shader::isGeometryAvailable())
//        return EXIT_FAILURE;
//
//    if (!shader.loadFromFile("shaders/effect.vert", "shaders/effect.geom", "shaders/effect.frag"))
//        return EXIT_FAILURE;
//
//    shader.setUniform("resolution", sf::Vector2f((float)screen.width, (float)screen.height)); 
//    shader.setUniform("size", sf::Vector2f(32, 32));                                          
//    shader.setUniform("texture", sf::Shader::CurrentTexture);                                 
//
//    ParticleSystem ps(texture, shader, 1000);
//
//    sf::Clock clock;
//    sf::Time delta_time;
//
//    while (window.isOpen())
//    {
//        static sf::Event event;
//
//        while (window.pollEvent(event))
//            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
//                window.close();
//
//        delta_time = clock.restart();
//
//        sf::Vector2i mouse = sf::Mouse::getPosition(window);
//        auto pos = window.mapPixelToCoords(mouse);
//        ps.setEmitter(window.mapPixelToCoords(mouse));
//
//        window.clear();
//
//        ps.update(delta_time);
//
//       
//        window.draw(ps);
//        window.display();
//    }
//    return EXIT_SUCCESS;
//}

extern sf::VideoMode screen;

class ParticleSystem :
    public sf::Drawable
{
public:
    ParticleSystem(sf::Texture& texture, sf::Shader& shader, std::size_t amount);
    ~ParticleSystem() = default;

    void setEmitter(const sf::Vector2f& position);
    void setParticleSize(const sf::Vector2f& size);
    void setDirection(float direction);
    void setDispersion(float dispersion);
    void setPower(float power);

    void update(sf::Time delta_time);

private:
    sf::Vector2f to_ndc(const sf::Vector2f& pos);
    void resetParticle(std::size_t index);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    struct Particle
    {
        sf::Vector2f m_velocity;
        sf::Time     m_lifetime;
    };

    sf::Vector2f m_emitter;
    sf::Vector2f m_particle_size;

    float        m_direction;
    float        m_dispersion;
    float        m_power;

    const sf::Texture* m_texture;
    sf::Shader*        m_shader;

    sf::VertexArray       m_vertices;
    std::vector<Particle> m_particles;
};
