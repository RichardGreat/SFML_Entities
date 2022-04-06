#include <SFML/Graphics.hpp>

#include <vector>

class ParticleSystem :
	public sf::Drawable
{
public:
	enum ScalingMode :
		std::size_t
	{
		Off = 0,
		Decreasing,		
		Increasing
	};

	ParticleSystem();

	void setTexture(const sf::Texture* texture);
	void setColor(const sf::Color& color);
	void setShader(const sf::Shader* shader);
	void setBlendMode(const sf::BlendMode& blend_mode);

	void setParticleSize(const sf::Vector2f& size);
	void setEmitter(const sf::Vector2f& emitter);
	void setDirection(sf::Angle direction);
	void setDispersion(sf::Angle dispersion);
	void setVelocity(float velocity);
	void setRespawnRate(float rate); // Explanation : setRespawnRate(4) will be respawn 4 particles per second
	void setRespawnArea(const sf::Vector2f& area);
	void setLifeTime(float lifetime);

	void setEmitted(bool emitted);
	void setAttenuated(bool attenuation);
	void setScalingMode(ScalingMode mode);

	void init(std::size_t amount);
	void update(float dt);

	const sf::RenderStates& getStates()       const;
	sf::Color               getColor()        const;
	const sf::Vector2f&     getParticleSize() const;
	const sf::Vector2f&     getEmitter()      const;
	sf::Angle               getDirection()    const;
	sf::Angle               getDispersion()   const;
	float                   getVelocity()     const;
	float                   getRespawnRate()  const;
	const sf::Vector2f&     getRespawnArea()  const;
	float                   getLifeTime()     const;

	bool        isEmitted()      const;
	bool        isAttenuated()   const;
	ScalingMode getScalingMode() const;

private:
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	std::size_t findUnusedParticle();
	void        respawnParticle(std::size_t index);
	
private:
	struct Particle
	{
		sf::Vector2f velocity;
		float        lifetime = 0.0f;
	};

	mutable sf::RenderStates m_states;
	std::vector<sf::Vertex>  m_vertices;
	std::vector<Particle>    m_particles;

	sf::Vector2f m_emitter;
	sf::Vector2f m_respawn_area;
	sf::Vector2f m_particle_size;

	std::size_t m_amount;
	std::size_t m_last_used_particle;

	sf::Angle m_direction;
	sf::Angle m_dispersion;

	float m_velocity;
	float m_lifetime_max;
	float m_rate;
	float m_timer;

	bool m_is_emitted;
	bool m_is_attenuated;

	ScalingMode m_scaling_mode;
};
