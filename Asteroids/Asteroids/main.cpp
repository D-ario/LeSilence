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

    LifePoint lifepoint(Vector2f(750.0f, 5.0f));
    LifePoint lifepoint2(Vector2f(800.0f, 5.0f));
    LifePoint lifepoint3(Vector2f(850.0f, 5.0f));

    SpaceShip spaceship(Vector2f(WindowWidth / 2, WindowHeight / 2));
    vector<Bullet> bullets;
    vector<Asteroid> asteroids;
    vector<Enemy> enemies;
    vector<ParticleSystem> particleSystems;

    ParticleSystem playerParticles(400, spaceship.shape.getPosition(), false);
    particleSystems.push_back(playerParticles);

    AsteroidsSpawner asteroidsSpawner;
    EnemySpawner enemySpawner;

    // UI - Score
    int currentScore = 0;
    int numCleared = 0;

    sf::Font myFont;
    if (!myFont.loadFromFile("../../Assets/font/StarJout.ttf")) {}

    // texte "Score" 
    sf::Text score;
    score.setFont(myFont);
    score.setFillColor(sf::Color::White);
    score.setStyle(sf::Text::Regular);
    score.setString("Score");
    score.setCharacterSize(25);
    score.setPosition(545, 5);

    // Score
    sf::Text scoreCurrent;
    scoreCurrent.setFont(myFont);
    scoreCurrent.setFillColor(sf::Color::White);
    scoreCurrent.setStyle(sf::Text::Regular);
    scoreCurrent.setString("0");
    scoreCurrent.setCharacterSize(25);
    scoreCurrent.setPosition(645, 5);

    // zone d'�criture du score
    sf::RectangleShape scoreRectangle;
    scoreRectangle.setSize(sf::Vector2f(100, 30));
    scoreRectangle.setOutlineThickness(1);
    scoreRectangle.setOutlineColor(sf::Color::White);
    scoreRectangle.setFillColor(sf::Color::Black);
    scoreRectangle.setPosition(640, 5);

    // texte "Wave" 
    sf::Text wave;
    wave.setFont(myFont);
    wave.setFillColor(sf::Color::White);
    wave.setStyle(sf::Text::Regular);
    wave.setString("Wave:");
    wave.setCharacterSize(25);
    wave.setPosition(10, 5);

    // Wave
    sf::Text waveCurrent;
    waveCurrent.setFont(myFont);
    waveCurrent.setFillColor(sf::Color::White);
    waveCurrent.setStyle(sf::Text::Regular);
    waveCurrent.setString("0");
    waveCurrent.setCharacterSize(25);
    waveCurrent.setPosition(115, 5);

    Clock rootClock;

    while (window.isOpen() == true)
    {
        sf::Time elapsed = rootClock.restart();
        float deltaTime = elapsed.asSeconds();
        if (deltaTime > 0.2f) // Useful with breakpoint debugging
        {
            deltaTime = 0.2f;
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

            spaceship.ProcessEvent(event);
        }

        // ===== Update ===== //

        asteroidsSpawner.Update(deltaTime, asteroids);
        enemySpawner.Update(deltaTime, enemies);
        waveCurrent.setString(to_string(asteroidsSpawner.GetDifficulty() + 1));

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

        // Convert score to string
        std::stringstream s;
        s << currentScore;
        scoreCurrent.setString(s.str());

        window.draw(wave);
        window.draw(waveCurrent);

        window.draw(score);
        window.draw(scoreRectangle);
        window.draw(scoreCurrent);

        if (spaceship.life == 3)
        {
            lifepoint.Draw(window);
            lifepoint2.Draw(window);
            lifepoint3.Draw(window);
        }
        else if (spaceship.life == 2)
        {
            lifepoint.Draw(window);
            lifepoint2.Draw(window);
        }
        else if (spaceship.life == 1)
        {
            lifepoint.Draw(window);
        }
        else
        {
            //window.close();
        }

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
        window.display();
    }

    return 0;
}