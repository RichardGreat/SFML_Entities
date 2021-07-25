#define _USE_MATH_DEFINES
#include <cmath>

#include "ParticleSystem.hpp"

float radians(int angle)
{
	angle %= 360;
	return angle * M_PI / 180.0f;
}

ParticleSystem::ParticleSystem(sf::Texture& texture, sf::Shader& shader, std::size_t amount) :
    m_points(sf::Points, amount),
    m_particles(amount)
{
    m_texture = &texture;
    m_shader = &shader;
}

ParticleSystem::~ParticleSystem()
{
    m_points.clear();
}

void ParticleSystem::setEmitter(sf::Vector2f position)
{
    m_emitter = position;
}

void ParticleSystem::update(sf::Time delta_time)
{
    for (std::size_t i = 0; i < m_particles.size(); ++i)
    {
        Particle& particle = m_particles[i];
        particle.m_lifetime -= delta_time;

        if (particle.m_lifetime <= sf::Time::Zero)
            resetParticle(i);

        m_points[i].position += particle.m_velocity * delta_time.asSeconds() / float(screen.width);

        float ratio = particle.m_lifetime / sf::seconds(3.0f);
        m_points[i].color.a = static_cast<sf::Uint8>(ratio * 255);
    }
}

sf::Vector2f ParticleSystem::to_ndc(const sf::Vector2f& pos)
{
    float scr_half_w = screen.width / 2.0f;
    float scr_half_h = screen.height / 2.0f;

    float x = (pos.x - scr_half_w) / scr_half_w;
    float y = (pos.y - scr_half_h) / scr_half_h;

    return sf::Vector2f(x, -y);
}

void ParticleSystem::resetParticle(std::size_t index)
{
    float angle = radians(std::rand() % 360);
    float speed = (std::rand() % 50) + 50.f;

    m_particles[index].m_velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
    m_particles[index].m_lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

    m_points[index].position = to_ndc(m_emitter);
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.shader = m_shader;
    states.texture = m_texture;
    target.draw(m_points, states);
}
