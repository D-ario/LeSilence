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
		bool Move(float& deltaTime);
		bool Collision(std::vector<Asteroid>& asteroids, int& currentScore);

	public:
		sf::Vector2f velocity;
		sf::CircleShape circle;

	private:
		sf::Vector2f position;
		short countCollisionBullet = 0;
		static constexpr short maxCollisionBullet = 3;

};

#endif