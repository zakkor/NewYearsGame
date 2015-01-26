#include "Background.h"

Background::Background()
{
   //
}

void Background::updateGradient()
{
    sf::Time time = clock.getElapsedTime();

    if (time.asMilliseconds() >= 30)
    {
        for (int i = 0; i <= 3; i++)
        {
            gradient[i].color.r += 2;
            gradient[i].color.g += 7;
            gradient[i].color.b += 4;
        }

        clock.restart();
    }
}

void Background::drawGradient(sf::RenderWindow &window)
{
    window.draw(gradient, 4, sf::Quads);
}
