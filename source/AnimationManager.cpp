#include "AnimationManager.hpp"

AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager()
{
	release();
}

void AnimationManager::create(const std::string& id, const sf::Texture* texture, int duration, float rate)
{
	std::unique_ptr<std::vector<sf::IntRect>> frames;
	frames->reserve(duration);

	auto tex_size = texture->getSize();
	int frame_width = tex_size.x / duration;

	for (int i = 0; i < duration; i++)
		frames->emplace_back(i * frame_width, 0, frame_width, tex_size.y);

	Animator a(frames.get(), rate);
	m_frames.push_back(std::move(frames));
	m_animators.emplace(std::move(id), a);
}

void AnimationManager::create(const std::string& id, const sf::Texture* texture, int rows, int columns, float rate)
{
	std::unique_ptr<std::vector<sf::IntRect>> frames;
	frames->reserve(columns * rows);

	auto tex_size = texture->getSize();
	int frame_width = tex_size.x / columns;
	int frame_height = tex_size.y / rows;

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
			frames->emplace_back(x * frame_width, y * frame_height, frame_width, frame_height);

	Animator a(frames.get(), rate);
	m_frames.push_back(std::move(frames));
	m_animators.emplace(std::move(id), a);
}

Animator AnimationManager::get(const std::string& id) const
{
	if (auto found = m_animators.find(id); found != m_animators.end())
		return found->second;

	return Animator();
}

void AnimationManager::release()
{
	m_frames.clear();
	m_animators.clear();
}
