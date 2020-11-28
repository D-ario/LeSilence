#ifndef _GUI_H_
#define _GUI_H_

#include <SFML/Graphics.hpp>

#include "Life.h"

class Gui
{
public:

	Gui();

	void ProcessEvent(const sf::Event& event);
	void Update(float deltatime);
	void DrawBackground(sf::RenderWindow& renderWindow, int currentWave, int score, int life);
	void DrawForeground(sf::RenderWindow& renderWindow, bool gameover);

	bool IsMute() const;

private:

	sf::Text scoreCurrent;
	sf::Text score;
	sf::Text wave;
	sf::Text waveCurrent;
	sf::Text gameOver;
	sf::Text retryText;
	sf::RectangleShape scoreRectangle;
	sf::Sprite songOn;
	sf::Sprite songOff;
	sf::Texture songTexture;

	LifePoint lifepoint;
	LifePoint lifepoint2;
	LifePoint lifepoint3;

	sf::Font myFont;

	bool mute = false;
};

#endif
