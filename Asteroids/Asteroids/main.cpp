#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Bullet.h"
#include "SpaceShip.h"
#include "Asteroid.h"
#include "AsteroidsSpawner.h"
#include "ParticleSystem.h"

using namespace sf;
using namespace std;

constexpr unsigned int WindowWidth = 1280;
constexpr unsigned int WindowHeight = 720;

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(WindowWidth, WindowHeight), "Asteroids");
    window.setKeyRepeatEnabled(false);

    sf::Music music;
    // Open it from an audio file
    if (!music.openFromFile("music.ogg"))
    {
        // error...
    }

    music.play();

    SpaceShip spaceship(Vector2f(WindowWidth / 2, WindowHeight / 2));
    vector<Bullet> bullets;
    vector<Asteroid> asteroids;

    AsteroidsSpawner asteroidsSpawner;

    // Asteroid TEST
    for (int i = 1; i < 3; ++i)
    {
        for (int j = 1; j < 9; ++j)
        {
            Asteroid asteroid(Vector2f(j * 150, i * 160), (rand() % 300 + 50) * 0.01f);

            asteroids.push_back(asteroid);
        }
    }
    //

    Clock rootClock;

    ParticleSystem particles(1000, false);

    while (window.isOpen() == true)
    {
        sf::Time elapsed = rootClock.restart();
        float deltaTime = elapsed.asSeconds();

        // ===== Event =====
        Event event;
        while (window.pollEvent(event) == true)
        {
            if (event.type == Event::Closed)
            {
                window.close();
                break;
            }

            spaceship.ProcessEvent(event);
        }

        // ===== Update =====

        asteroidsSpawner.Update(deltaTime, asteroids);

        spaceship.Update(deltaTime, bullets);

        for (int i = 0; i < asteroids.size(); i++)
        {
            asteroids[i].Update(deltaTime, asteroids);
        }

        // Move all bullets
        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].Move(deltaTime);
            if (bullets[i].Collision(asteroids) == true)
            {
                bullets.erase(bullets.begin() + i);
                --i;
            }
        }

        spaceship.Collision(bullets, asteroids);
        sf::Vector2i position = sf::Vector2i(spaceship.shape.getPosition().x, spaceship.shape.getPosition().y);
        particles.setEmitter(window.mapPixelToCoords(position));
        particles.update(elapsed);

        // ===== Render =====
        window.clear(Color::Black);
        
        spaceship.Draw(window);

        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].Draw(window);
        }

        for (int i = 0; i < asteroids.size(); i++)
        {
            asteroids[i].Draw(window);
        }

        window.draw(particles);

        window.display();
    }

	return 0;
}
