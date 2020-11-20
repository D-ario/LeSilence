#ifndef _SPACESHIP_H_
#define _SPACESHIP_H_

#include <SFML/Graphics.hpp>
#include <vector>

class Bullet;
class Asteroid;

class SpaceShip
{
	public:
		SpaceShip(sf::Vector2f position);

		void ProcessEvent(const sf::Event& event);
		void Update(float deltatime, std::vector<Bullet>& bullets);
		void Draw(sf::RenderWindow& renderWindow);
		void Collision(std::vector<Bullet>& bullets, std::vector<Asteroid>& asteroids);


	public:
		sf::ConvexShape shape;
		bool forward = false;
		int life = 3;

	private:

		float turnSpeed = 180.0f;
		float forwardSpeed = 0.2f;
		float decelerationRate = 2.0f;
		float fireRate = 1.0f / 5.0f;
		bool invincibility = false;
		float tInvincibility = 0.f;

		float turnFactor = 0.0f;
		sf::Vector2f velocity;
		bool fire = false;
		float elapsedTimeSinceLastFire = 0.0f;
};

#endif
