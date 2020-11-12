
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

constexpr float WindowWidth = 1280.0f;
constexpr float WindowHeight = 720.0f;
constexpr float TurnSpeed = 180.0f;
constexpr float ForwardSpeed = 0.2f;
constexpr float DecelerationRate = 2.0f;
constexpr float FireRate = 1.0f / 5.0f;

int main()
{
    RenderWindow window(VideoMode(WindowWidth, WindowHeight), "Asteroids");

    window.setKeyRepeatEnabled(false);

    ConvexShape spaceship;
    spaceship.setPointCount(3);
    spaceship.setPoint(0, Vector2f(10.0f, 15.0f));
    spaceship.setPoint(1, Vector2f(-10.0f, 15.0f));
    spaceship.setPoint(2, Vector2f(0.0f, -15.0f));
    spaceship.setFillColor(Color::Black);
    spaceship.setOutlineColor(Color::White);
    spaceship.setOutlineThickness(2.0f);

    spaceship.setPosition(Vector2f(WindowWidth * 0.5f, WindowHeight * 0.5f));

    Clock rootClock;
    Clock fireClock;

    float turnFactor = 0.0f;
    bool forward = false;
    Vector2f velocity;
    bool fire = false;
    float elapsedTimeSinceLastFire = 0.0f;

    while (window.isOpen() == true)
    {
        float deltaTime = rootClock.restart().asSeconds();
        elapsedTimeSinceLastFire += deltaTime;

        // ===== Event =====
        Event event;
        while (window.pollEvent(event) == true)
        {
            if (event.type == Event::Closed)
            {
                window.close();
                break;
            }
            
            else if (event.type == Event::KeyPressed)
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

        // ===== Update =====

        // Apply rotation (related to TurnFactor)
        if (turnFactor != 0.0f)
        {
            spaceship.setRotation(spaceship.getRotation() + turnFactor * TurnSpeed * deltaTime);
        }

        // If Forward input is pressed -> increase the velocity
        if (forward == true)
        {
            Vector2f forwardDirection(0.0f, -1.0f);

            // Build Transform with the current spaceship orientation
            Transform orientation;
            orientation.rotate(spaceship.getRotation());

            // Rotate forwardDirection
            forwardDirection = orientation * forwardDirection;

            // Apply to velocity
            velocity += forwardDirection * ForwardSpeed * deltaTime;
        }

        // Deceleration
        velocity -= velocity * DecelerationRate * deltaTime;

        // Modify the spaceship position related to the velocity
        Vector2f newPosition = spaceship.getPosition();
        newPosition += velocity;
        spaceship.setPosition(newPosition);

        // Fire
        if (fire == true && elapsedTimeSinceLastFire >= FireRate)
        {
            cout << fire;
            elapsedTimeSinceLastFire = 0.0f;
        }

        // Clip and warp spaceship to border
        Vector2f position = spaceship.getPosition();
        if (position.x > WindowWidth)
        {
            position.x -= WindowWidth;
        }
        else if (position.x < 0)
        {
            position.x += WindowWidth;
        }
        if (position.y > WindowHeight)
        {
            position.y -= WindowHeight;
        }
        else if (position.y < 0)
        {
            position.y += WindowHeight;
        }
        spaceship.setPosition(position);

        // ===== Render =====
        window.clear(Color::Black);

        window.draw(spaceship);

        window.display();
    }

	return 0;
}
