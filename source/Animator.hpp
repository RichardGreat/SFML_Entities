#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

template<class T>
class Animator
{
	using Frames = std::vector<sf::IntRect>;
public:
	Animator(sf::Texture& texture, std::size_t duration, sf::Time delay);
	Animator(sf::Texture& texture, std::size_t rows, std::size_t columns, sf::Time delay);
	~Animator();

	void set(T& drawable);
	void reset();
	void update(sf::Time delta);
	bool isOver();

private:
	std::size_t m_cycle_counter;
	std::size_t m_current_frame;
	std::size_t m_last_frame;
	sf::Time    m_delay;
	sf::Time    m_elapsed_time;
	T*          m_sprite;
	Frames      m_frames;
};

template<class T>
inline Animator<T>::Animator(sf::Texture& texture, std::size_t duration, sf::Time delay):
	m_cycle_counter(0),
	m_current_frame(0),
	m_last_frame(0),
	m_sprite(nullptr)
{
	m_frames.reserve(duration);

	std::size_t frame_width = texture.getSize().x / duration;
	std::size_t frame_height = texture.getSize().y;

	for (std::size_t i = 0; i < duration; ++i)
		m_frames.push_back(sf::IntRect(i * frame_width, 0, frame_width, frame_height));

	m_last_frame = duration;
	m_delay = delay;
}

template<class T>
inline Animator<T>::Animator(sf::Texture& texture, std::size_t rows, std::size_t columns, sf::Time delay) :
	m_cycle_counter(0),
	m_current_frame(0),
	m_last_frame(0),
	m_sprite(nullptr)
{
	m_frames.reserve(rows * columns);

	std::size_t frame_width = texture.getSize().x / columns;
	std::size_t frame_height = texture.getSize().y / rows;

	for (std::size_t y = 0; y < rows; ++y)
		for (std::size_t x = 0; x < columns; ++x)
			m_frames.push_back(sf::IntRect(frame_width * x, frame_height * y, frame_width, frame_height));

	m_last_frame = rows * columns;
	m_delay = delay;
}

template<class T>
inline Animator<T>::~Animator()
{
	m_frames.clear();
}

template<class T>
inline void Animator<T>::set(T& drawable)
{
	m_sprite = &drawable;
	m_sprite->setTextureRect(m_frames[m_current_frame]);
}

template<class T>
inline void Animator<T>::reset()
{
	m_sprite = nullptr;
	m_cycle_counter = m_current_frame = m_last_frame = 0;
	m_elapsed_time = sf::Time::Zero;
}

template<class T>
inline void Animator<T>::update(sf::Time delta)
{
	if (m_sprite)
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
			m_sprite->setTextureRect(m_frames[m_current_frame]);
		}
	}
}

template<class T>
inline bool Animator<T>::isOver()
{
	return m_cycle_counter > 0;
}
