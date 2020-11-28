#include "Gui.h"

using namespace std;
using namespace sf;

Gui::Gui()
    : lifepoint(Vector2f(750.0f, 5.0f))
    , lifepoint2(Vector2f(800.0f, 5.0f))
    , lifepoint3(Vector2f(850.0f, 5.0f))
{

    songTexture.loadFromFile("../../Assets/texture/song_GUI.png");

    songOn.setTexture(songTexture);
    songOn.setTextureRect(IntRect(512, 0, 512, 512));
    songOn.setScale(35.0f / 512.0f, 35.0f / 512.0f);
    songOn.setPosition(1280.0f - 35.0f, 0.0f);

    songOff.setTexture(songTexture);
    songOff.setTextureRect(IntRect(0, 0, 512, 512));
    songOff.setScale(35.0f / 512.0f, 35.0f / 512.0f);
    songOff.setPosition(1280.0f - 35.0f, 0.0f);

    // UI - Score
	if (myFont.loadFromFile("../../Assets/font/StarJout.ttf") == false)
    {

    }

    // texte "Score" 
    score.setFont(myFont);
    score.setFillColor(Color::White);
    score.setStyle(Text::Regular);
    score.setString("Score");
    score.setCharacterSize(25);
    score.setPosition(545, 5);

    // Score
    scoreCurrent.setFont(myFont);
    scoreCurrent.setFillColor(Color::White);
    scoreCurrent.setStyle(Text::Regular);
    scoreCurrent.setString("0");
    scoreCurrent.setCharacterSize(25);
    scoreCurrent.setPosition(645, 5);

    // zone d'écriture du score
    scoreRectangle.setSize(Vector2f(100, 30));
    scoreRectangle.setOutlineThickness(1);
    scoreRectangle.setOutlineColor(Color::White);
    scoreRectangle.setFillColor(Color::Black);
    scoreRectangle.setPosition(640, 5);

    // texte "Wave"
    wave.setFont(myFont);
    wave.setFillColor(Color::White);
    wave.setStyle(Text::Regular);
    wave.setString("Wave:");
    wave.setCharacterSize(25);
    wave.setPosition(10, 5);

    // Wave
    waveCurrent.setFont(myFont);
    waveCurrent.setFillColor(Color::White);
    waveCurrent.setStyle(Text::Regular);
    waveCurrent.setString("0");
    waveCurrent.setCharacterSize(25);
    waveCurrent.setPosition(115, 5);

    // texte "GameOver" 
    gameOver.setFont(myFont);
    gameOver.setFillColor(Color::White);
    gameOver.setStyle(Text::Regular);
    gameOver.setString("Gameover");
    gameOver.setCharacterSize(56);
    FloatRect gameOverBounds = gameOver.getGlobalBounds();
    gameOver.setPosition(1280 * 0.5f - gameOverBounds.width * 0.5f, 720.0f * 0.5f - gameOverBounds.height * 0.5f);

    retryText.setFont(myFont);
    retryText.setFillColor(Color::White);
    retryText.setStyle(Text::Regular);
    retryText.setString("Press 'Enter' to Retry, or 'Esc' to Quit");
    retryText.setCharacterSize(32);
    FloatRect retryTextBounds = retryText.getGlobalBounds();
    retryText.setPosition(1280 * 0.5f - retryTextBounds.width * 0.5f, 720.0f * 0.5f + gameOverBounds.height + retryTextBounds.height);
}

void Gui::ProcessEvent(const Event& event)
{
    if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Button::Left)
    {
        if (songOff.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) == true)
        {
            mute = !mute;
        }
    }        
}

void Gui::Update(float deltatime)
{

}

void Gui::DrawBackground(RenderWindow& renderWindow, int currentWave, int currentScore, int life)
{
    renderWindow.draw(wave);
    waveCurrent.setString(to_string(currentWave));
    renderWindow.draw(waveCurrent);

    renderWindow.draw(score);
    renderWindow.draw(scoreRectangle);

    scoreCurrent.setString(to_string(currentScore));
    renderWindow.draw(scoreCurrent);

    if (life == 3)
    {
        lifepoint.Draw(renderWindow);
        lifepoint2.Draw(renderWindow);
        lifepoint3.Draw(renderWindow);
    }
    else if (life == 2)
    {
        lifepoint.Draw(renderWindow);
        lifepoint2.Draw(renderWindow);
    }
    else if (life == 1)
    {
        lifepoint.Draw(renderWindow);
    }

    if (mute == true)
    {
        renderWindow.draw(songOff);
    }
    else
    {
        renderWindow.draw(songOn);
    }
}

void Gui::DrawForeground(RenderWindow& renderWindow, bool gameover)
{
    if (gameover == true)
    {
        renderWindow.draw(gameOver);
        renderWindow.draw(retryText);
    }
}

bool Gui::IsMute() const
{
    return mute;
}
