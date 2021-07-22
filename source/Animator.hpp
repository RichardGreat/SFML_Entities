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
Animator::~Animator() = default;

void Animator::update(sf::Time delta)
{
	m_elapsed_time += delta;

	if (m_elapsed_time >= m_delay)
	{
		m_current_frame++;
		m_elapsed_time = sf::Time::Zero;

		if (m_current_frame == m_last_frame)
		{
			m_cycle_counter++;
			m_current_frame = 0;
		}
		m_frame.left = m_current_frame * m_frame.width;
		m_sprite->setTextureRect(m_frame);
	}
}

const std::size_t Animator::count() const
{
	return m_cycle_counter > 0;
}
