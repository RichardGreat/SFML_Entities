#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

// Легковесный класс для воспроизведения линейной анимации
// Для работы необходим указатель на массив кадров, загружаемый отдельно
// во избежание излишних накладных расходов на динамическое выделение памяти,
// и скорость анимации, измеряемой в кадр/сек

// Brief:
// 
// std::vector<sf::IntRect> frames;
// const float FPS = 48; // 48 frames per sec
//
// sf::Clock clock;
//
// Animator animator(&frames, FPS);
//
// // Some code...
//
// sf::Sprite sprite(some_texture);
// float dt = clock.restart().asSeconds(); // delta time
//
// animator.update(sprite, dt); // Look, it's nice, isn't it?

class Animator
{
public:
    Animator();
    Animator(const std::vector<sf::IntRect>* frames, float rate);
    ~Animator() = default;

    void setFrames(const std::vector<sf::IntRect>* frames);
    void setRate(float fps);
    void update(sf::Sprite& sprite, float dt /* delta time */);
    void reset();

    const std::vector<sf::IntRect>* getFrames() const;
    float                           getRate()   const;
    bool                            isOver()    const; // End of the current cycle
                                                      
private:                                              
    const std::vector<sf::IntRect>* m_frames;          // frames from a some storage
    float                           m_current_frame;   // num of current frame
    float                           m_fps;             // frames per second
};
