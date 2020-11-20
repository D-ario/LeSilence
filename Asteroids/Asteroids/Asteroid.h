#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include <SFML/Graphics.hpp>
#include <vector>

class Asteroid
{
	public:

		Asteroid(sf::Vector2f position, float size, int type);

		void Update(float deltatime, const std::vector<Asteroid>& asteroids);
		int Death(std::vector<Asteroid>& asteroids);
		void Draw(sf::RenderWindow& renderWindow);

	public:
		sf::ConvexShape asteroidShape;
		int size;

	private:
		sf::Vector2f RandomizePoint(const sf::Vector2f& point);
		sf::Vector2f velocity;
		float rotateSpeed;
};

#endif
