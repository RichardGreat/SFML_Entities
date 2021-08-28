#pragma once

#include "Animator.hpp"

#include <SFML/Graphics.hpp>

#include <list>
#include <vector>
#include <map>
#include <memory>

// Brief:
// 
// auto texture = get_texture("puppy"); // entire texture
// float frames_per_sec = 12;           // animation speed
// int duration = 4;                    // amount of frames
//
// AnimationManager am();
// am.create("puppy_walk", texture, duration, frames_per_sec);
//
// Animator animator = am.get("puppy_walk");
// 
// ..
// 
// Play it! // Note: More information is available from the Animator.hpp
//

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	// Создаёт анимацию из кадров, расположенных на текстуре последовательно
	// Параметры: идентификатор, указатель на текстуру, количество кадров
	void create(const std::string& id, const sf::Texture* texture, int duration, float rate);
	
	// Создаёт анимацию из кадров, расположенных на текстуре таблицей
	// Параметры: идентификатор, указатель на текстуру, количество кадров в колонке и строке
	void create(const std::string& id, const sf::Texture* texture, int columns, int rows, float rate);
	
	// Возвращает копию объекта Animator по значению. Если искомого экземпляра
	// не было найдено, вернёт объект с нулевыми полями
	Animator get(const std::string& id) const;
	
	// Освобождает все загруженные ресурсы
	void release();

private:
	std::map<std::string, Animator>                      m_animators; // Экземпляры аниматоров
	std::list<std::unique_ptr<std::vector<sf::IntRect>>> m_frames;    // Контейнер с уникальными наборами анимаций
};
