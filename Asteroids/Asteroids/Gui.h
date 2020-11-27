#ifndef _GUI_H_
#define _GUI_H_

#include <SFML/Graphics.hpp>

#include "Life.h"

class Gui
{
public:

	Gui();

	void Update(float deltatime);
	void DrawBackground(sf::RenderWindow& renderWindow, int currentWave, int score, int life);
	void DrawForeground(sf::RenderWindow& renderWindow, bool gameover);

private:

	sf::Text scoreCurrent;
	sf::Text score;
	sf::Text wave;
	sf::Text waveCurrent;
	sf::Text gameOver;
	sf::Text retryText;
	sf::RectangleShape scoreRectangle;

	LifePoint lifepoint;
	LifePoint lifepoint2;
	LifePoint lifepoint3;

	sf::Font myFont;
};

#endif
