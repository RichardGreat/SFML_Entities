#include "ParticleSystem.hpp"

#include "Utils.hpp"

ParticleSystem::ParticleSystem():
	m_particle_size(32.0f, 32.0f), // Default size is 32x32 pixels
	m_amount(0),
	m_last_used_particle(0),
	m_velocity(0.0f),
	m_lifetime_max(0.0f),
	m_rate(0.0f),
	m_timer(0.0f),
	m_is_emitted(false),
	m_is_attenuated(true),
	m_scaling_mode(ScalingMode::Off)
{
}

void ParticleSystem::setTexture(const sf::Texture* texture)
{
	setParticleSize(sf::Vector2f(texture->getSize())); 
	m_states.texture = texture;

	for (size_t i = 0; i < m_amount; ++i)
	{
		sf::Vertex* quad = &m_vertices[i * 4];

		quad[0].texCoords = sf::Vector2f(0, 0);
		quad[1].texCoords = sf::Vector2f(m_particle_size.x, 0);
		quad[2].texCoords = sf::Vector2f(m_particle_size.x, m_particle_size.y);
		quad[3].texCoords = sf::Vector2f(0, m_particle_size.y);
	}
}

void ParticleSystem::setColor(const sf::Color& color)
{
	for (size_t i = 0; i < m_amount; ++i)
	{
		sf::Vertex* quad = &m_vertices[i * 4];

		quad[0].color = color;
		quad[1].color = color;
		quad[2].color = color;
		quad[3].color = color;
	}
}

void ParticleSystem::setShader(const sf::Shader* shader)
{
	m_states.shader = shader;
}

void ParticleSystem::setBlendMode(const sf::BlendMode& blend_mode)
{
	m_states.blendMode = blend_mode;
}

void ParticleSystem::setParticleSize(const sf::Vector2f& size)
{
	m_particle_size = size;
}

void ParticleSystem::setEmitter(const sf::Vector2f& emitter)
{
	m_emitter = emitter;
}

void ParticleSystem::setDirection(sf::Angle direction)
{
	m_direction = direction;
}

void ParticleSystem::setDispersion(sf::Angle dispersion)
{
	m_dispersion = dispersion;
}

void ParticleSystem::setVelocity(float velocity)
{
	m_velocity = fabs(velocity);
}

void ParticleSystem::setRespawnRate(float rate) 
{
	m_rate = fabs(rate);
}

void ParticleSystem::setRespawnArea(const sf::Vector2f& area)
{
	m_respawn_area = area;
}

void ParticleSystem::setLifeTime(float lifetime)
{
	m_lifetime_max = fabs(lifetime);
}

void ParticleSystem::setEmitted(bool emitted)
{
	m_is_emitted = emitted;
}

void ParticleSystem::setAttenuated(bool attenuation)
{
	m_is_attenuated = attenuation;
}

void ParticleSystem::setScalingMode(ScalingMode mode)
{
	m_scaling_mode = mode;
}

void ParticleSystem::init(std::size_t amount)
{
	m_amount = amount;

	m_particles.resize(amount, Particle());
	m_vertices.resize(amount * 4, sf::Vertex());

	for (size_t i = 0; i < amount; ++i)
	{
		sf::Vertex* quad = &m_vertices[i * 4];

		quad[0].texCoords = sf::Vector2f(0, 0);
		quad[1].texCoords = sf::Vector2f(m_particle_size.x, 0);
		quad[2].texCoords = sf::Vector2f(m_particle_size.x, m_particle_size.y);
		quad[3].texCoords = sf::Vector2f(0, m_particle_size.y);

		sf::Vector2f offset = m_emitter - m_particle_size * 0.5f; // Center of the quadrant

		quad[0].position = offset;
		quad[1].position = sf::Vector2f(offset.x + m_particle_size.x, offset.y);
		quad[2].position = sf::Vector2f(offset.x + m_particle_size.x, offset.y + m_particle_size.y);
		quad[3].position = sf::Vector2f(offset.x,                     offset.y + m_particle_size.y);
	}
}

