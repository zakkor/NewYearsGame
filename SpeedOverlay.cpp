#include "SpeedOverlay.h"

SpeedOverlay::SpeedOverlay()
{
    greenGradient.loadFromFile("Media/good_Speed.png");
    redGradient.loadFromFile("Media/bad_Speed.png");
    greenSprite.setTexture(greenGradient);
    redSprite.setTexture(redGradient);
}

void SpeedOverlay::updateOverlay(float playerSpeed, float minSpeed)
{
    double speedDiff = playerSpeed - minSpeed;
    if (speedDiff <= 10)
    {
        redSprite.setColor(sf::Color(255, 255, 255, (sf::Uint8) ((10 - speedDiff) * 255 / 10)));
    }
    else if (speedDiff > 10 && speedDiff < 20)
    {
        greenSprite.setColor(sf::Color(255, 255, 255, (sf::Uint8) ((speedDiff - 10) * 255 / 20)));
    }
}

void SpeedOverlay::drawOverlay(sf::RenderWindow &window)
{
    window.draw(greenSprite);
    window.draw(redSprite);
}
