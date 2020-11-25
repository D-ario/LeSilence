#include <iostream>

#include <cmath>

#include "Enemy.h"
#include "Math.h"

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

	enemyShape.setRotation(90.0f);
}

void Enemy::Update(float deltatime, const SpaceShip& spaceship, vector<Bullet>& bullets)
{
	Vector2f forwardDirection(0.0f, 1.0f);

	// Build Transform with the current spaceship orientation
	Transform orientation;
	orientation.rotate(enemyShape.getRotation());

	// Rotate forwardDirection
	forwardDirection = orientation * forwardDirection;

	Vector2f spaceShipDirection = enemyShape.getPosition() - spaceship.shape.getPosition();

	// Dot product to align orientation to spaceship
	float angle = VectorMath::Angle(VectorMath::Normalize(forwardDirection), VectorMath::Normalize(spaceShipDirection));

	if (isnan(angle) == false)
	{
		enemyShape.rotate(angle * deltatime * 1.5f);
	}

	if (abs(angle) < 30.0f)
	{
		velocity += forwardDirection * -forwardSpeed * deltatime;
	}

	// Deceleration
	velocity -= velocity * decelerationRate * deltatime;

    Vector2f position = enemyShape.getPosition();
    position += velocity * deltatime;
    enemyShape.setPosition(position);


	elapsedTimeSinceLastFire += deltatime;
	if (abs(angle) < 5.0f)
	{
		// Fire
		if (elapsedTimeSinceLastFire >= fireRate)
		{
			Transform orientation;
			orientation.rotate(enemyShape.getRotation());

			Vector2f forwardDirection(0.0f, -1.0f);
			forwardDirection = orientation * forwardDirection;

			Vector2f position = enemyShape.getPosition() + orientation * Vector2f(0.f, -40.f);

			Bullet bullet(position, forwardDirection, 200.f + VectorMath::Len(velocity) * 1.2f); // 200 + Current speed
			bullets.push_back(bullet);

			elapsedTimeSinceLastFire = 0.0f;
		}
	}
}

void Enemy::Draw(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(enemyShape);
}

bool Enemy::Collision(std::vector<Bullet>& bullets)
{
	FloatRect shapeBounds = enemyShape.getGlobalBounds();
	shapeBounds.top += shapeBounds.height * 0.25f;
	shapeBounds.height *= 0.5f;
	shapeBounds.left += shapeBounds.width * 0.25f;
	shapeBounds.width *= 0.5f;

	for (size_t i = 0; i < bullets.size(); i++)
	{
		Bullet& other = bullets[i];

		FloatRect otherBounds = other.circle.getGlobalBounds();

		if (shapeBounds.intersects(otherBounds))
		{
			bullets.erase(bullets.begin() + i);
			return true;
		}
	}

	return false;
}
