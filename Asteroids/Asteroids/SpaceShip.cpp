#include "SpaceShip.h"
#include "Bullet.h"
#include "Asteroid.h"

#include <iostream>

using namespace sf;
using namespace std;

SpaceShip::SpaceShip(Vector2f position)
{
    shape.setOrigin(shape.getScale().x / 2, shape.getScale().y / 2);
    shape.setPointCount(3);
    shape.setPoint(0, Vector2f(10.0f, 15.0f));
    shape.setPoint(1, Vector2f(-10.0f, 15.0f));
    shape.setPoint(2, Vector2f(0.0f, -15.0f));
    shape.setFillColor(Color::Black);
    shape.setOutlineColor(Color::White);
    shape.setOutlineThickness(2.0f);

    shape.setPosition(position);
}

void SpaceShip::ProcessEvent(const Event& event)
{
    if (event.type == Event::KeyPressed)
    {
        if (event.key.code == Keyboard::Up)
        {
            forward = true;
        }
        else if (event.key.code == Keyboard::Left)
        {
            turnFactor -= 1.0f;
        }
        else if (event.key.code == Keyboard::Right)
        {
            turnFactor += 1.0f;
        }
        else if (event.key.code == Keyboard::Space)
        {
            fire = true;
        }
    }
    else if (event.type == Event::KeyReleased)
    {
        if (event.key.code == Keyboard::Up)
        {
            forward = false;
        }
        else if (event.key.code == Keyboard::Left)
        {
            turnFactor += 1.0f;
        }
        else if (event.key.code == Keyboard::Right)
        {
            turnFactor -= 1.0f;
        }
        else if (event.key.code == Keyboard::Space)
        {
            fire = false;
        }
    }
}

void SpaceShip::Update(float deltatime, vector<Bullet>& bullets)
{
    elapsedTimeSinceLastFire += deltatime;

    // Apply rotation (related to TurnFactor)
    if (turnFactor != 0.0f)
    {
        shape.setRotation(shape.getRotation() + turnFactor * turnSpeed * deltatime);
    }

    // If Forward input is pressed -> increase the velocity
    if (forward == true)
    {
        Vector2f forwardDirection(0.0f, -1.0f);

        // Build Transform with the current spaceship orientation
        Transform orientation;
        orientation.rotate(shape.getRotation());

        // Rotate forwardDirection
        forwardDirection = orientation * forwardDirection;

        // Apply to velocity
        velocity += forwardDirection * forwardSpeed * deltatime;
    }

    // Deceleration
    velocity -= velocity * decelerationRate * deltatime;

    // Modify the spaceship position related to the velocity
    Vector2f newPosition = shape.getPosition();
    newPosition += velocity;
    shape.setPosition(newPosition);

    // Fire
    if (fire == true && elapsedTimeSinceLastFire >= fireRate)
    {
        Transform orientation;
        orientation.rotate(shape.getRotation());

        Vector2f forwardDirection(0.0f, -1.0f);
        forwardDirection = orientation * forwardDirection;

        Vector2f position = shape.getPosition() + orientation * Vector2f(0.f, -40.f);

        Bullet bullet(position, forwardDirection, 150.f);
        bullets.push_back(bullet);

        elapsedTimeSinceLastFire = 0.0f;
    }

    // Clip and warp spaceship to border
    Vector2f position = shape.getPosition();
    if (position.x > 1280)
    {
        position.x -= 1280;
    }
    else if (position.x < 0)
    {
        position.x += 1280;
    }
    if (position.y > 720)
    {
        position.y -= 720;
    }
    else if (position.y < 0)
    {
        position.y += 720;
    }
    shape.setPosition(position);
}

void SpaceShip::Draw(sf::RenderWindow& renderWindow)
{
    // Mirroring draw (border)

    FloatRect bounds = shape.getGlobalBounds();

    if (bounds.top < 0)
    {
        Vector2f realPosition = shape.getPosition();
        shape.setPosition(Vector2f(realPosition.x, 720 + realPosition.y));
        renderWindow.draw(shape);
        shape.setPosition(realPosition);
    }
    else if (bounds.top + bounds.height > 720)
    {
        Vector2f realPosition = shape.getPosition();
        shape.setPosition(Vector2f(realPosition.x, realPosition.y - 720));
        renderWindow.draw(shape);
        shape.setPosition(realPosition);
    }
    if (bounds.left < 0)
    {
        Vector2f realPosition = shape.getPosition();
        shape.setPosition(Vector2f(1280 + realPosition.x, realPosition.y));
        renderWindow.draw(shape);
        shape.setPosition(realPosition);
    }
    else if (bounds.left + bounds.width > 1280)
    {
        Vector2f realPosition = shape.getPosition();
        shape.setPosition(Vector2f(realPosition.x - 1280, realPosition.y));
        renderWindow.draw(shape);
        shape.setPosition(realPosition);
    }

    renderWindow.draw(shape);
}

void SpaceShip::Collision(std::vector<Bullet>& bullets, std::vector<Asteroid>& asteroids)
{
    if (invincibility)
        return;

    FloatRect shapeBounds = shape.getGlobalBounds();
    shapeBounds.top += shapeBounds.height * 0.25f;
    shapeBounds.height *= 0.5f;
    shapeBounds.left += shapeBounds.width * 0.25f;
    shapeBounds.width *= 0.5f;

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
            cout << "Colision Asteroid" << endl;
            // Lose life
            //invincibility = true;
            asteroids.erase(asteroids.begin() + i);
            break;
        }
    }

    for (size_t i = 0; i < bullets.size(); i++)
    {
        Bullet& other = bullets[i];

        FloatRect otherBounds = other.circle.getGlobalBounds();

        if (shapeBounds.intersects(otherBounds))
        {
            cout << "Colision Bullet" << endl;
            // Lose life
            //invincibility = true;
            bullets.erase(bullets.begin() + i);
            break;
        }
    }
}