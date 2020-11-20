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
    vector<ParticleSystem> particleSystems;

    ParticleSystem playerParticles(400, spaceship.shape.getPosition(), false);
    particleSystems.push_back(playerParticles);

    AsteroidsSpawner asteroidsSpawner;

    // UI - Score
    int currentScore = 0;
    int numCleared = 0;

    sf::Font myFont;
    if (!myFont.loadFromFile("./font/StarJout.ttf")) {}

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

    Clock rootClock;

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

        // ===== Update ===== //

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
            if (bullets[i].Collision(asteroids, currentScore) == true)
            {
                ParticleSystem asteroidDestroyedParticles(300, bullets[i].circle.getPosition(), true);
                particleSystems.push_back(asteroidDestroyedParticles);

                bullets.erase(bullets.begin() + i);
                --i;
            }
        }

        spaceship.Collision(bullets, asteroids);

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

        window.draw(score);
        window.draw(scoreRectangle);
        window.draw(scoreCurrent);

        spaceship.Draw(window);

        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].Draw(window);
        }

        for (int i = 0; i < asteroids.size(); i++)
        {
            asteroids[i].Draw(window);
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
