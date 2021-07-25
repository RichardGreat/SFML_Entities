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

//                                                               Тестовый код:
//
// sf::VideoMode screen(1200, 800); // Параметры экрана
// 
// 
//int main()
//{
//    srand(static_cast<unsigned>(time(0)));
//
//    sf::RenderWindow window(screen, "Simple shaders!");
//    window.setFramerateLimit(60);
//
//    sf::Texture texture;
//    texture.loadFromFile("path/texture.png");
//    texture.setSmooth(true);
// 
//    // Проверяем поддержку шейдера
//    sf::Shader shader;
//
//    if (!sf::Shader::isGeometryAvailable())
//        return EXIT_FAILURE;
//
//    if (!shader.loadFromFile("path/shader.vert", "path/shader.geom", "path/shader.frag"))
//        return EXIT_FAILURE;
// 
//    // Устанавливаем глобальные переменные
//    shader.setUniform("resolution", sf::Vector2f((float)screen.width, (float)screen.height));
//    shader.setUniform("size", sf::Vector2f(50, 50));
//    shader.setUniform("texture", sf::Shader::CurrentTexture);
//
//    ParticleSystem ps(&texture, &shader, 100);
//
//    sf::Clock clock;
//    sf::Time delta_time;
//
//    float dir = 0;  // Направление в градусах
//    float disp = 0; // Дисперсия в градусах
//
//    ps.setVelocity(500);               // Скорость в пикс/сек
//    ps.setMaxLifeTime(sf::seconds(3)); // Максимальная продолжительность жизни частицы
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
//        // Задаём точку эмисии
//        sf::Vector2i mouse = sf::Mouse::getPosition(window);
//        auto pos = window.mapPixelToCoords(mouse);
//        ps.setEmitter(window.mapPixelToCoords(mouse));
//       
//        // Если нажата эта клавиша, вращаем эмиссию по часовой стрелке
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//        {
//            dir -= 5;
//            ps.setDirection(dir);
//        }
//     
//        // Если нажата эта клавиша, увеличиваем дисперсию
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//        {
//            disp++;
//            ps.setDispersion(disp);
//        }
// 
//       ps.update(delta_time);
//
//       window.clear();
//       window.draw(ps);
//       window.display();
//    }
//    return EXIT_SUCCESS;
//}
