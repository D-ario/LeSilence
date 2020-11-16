#ifndef _BULLET_H_
#define _BULLET_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class Asteroid;

class Bullet
{
	public:
		Bullet(sf::Vector2f _position, sf::Vector2f _direction, float _speed);
		~Bullet();

		void Draw(sf::RenderWindow& window);
		void Move(float& deltaTime);
		void Collision(std::vector<Asteroid>& asteroids);

	public:
		sf::Vector2f velocity;
		sf::CircleShape circle;

	private:
		sf::Vector2f position;

};

#endif