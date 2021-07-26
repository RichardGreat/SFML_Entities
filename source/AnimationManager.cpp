#include "Resources.hpp"
#include "AnimationManager.hpp"

const std::vector<sf::IntRect>* AnimationManager::get(const std::string_view id)
{
	static AnimationManager animations;

	if (auto found = animations.m_storage.find(id); found != animations.m_storage.end())
		return &found->second;

	return nullptr;
}

AnimationManager::AnimationManager()
{
	createAnimation("puppy_walk", 12);   // Будет создана анимация из 12 кадров
	createAnimation("explosion", 4, 4);  // Будет создана анимация из 16 кадров
}

void AnimationManager::createAnimation(const std::string_view title, int duration)
{
	std::vector<sf::IntRect> frames;
	frames.reserve(duration);

	auto tex_size = get_texture(title)->getSize();
	int frame_width = tex_size.x / duration;

	for (int i = 0; i < duration; i++)
		frames.emplace_back(i * frame_width, 0, frame_width, tex_size.y);

	m_storage.emplace(title, std::move(frames));
}

void AnimationManager::createAnimation(const std::string_view title, int rows, int columns)
{
	std::vector<sf::IntRect> frames;
	frames.reserve(columns * rows);

	auto tex_size = get_texture(title)->getSize();
	int frame_width = tex_size.x / columns;
	int frame_height = tex_size.y / rows;

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
			frames.emplace_back(x * frame_width, y * frame_height, frame_width, frame_height);
		
	m_storage.emplace(title, std::move(frames));
}
