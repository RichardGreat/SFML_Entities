#pragma once

#include <SFML/Graphics.hpp>

#include <string_view>
#include <vector>
#include <map>

// Brief:
// 
// auto frames = AnimationManager::get("puppy_walk");
// float frames_per_sec = 12;
// 
// Animator animator(frames, frames_per_sec);
// 
// ..
// 
// Play it!
//

class AnimationManager
{
public:
	~AnimationManager() = default;

	// Класс является синглтоном с быстрым и удобным доступом из любой точки приложения
	static const std::vector<sf::IntRect>* get(const std::string_view id);

private:
	AnimationManager();

	// Создаёт анимацию из кадров, расположенных на текстуре последовательно
	// Параметры: название текстуры, количество кадров
	void createAnimation(const std::string_view title, int duration);

	// Создаёт анимацию из кадров, расположенных на текстуре таблицей
	// Параметры: название текстуры, количество кадров в колонке и строке
	void createAnimation(const std::string_view title, int columns, int rows);

	std::map<std::string_view, std::vector<sf::IntRect>> m_storage;
};
