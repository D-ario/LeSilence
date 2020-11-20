#ifndef _LIFE_H_
#define _LIFE_H_

#include <SFML/Graphics.hpp>

class SpaceShip;

class LifePoint
{
	public:
		LifePoint(sf::Vector2f position);
		void Draw(sf::RenderWindow& renderWindow);
		sf::ConvexShape shape;
};

#endif