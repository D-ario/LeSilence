#include "Life.h"
#include "SpaceShip.h"

#include <iostream>

using namespace sf;
using namespace std;

LifePoint::LifePoint(Vector2f position)
{
	shape.setPointCount(8);
	shape.setPoint(0, Vector2f(20.0f, 10.0f));
	shape.setPoint(1, Vector2f(10.0f, 5.0f));
	shape.setPoint(2, Vector2f(5.0f, 10.0f));
	shape.setPoint(3, Vector2f(5.0f, 15.0f));
	shape.setPoint(4, Vector2f(20.0f, 30.0f));
	shape.setPoint(5, Vector2f(35.0f, 15.0f));
	shape.setPoint(6, Vector2f(35.0f, 10.0f));
	shape.setPoint(7, Vector2f(30.0f, 5.0f));

	shape.setPosition(position);

	shape.setFillColor(Color::White);
	shape.setOutlineColor(Color::White);
}

void LifePoint::Draw(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(shape);
}
