#include <SFML/Graphics.hpp>

#include <vector>

extern sf::VideoMode screen;

class Splash: public sf::Drawable
{
	using Vertices = std::vector<sf::Vertex>;
public:
	Splash(sf::Vector2f start_position, float radius);
	~Splash();
	
	void update();
	bool is_alive() const;
	
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Vertices m_vertices;
	float    m_velocity;
};