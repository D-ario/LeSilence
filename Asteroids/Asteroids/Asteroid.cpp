#include "Asteroid.h"

#include <iostream>

using namespace sf;

Asteroid::Asteroid(sf::Vector2f position, float size) : size(size)
{
    asteroidShape.setPointCount(10);
    asteroidShape.setPoint(0, Vector2f(0.0f, -15.0f) * size);
    asteroidShape.setPoint(1, RandomizePoint(Vector2f(6.0f, -10.0f)) * size);
    asteroidShape.setPoint(2, Vector2f(12.0f, -4.0f) * size);
    asteroidShape.setPoint(3, RandomizePoint(Vector2f(10.0f, 4.0f)) * size);
    asteroidShape.setPoint(4, Vector2f(8.0f, 12.0f) * size);
    asteroidShape.setPoint(5, RandomizePoint(Vector2f(0.0f, 12.0f)) * size);
    asteroidShape.setPoint(6, Vector2f(-8.0f, 12.0f) * size);
    asteroidShape.setPoint(7, RandomizePoint(Vector2f(-10.0f, 4.0f)) * size);
    asteroidShape.setPoint(8, Vector2f(-12.0f, -4.0f) * size);
    asteroidShape.setPoint(9, RandomizePoint(Vector2f(-6.0f, -10.0f)) * size);
    asteroidShape.setFillColor(Color::Black);
    asteroidShape.setOutlineColor(Color::White);
    asteroidShape.setOutlineThickness(2.0f);

    asteroidShape.setPosition(position);

    rotateSpeed = rand() % 75;
    if (rand() % 2 == 0)
    {
        rotateSpeed = -rotateSpeed;
    }

    velocity.x = rand() % 50 + 25;
    if (rand() % 2 == 0)
    {
        velocity.x = -velocity.x;
    }

    velocity.y = rand() % 75 + 25;
       if (rand() % 2 == 0)
    {
        velocity.y = -velocity.y;
    }
}

Vector2f Asteroid::RandomizePoint(const Vector2f& point)
{
    int randX = rand() % 5;
    if (rand() % 2 == 0)
    {
        randX = -randX;
    }

    int randY = rand() % 5;
    if (rand() % 2 == 0)
    {
        randY = -randY;
    }

    return sf::Vector2f(point.x + randX, point.y + randY);
}

void Asteroid::Update(float deltatime, const std::vector<Asteroid>& asteroids)
{
    asteroidShape.rotate(rotateSpeed * deltatime);

    Vector2f position = asteroidShape.getPosition();
    position += velocity * deltatime;
    asteroidShape.setPosition(position);

    // Border Bounce

    FloatRect asteroidShapeBounds = asteroidShape.getGlobalBounds();

    if (velocity.x < 0 && asteroidShapeBounds.left < 0.0f)
    {
        velocity.x = -velocity.x;
    }
    else if (velocity.x > 0 && asteroidShapeBounds.left + asteroidShapeBounds.width > 1280)
    {
        velocity.x = -velocity.x;
    }

    if (velocity.y < 0 && asteroidShapeBounds.top < 0.0f)
    {
        velocity.y = -velocity.y;
    }
    else if (velocity.y > 0 && asteroidShapeBounds.top + asteroidShapeBounds.height > 720)
    {
        velocity.y = -velocity.y;
    }

    // Bounce each other 

    asteroidShapeBounds.top += asteroidShapeBounds.height * 0.25f;
    asteroidShapeBounds.height *= 0.5f;
    asteroidShapeBounds.left += asteroidShapeBounds.width * 0.25f;
    asteroidShapeBounds.width *= 0.5f;

    for (size_t i = 0; i < asteroids.size(); i++)
    {
        const Asteroid& other = asteroids[i];

        if (this == &other)
        {
            continue;
        }

        FloatRect otherBounds = other.asteroidShape.getGlobalBounds();
        
        otherBounds.top += otherBounds.height * 0.25f;
        otherBounds.height *= 0.5f;
        otherBounds.left += otherBounds.width * 0.25f;
        otherBounds.width *= 0.5f;

        if (asteroidShapeBounds.intersects(otherBounds) == true)
        {
            if (velocity.x > 0 && asteroidShape.getPosition().x < other.asteroidShape.getPosition().x)
            {
                velocity.x = -velocity.x;
            }
            if (velocity.x < 0 && asteroidShape.getPosition().x > other.asteroidShape.getPosition().x)
            {
                velocity.x = -velocity.x;
            }
            if (velocity.y > 0 && asteroidShape.getPosition().y < other.asteroidShape.getPosition().y)
            {
                velocity.y = -velocity.y;
            }
            if (velocity.y < 0 && asteroidShape.getPosition().y > other.asteroidShape.getPosition().y)
            {
                velocity.y = -velocity.y;
            }
        }
    }
}

int Asteroid::Death(std::vector<Asteroid>& asteroids)
{
    if (size > 1.0f)
    {
        Asteroid asteroid(asteroidShape.getPosition(), size * 0.5f);
        asteroids.push_back(asteroid);

        Asteroid asteroid2(asteroidShape.getPosition(), size * 0.5f);
        asteroids.push_back(asteroid2);
    }

    return 10;
}

void Asteroid::Draw(sf::RenderWindow& renderWindow)
{
    renderWindow.draw(asteroidShape);
}
