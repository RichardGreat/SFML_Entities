#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

extern sf::VideoMode screen;

class ParticleSystem :
    public sf::Drawable
{
public:
    ParticleSystem(sf::Texture& texture, sf::Shader& shader, std::size_t amount);
    ~ParticleSystem() = default;

    void setEmitter(const sf::Vector2f& position);
    void setDirection(float direction);
    void setDispersion(float dispersion);
    void setVelocity(float power);

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

    float        m_direction;
    float        m_dispersion;
    float        m_velocity;

    const sf::Texture* m_texture;
    sf::Shader*        m_shader;

    sf::VertexArray       m_vertices;
    std::vector<Particle> m_particles;
};
