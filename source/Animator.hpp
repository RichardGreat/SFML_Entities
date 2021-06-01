#pragma once

#include <SFML/Graphics.hpp>

class Animator
{
public:
	Animator(sf::Sprite& sprite, std::size_t duration, sf::Time delay);
	~Animator();

	void update(sf::Time delta);
	const std::size_t count() const;

private:
	std::size_t m_cycle_counter;
	std::size_t m_current_frame;
	std::size_t m_last_frame;
	sf::Time    m_delay;
	sf::Time    m_elapsed_time;
	sf::Sprite* m_sprite;
	sf::IntRect m_frame;
};

Animator::Animator(sf::Sprite& sprite, std::size_t duration, sf::Time delay):
	m_cycle_counter(0),
	m_current_frame(0),
	m_last_frame(duration),
	m_sprite(&sprite)
{
	m_frame = m_sprite->getTextureRect();
	m_frame.width /= duration;
	m_sprite->setTextureRect(m_frame);
	m_delay = delay;
}

Animator::~Animator()
{
}

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
