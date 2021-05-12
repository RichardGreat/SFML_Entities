#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

extern sf::VideoMode screen;

class ParticleSystem_1 : public sf::Drawable
{
public:
    ParticleSystem_1(sf::Texture& texture, sf::Shader& shader, sf::BlendMode& mode, std::size_t amount);
    ~ParticleSystem_1();

    void setEmitter(sf::Vector2f position);
    void update(sf::Time delta_time);

protected:
    sf::Vector2f to_ndc(sf::Vector2f& pos);
    void resetParticle(std::size_t index);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    struct Particle
    {
        sf::Vector2f m_velocity;
        sf::Time     m_lifetime;
    };

    sf::Vector2f          m_emitter;
    sf::RenderStates      m_states;
    sf::VertexArray       m_points;
    std::vector<Particle> m_particles;
};

// Система частиц без использования шейдеров
class ParticleSystem_2 : public sf::Drawable
{
public:
	ParticleSystem_2(std::size_t amount, float size);
	~ParticleSystem_2();

	void update(sf::Vector2f position);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::vector<sf::Vertex> m_vertices;
    float                   m_size;
};