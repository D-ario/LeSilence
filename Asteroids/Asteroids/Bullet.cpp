#include "Bullet.h"
#include "Asteroid.h"

#include <iostream>

using namespace sf;

Bullet::Bullet(sf::Vector2f _position, sf::Vector2f _direction, float _speed)
{
	position = _position;

	circle.setRadius(2.5f);
	circle.setOrigin(sf::Vector2f(circle.getRadius() , circle.getRadius()));
	circle.setPosition(position);

	velocity = _direction * _speed;
}

Bullet::~Bullet()
{
}

bool Bullet::Move(float& deltaTime)
{
	position += velocity * deltaTime;

	if (position.x <= 0.0f)
	{
		velocity.x = -velocity.x;
		position.x = 0.f;
		countCollisionBullet++;
	}
	else if (position.x + circle.getRadius() >= 1280)
	{
		velocity.x = -velocity.x;
		position.x = 1280 - circle.getRadius();
		countCollisionBullet++;
	}

	if (position.y <= 0.f)
	{
		velocity.y = -velocity.y;
		position.y = 0.f;
		countCollisionBullet++;
	}
	else if (position.y + circle.getRadius() >= 720)
	{
		velocity.y = -velocity.y;
		position.y = 720 - circle.getRadius();
		countCollisionBullet++;
	}
	
	circle.setPosition(position);

	float alpha = 1.0f - ((float)countCollisionBullet / (float)maxCollisionBullet);

	circle.setFillColor(Color(255, 255, 255, alpha * 255));

	return (countCollisionBullet >= maxCollisionBullet);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(circle);
}

bool Bullet::Collision(std::vector<Asteroid>& asteroids, int& currentScore)
{
    FloatRect shapeBounds = circle.getGlobalBounds();

    for (size_t i = 0; i < asteroids.size(); i++)
    {
        Asteroid& other = asteroids[i];

        FloatRect otherBounds = other.asteroidShape.getGlobalBounds();

        otherBounds.top += otherBounds.height * 0.25f;
        otherBounds.height *= 0.5f;
        otherBounds.left += otherBounds.width * 0.25f;
        otherBounds.width *= 0.5f;

        if (shapeBounds.intersects(otherBounds))
        {
			currentScore += asteroids[i].Death(asteroids);
            asteroids.erase(asteroids.begin() + i);

			return true;
        }
    }

	return false;
}
