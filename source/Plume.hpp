#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

extern sf::VideoMode screen;

class Plume : public sf::Drawable
{
public:
    Plume(sf::Texture& texture, sf::Shader& shader, std::size_t amount);
    ~Plume();

    void setEmitter(sf::Vector2f position);
    void update(sf::Time delta_time);

protected:
    sf::Vector2f to_ndc(sf::Vector2f& pos);
    void resetParticle(std::size_t index);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    struct Particle
    {
        sf::Vector2f m_velocity;
        sf::Time     m_lifetime;
    };

    sf::Vector2f          m_emitter;
    sf::Texture*          m_texture;
    sf::Shader*           m_shader;
    sf::VertexArray       m_points;
    std::vector<Particle> m_particles;
};