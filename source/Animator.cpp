#include "Animation.hpp"

Animator::Animator() :
    m_frames(nullptr), m_current_frame(0), m_fps(0) {}

Animator::Animator(const std::vector<sf::IntRect>* frames, float rate) :
    m_frames(frames), m_current_frame(0), m_fps(rate)
{
}

void Animator::setFrames(const std::vector<sf::IntRect>*frames)
{
    if (!frames || frames->empty())
        return;

    m_frames = frames;
}

void Animator::setRate(float fps)
{
    m_fps = std::fabs(fps);
}

void Animator::update(sf::Sprite& sprite, float dt)
{
    if (m_frames)
    {
        m_current_frame += dt * m_fps;

        if (m_current_frame >= m_frames->size())
            reset();

        sprite.setTextureRect((*m_frames)[std::size_t(m_current_frame)]);
    }
}

void Animator::reset()
{
    m_current_frame = 0;
}

const std::vector<sf::IntRect>* Animator::getFrames() const
{
    return m_frames;
}

float Animator::getRate() const
{
    return m_fps;
}

bool Animator::isOver() const 
{
    return m_current_frame + m_fps >= m_frames->size();
}
