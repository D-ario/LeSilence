#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
constexpr float WindowWidth = 1280.0f;
constexpr float WindowHeight = 720.0f;
constexpr float ForwardSpeed = 0.2f;

void Enemy()
{
	//pre def
	Clock rootClock;
	float deltaTime = rootClock.restart().asSeconds();
	RenderWindow window(VideoMode(WindowWidth, WindowHeight), "Asteroids");

	//def Enemy
	ConvexShape enemy;
	enemy.setPointCount(4);
	enemy.setPoint(0, Vector2f(-10.f, -15.f));
	enemy.setPoint(1, Vector2f(-10.f, 15.f));
	enemy.setPoint(2, Vector2f(10.f, 15.f));
	enemy.setPoint(3, Vector2f(10.f, -15.f));
	enemy.setFillColor(Color::Red);
	enemy.setOutlineColor(Color::Black);

	//à redéfinir avec le EnemyManager
	enemy.setPosition(Vector2f(WindowWidth * 2.f, WindowHeight * 2.f));


	//def mouvement
	bool moving = true;
	Vector2f velocityEnemy;

	if (moving == true)
	{
		Vector2f movingDirection(0.0f, -1.0f);

		//apply velocity
		velocityEnemy += movingDirection * ForwardSpeed * deltaTime;

		//new position Enemy
		Vector2f newPositionE = enemy.getPosition();
		newPositionE += velocityEnemy;
		enemy.setPosition(newPositionE);
	}

	if 
}
