#ifndef _SPACESHIP_H_
#define _SPACESHIP_H_

#include <SFML/Graphics.hpp>
#include <vector>

class Bullet;

class SpaceShip
{
	public:
		SpaceShip(sf::Vector2f position);

		void ProcessEvent(const sf::Event& event);
		void Update(float deltatime, std::vector<Bullet>& bullets);
		void Draw(sf::RenderWindow& renderWindow);

	private:

		float turnSpeed = 180.0f;
		float forwardSpeed = 0.2f;
		float decelerationRate = 2.0f;
		float fireRate = 1.0f / 5.0f;

		sf::ConvexShape shape;

		float turnFactor = 0.0f;
		bool forward = false;
		sf::Vector2f velocity;
		bool fire = false;
		float elapsedTimeSinceLastFire = 0.0f;
};

#endif