void ParticleSystem::update(float dt)
{
	if (m_is_emitted)	
		m_timer += m_rate * dt;

	while (m_timer > 1.0f)
	{
		m_timer -= 1.0f;
		respawnParticle(findUnusedParticle());
	}

	for (std::size_t i = 0; i < m_amount; ++i)
	{
		if (m_particles[i].lifetime > 0.0f)
		{
			sf::Vertex* quad   = &m_vertices[i * 4];
			Particle& particle = m_particles[i];

			sf::Vector2f offset = particle.velocity * dt;

			quad[0].position += offset;
			quad[1].position += offset;
			quad[2].position += offset;
			quad[3].position += offset;

			float ratio = particle.lifetime / m_lifetime_max;

			if (m_scaling_mode != ScalingMode::Off)
			{
				sf::Vector2f position = quad[0].position;

				sf::Vector2f scale = m_scaling_mode == ScalingMode::Decreasing ?
					m_particle_size * ratio :
					m_particle_size + (m_particle_size - m_particle_size * ratio);

				quad[1].position.x = position.x + scale.x;
				quad[2].position   = position   + scale;
				quad[3].position.y = position.y + scale.y;
			}		
			
			if(m_is_attenuated)
			{
				sf::Uint8 opacity = ratio * 255;

				quad[0].color.a = opacity;
				quad[1].color.a = opacity;
				quad[2].color.a = opacity;
				quad[3].color.a = opacity;
			}					
		}
		m_particles[i].lifetime -= dt;
	}
}

// Getters

const sf::RenderStates& ParticleSystem::getStates() const
{
	return m_states;
}

sf::Color ParticleSystem::getColor() const
{
	if (!m_vertices.empty())
		return m_vertices[0].color;

	return sf::Color::White;
}

const sf::Vector2f& ParticleSystem::getParticleSize() const
{
	return m_particle_size;
}

const sf::Vector2f& ParticleSystem::getEmitter() const
{
	return m_emitter;
}

sf::Angle ParticleSystem::getDirection() const
{
	return m_direction;
}

sf::Angle ParticleSystem::getDispersion() const
{
	return m_dispersion;
}

float ParticleSystem::getVelocity() const
{
	return m_velocity;
}

float ParticleSystem::getRespawnRate() const
{
	return m_rate;
}

const sf::Vector2f& ParticleSystem::getRespawnArea() const
{
	return m_respawn_area;
}

float ParticleSystem::getLifeTime() const
{
	return m_lifetime_max;
}

bool ParticleSystem::isEmitted() const
{
	return m_is_emitted;
}

bool ParticleSystem::isAttenuated() const
{
	return m_is_attenuated;
}

ParticleSystem::ScalingMode ParticleSystem::getScalingMode() const
{
	return m_scaling_mode;
}

void ParticleSystem::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	for (size_t i = 0; i < m_amount; ++i)
		if (m_particles[i].lifetime > 0.0f)
			target.draw(&m_vertices[i * 4], 4, sf::TriangleFan, m_states);
}

std::size_t ParticleSystem::findUnusedParticle()
{
	for (std::size_t i = m_last_used_particle; i < m_amount; ++i)
		if (m_particles[i].lifetime < 0.0f)
		{
			m_last_used_particle = i;
			return i;
		}

	for (std::size_t i = 0; i < m_last_used_particle; ++i)
		if (m_particles[i].lifetime < 0.0f)
		{
			m_last_used_particle = i;
			return i;
		}
			
	m_last_used_particle = 0;

	return m_last_used_particle;
}

constexpr float inv_rand_max = 1.0f / RAND_MAX;

float frand(float min, float max)
{
	float fval = static_cast<float>(rand());

	return (fval * inv_rand_max * (max - min) + min);
}

float frand(float bound)
{
	return frand(-bound, bound);
}

sf::Vector2f rand2f(const sf::Vector2f& factors)
{
	return sf::Vector2f(frand(factors.x), frand(factors.y));
}

void ParticleSystem::respawnParticle(std::size_t index)
{
	Particle& particle = m_particles[index];

	float half_disp = (m_dispersion * 0.5f).asDegrees();
	float random = frand(-half_disp, half_disp);
	float angle = (m_direction + sf::degrees(random)).asRadians();

	particle.velocity.x = std::cos(angle) * m_velocity;
	particle.velocity.y = std::sin(angle) * m_velocity;

	particle.lifetime = frand(0, m_lifetime_max) + 1.0f; 

	sf::Vector2f respawn_point = rand2f(m_respawn_area);
	sf::Vector2f offset = m_emitter - m_particle_size * 0.5f + respawn_point; 

	sf::Vertex* quad = &m_vertices[index * 4];

	quad[0].position = offset;
	quad[1].position = sf::Vector2f(offset.x + m_particle_size.x, offset.y);
	quad[2].position = sf::Vector2f(offset.x + m_particle_size.x, offset.y + m_particle_size.y);
	quad[3].position = sf::Vector2f(offset.x,                     offset.y + m_particle_size.y);
}
