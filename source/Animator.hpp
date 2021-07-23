#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

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
