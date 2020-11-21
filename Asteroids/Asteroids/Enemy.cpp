#include <iostream>

#include "Enemy.h"

using namespace sf;
using namespace std;
constexpr float WindowWidth = 1280.0f;
constexpr float WindowHeight = 720.0f;
constexpr float ForwardSpeed = 0.2f;

Enemy::Enemy(sf::Vector2f position)
{
	//def Enemy
	enemyShape.setPointCount(3);
	enemyShape.setPoint(0, Vector2f(10.0f, 15.0f));
	enemyShape.setPoint(1, Vector2f(-10.0f, 15.0f));
	enemyShape.setPoint(2, Vector2f(0.0f, -15.0f));
	enemyShape.setFillColor(Color::Black);
	enemyShape.setOutlineColor(Color::Red);

	enemyShape.setOutlineThickness(2.0f);
	//à redéfinir avec le EnemyManager
	enemyShape.setPosition(position);
}

void Enemy::Update(float deltatime, const SpaceShip& spaceship)
{
	// TODO dot product to align orientation to spaceship

    Vector2f position = enemyShape.getPosition();
    position += velocity * deltatime;
    enemyShape.setPosition(position);
}

void Enemy::Draw(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(enemyShape);
}
