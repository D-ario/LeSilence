#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

#include "SpaceShip.h"
#include "Bullet.h"

class Enemy
{
public:

	Enemy(sf::Vector2f position);

	void Update(float deltatime, const SpaceShip& spaceship, std::vector<Bullet>& bullets);
	void Draw(sf::RenderWindow& renderWindow);
	bool Collision(std::vector<Bullet>& bullets);

public:
	sf::ConvexShape enemyShape;

private:
	sf::Vector2f velocity;

	float forwardSpeed = 200.0f;
	float decelerationRate = 2.0f;

	float fireRate = 1.0f;
	float elapsedTimeSinceLastFire = 0.0f;
};

#endif
