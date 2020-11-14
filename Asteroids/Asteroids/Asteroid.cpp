#include "Asteroid.h"

using namespace sf;

Asteroid::Asteroid(sf::Vector2f position, float size)
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

    velocity.x = rand() % 75;
    if (rand() % 2 == 0)
    {
        velocity.x = -velocity.x;
    }

    velocity.y = rand() % 75;
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

void Asteroid::Update(float deltatime)
{
    asteroidShape.rotate(rotateSpeed * deltatime);

    Vector2f position = asteroidShape.getPosition();
    position += velocity * deltatime;

    if (position.x <= 0.0f)
    {
        velocity.x = -velocity.x;
        position.x = 0.f;
    }
    else if (position.x + 20 >= 1280)
    {
        velocity.x = -velocity.x;
        position.x = 1280 - 20;
    }

    if (position.y <= 0.f)
    {
        velocity.y = -velocity.y;
        position.y = 0.f;
    }
    else if (position.y + 20 >= 720)
    {
        velocity.y = -velocity.y;
        position.y = 720 - 20;
    }

    asteroidShape.setPosition(position);
}

void Asteroid::Draw(sf::RenderWindow& renderWindow)
{
    renderWindow.draw(asteroidShape);
}