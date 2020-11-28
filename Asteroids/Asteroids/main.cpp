#include <iostream>
#include <sstream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Bullet.h"
#include "SpaceShip.h"
#include "Asteroid.h"
#include "AsteroidsSpawner.h"
#include "ParticleSystem.h"
#include "Life.h"
#include "Enemy.h"
#include "EnemySpawner.h"
#include "Gui.h"


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
    music.openFromFile("../../Assets/song/track_01_lightin.ogg");
    music.setVolume(20);
    music.setLoop(true);
    music.play();

    SpaceShip spaceship(Vector2f(WindowWidth / 2, WindowHeight / 2));
    vector<Bullet> bullets;
    vector<Asteroid> asteroids;
    vector<Enemy> enemies;
    vector<ParticleSystem> particleSystems;

    ParticleSystem playerParticles(400, spaceship.shape.getPosition(), false);
    particleSystems.push_back(playerParticles);

    AsteroidsSpawner asteroidsSpawner;
    EnemySpawner enemySpawner;

    Gui gui;

    int currentScore = 0;

    Clock rootClock;

    while (window.isOpen() == true)
    {
        sf::Time elapsed = rootClock.restart();
        float deltaTime = elapsed.asSeconds();
        if (deltaTime > 0.2f) // Useful with breakpoint debugging
        {
            deltaTime = 0.2f;
        }

        if (spaceship.life <= 0)
        {
            deltaTime = 0.0f;
        }

        // ===== Event =====
        Event event;
        while (window.pollEvent(event) == true)
        {
            if (event.type == Event::Closed)
            {
                window.close();
                break;
            }

            if (spaceship.life <= 0)
            {
                if (event.type == Event::KeyReleased)
                {
                    if (event.key.code == Keyboard::Key::Return || event.key.code == Keyboard::Key::Enter) // Retry
                    {
                        spaceship.life = 3;
                        spaceship.shape.setPosition(1280.0f * 0.5f, 720.0f * 0.5f);
                        bullets.clear();
                        asteroids.clear();
                        enemies.clear();
                    }
                    else if (event.key.code == Keyboard::Key::Escape) // Quit
                    {
                        window.close();
                    }
                }
            }

            spaceship.ProcessEvent(event);
            gui.ProcessEvent(event);
            if (gui.IsMute() == true)
            {
                music.pause();
            }
            else if (music.getStatus() != Music::Status::Playing)
            {
                music.play();
            }
        }

        // ===== Update ===== //

        gui.Update(deltaTime);
        asteroidsSpawner.Update(deltaTime, asteroids);
        enemySpawner.Update(deltaTime, enemies);

        spaceship.Update(deltaTime, bullets);

        for (int i = 0; i < asteroids.size(); i++)
        {
            asteroids[i].Update(deltaTime, asteroids);
        }

        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].Update(deltaTime, spaceship, bullets);
        }
        // Move all bullets
        for (int i = 0; i < bullets.size(); i++)
        {
            if (bullets[i].Move(deltaTime) == true)
            {
                bullets.erase(bullets.begin() + i);
                --i;
            }
            else if (bullets[i].Collision(asteroids, currentScore) == true)
            {
                ParticleSystem asteroidDestroyedParticles(300, bullets[i].circle.getPosition(), true);
                particleSystems.push_back(asteroidDestroyedParticles);

                bullets.erase(bullets.begin() + i);
                --i;
            }
        }

        spaceship.Collision(bullets, asteroids);
        for (int i = 0; i < enemies.size(); i++)
        {
            if (enemies[i].Collision(bullets) == true)
            {
                enemies.erase(enemies.begin() + i);
                --i;
            }
        }

        Transform orientation;
        orientation.rotate(spaceship.shape.getRotation());

        /* Player particles*/
        sf::Vector2i position = sf::Vector2i(spaceship.shape.getPosition().x, spaceship.shape.getPosition().y);
        particleSystems[0].setEmitter(spaceship.shape.getPosition());
        particleSystems[0].update(elapsed, orientation, spaceship.forward);

        /* Asteroids particles */
        for (int i = 1; i < particleSystems.size(); i++)
        {
            if (particleSystems[i].update(elapsed) == true)
            {
                particleSystems.erase(particleSystems.begin() + i);
                i--;
            }
        }

        // ===== Render =====
        window.clear(Color::Black);

        gui.DrawBackground(window, asteroidsSpawner.GetDifficulty() + 1, currentScore, spaceship.life);

        spaceship.Draw(window);

        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].Draw(window);
        }

        for (int i = 0; i < asteroids.size(); i++)
        {
            asteroids[i].Draw(window);
        }

        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].Draw(window);
        }

        for (int i = 0; i < particleSystems.size(); i++)
        {
            if (i == 0)
            {
                //if (spaceship.forward)
                window.draw(particleSystems[i]);
            }
            else
            {
                window.draw(particleSystems[i]);
            }
        }

        gui.DrawForeground(window, (spaceship.life <= 0));

        window.display();
    }

    return 0;
}