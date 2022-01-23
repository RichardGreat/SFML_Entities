#include "Animator.hpp"

template<class Drawable>
Animator<Drawable>::Animator() :
    m_frames(nullptr), m_current_frame(0.0f), m_fps(0.0f) {}

template<class Drawable>
Animator<Drawable>::Animator(const std::vector<sf::IntRect>& frames, float rate) :
    m_frames(nullptr), m_current_frame(0.0f), m_fps(0.0f)
{
    setFrames(frames);
    setRate(rate);
}

template<class Drawable>
void Animator<Drawable>::setFrames(const std::vector<sf::IntRect>& frames)
{
    m_frames = &frames;
}

template<class Drawable>
void Animator<Drawable>::setRate(float fps)
{
    m_fps = std::fabs(fps);
}

template<class Drawable>
void Animator<Drawable>::update(Drawable& object, float dt)
{
    if (m_frames)
    {
        m_current_frame += dt * m_fps;

        if (isOver())
            restart();

        object.setTextureRect((*m_frames)[std::size_t(m_current_frame)]);
    }
}

template<class Drawable>
void Animator<Drawable>::restart()
{
    m_current_frame = 0;
}

template<class Drawable>
const std::vector<sf::IntRect>* Animator<Drawable>::getFrames() const
{
    return m_frames;
}

template<class Drawable>
float Animator<Drawable>::getRate() const
{
    return m_fps;
}

template<class Drawable>
bool Animator<Drawable>::isOver() const
{
    return m_current_frame + m_fps >= m_frames->size();
}
