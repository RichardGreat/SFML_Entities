#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

extern sf::VideoMode screen;

class ParticleSystem :
    public sf::Drawable,
    private sf::NonCopyable
{
public:
    ParticleSystem(const sf::Texture* texture, sf::Shader* shader, std::size_t amount);
    ~ParticleSystem() = default;

    // Устанавливает точку эмиссии
    void setEmitter(const sf::Vector2f& position);

    // Устанавливает направление эмиссии( параметр: угол в градусах )
    void setDirection(float direction);

    // Устанавливает дисперсию( ширину сектора "распыления") частиц( параметр: угол в градусах )
    void setDispersion(float dispersion);

    // Устанавливает скорость эмиссии( параметр: скорость в пикселях в секунду )
    void setVelocity(float velocity);

    // Устанавливает максимальное время жизненного цикла частицы( параметр: значение в объекте sf::Time )
    void setMaxLifeTime(sf::Time lifetime);

    // Getters
    const sf::Vector2f& getEmitter()     const;
    float               getDirection()   const;
    float               getDispersion()  const;
    float               getVelocity()    const;
    const sf::Time&     getMaxLifeTime() const;

    void update(sf::Time delta_time);

private:
    // Перевод экранных координат точки эмиссии в координаты нормализованного устройства (NDC)
    sf::Vector2f to_ndc(const sf::Vector2f& pos);

    // Обновление отдельно взятой частицы по истечении её жизненного цикла
    void resetParticle(std::size_t index);

    // Рендеринг массива частиц
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    struct Particle
    {
        sf::Vector2f m_velocity;
        sf::Time     m_lifetime;
    };

    sf::Vector2f          m_emitter;
    float                 m_direction;
    float                 m_dispersion;
    float                 m_velocity;

    const sf::Texture*    m_texture;
    sf::Shader*           m_shader;
    sf::VertexArray       m_vertices;
    std::vector<Particle> m_particles;
    sf::Time              m_max_lifetime;
};
