#define _USE_MATH_DEFINES
#include <cmath>

#include "ParticleSystems.hpp"

float radians(int angle)
{
	// angle %= 360;
	return angle * M_PI / 180.0f;
}

ParticleSystem_1::ParticleSystem_1(sf::Texture& texture, sf::Shader& shader, sf::BlendMode& mode, std::size_t amount) :
	m_points(sf::Points, amount),
	m_particles(amount)
{
	m_states.texture = &texture;
	m_states.shader = &shader;
	m_states.blendMode = mode;
}

ParticleSystem_1::~ParticleSystem_1()
{
	m_points.clear();
}

void ParticleSystem_1::setEmitter(sf::Vector2f position)
{
	m_emitter = position;
}

void ParticleSystem_1::update(sf::Time delta_time)
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

sf::Vector2f ParticleSystem_1::to_ndc(sf::Vector2f& pos)
{
	float scr_half_w = screen.width / 2.0f;
	float scr_half_h = screen.height / 2.0f;

	float x = (pos.x - scr_half_w) / scr_half_w;
	float y = (pos.y - scr_half_h) / scr_half_h;

	return sf::Vector2f(x, -y);
}

void ParticleSystem_1::resetParticle(std::size_t index)
{
	float angle = (std::rand() % 360) * 3.14f / 180.f;
	float speed = (std::rand() % 50) + 50.f;

	m_particles[index].m_velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	m_particles[index].m_lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

	m_points[index].position = to_ndc(m_emitter);
}

void ParticleSystem_1::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_points, m_states);
}

//                                           ParticleSystem 2

ParticleSystem_2::ParticleSystem_2(std::size_t amount, float size)
{
	m_vertices.reserve(amount * 4);
	m_size = size / 2;

	for (size_t i = 0; i < amount; ++i)
	{
		sf::Color random_color(rand() % 255, rand() % 255, rand() % 255, 255);

		m_vertices.emplace_back(sf::Vector2f(0, 0),       random_color, sf::Vector2f());
		m_vertices.emplace_back(sf::Vector2f(size, 0),    random_color, sf::Vector2f());
		m_vertices.emplace_back(sf::Vector2f(size, size), random_color, sf::Vector2f());
		m_vertices.emplace_back(sf::Vector2f(0, size),    random_color, sf::Vector2f());
	}
}

ParticleSystem_2::~ParticleSystem_2()
{
	m_vertices.clear();
}

void ParticleSystem_2::update(sf::Vector2f position)
{
	for (std::size_t i = 0; i < m_vertices.size() / 4; ++i)
	{
		sf::Vertex* quad = &m_vertices[i * 4];

		if (quad->color.a > 5)
		{
			for (size_t j = 0; j < 4; ++j)
				quad[j].color.a--;

			quad[0].position += sf::Vector2f(0, 0);
			quad[0].position += sf::Vector2f(m_size, 0);
			quad[0].position += sf::Vector2f(m_size, m_size);
			quad[0].position += sf::Vector2f(0, m_size);
		}
		else
		{			
			float angle = radians(std::rand() % 360);
			float speed = (std::rand() % 50) + 50.f;
			m_particles[index] = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);

			sf::Vertex* quad = &m_vertices[index * 4];

			for (size_t i = 0; i < 4; ++i)
				quad[i].color.a = sf::Uint8(255);
		}
						
	}
}

void ParticleSystem_2::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(&m_vertices[0], m_vertices.size(), sf::Quads, states);
}
