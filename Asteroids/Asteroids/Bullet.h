#ifndef _BULLET_H_
#define _BULLET_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Bullet
{
	public:
		Bullet(sf::Vector2f _position, sf::Vector2f _direction, float _speed);
		~Bullet();

		sf::Vector2f velocity;

		void Draw(sf::RenderWindow& window);
		void Move(float& deltaTime);

	private:
		
		sf::Vector2f position;
		sf::CircleShape circle;

		
		
};

#endif