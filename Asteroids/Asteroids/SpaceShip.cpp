#include "SpaceShip.h"

#include "Bullet.h"

#include <SFML/Graphics.hpp>

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

        Vector2f position = shape.getPosition() + orientation * Vector2f(0.f, -15.f) + Vector2f(0.f, -5.f);

        Bullet bullet(position, forwardDirection, 50.f);
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
    renderWindow.draw(shape);
}
