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

void Bullet::Move(float& deltaTime)
{
	position += velocity * deltaTime;

	if (position.x <= 0.0f)
	{
		velocity.x = -velocity.x;
		position.x = 0.f;
	}
	else if (position.x + circle.getRadius() >= 1280)
	{
		velocity.x = -velocity.x;
		position.x = 1280 - circle.getRadius();
	}

	if (position.y <= 0.f)
	{
		velocity.y = -velocity.y;
		position.y = 0.f;
	}
	else if (position.y + circle.getRadius() >= 720)
	{
		velocity.y = -velocity.y;
		position.y = 720 - circle.getRadius();
	}

	circle.setPosition(position);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(circle);
}

void Bullet::Collision(std::vector<Asteroid>& asteroids)
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
            asteroids.erase(asteroids.begin() + i);
			delete this;
            break;
        }
    }
}