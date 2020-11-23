#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

#include "SpaceShip.h"

class Enemy
{
public:

	Enemy(sf::Vector2f position);

	void Update(float deltatime, const SpaceShip& spaceship);
	void Draw(sf::RenderWindow& renderWindow);

public:
	sf::ConvexShape enemyShape;

private:
	sf::Vector2f velocity;

	float forwardSpeed = 0.2f;
	float decelerationRate = 2.0f;
};

#endif
