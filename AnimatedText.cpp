#include <iostream>
#include "AnimatedText.h"

AnimatedText::AnimatedText()
{
    isGrowing = true;
}


void AnimatedText::updateText()
{
    sf::Time time = clock.getElapsedTime();

    if (time.asMilliseconds() >= 30)
    {
        text.setColor(sf::Color((sf::Uint8) (text.getColor().r + 3),
                (sf::Uint8) (text.getColor().g + 7),
                (sf::Uint8) (text.getColor().b + 5)));

        clock.restart();
    }

    if (isGrowing)
    {
        if (text.getScale().x <= 1.5f)
        {
            text.scale(1.005, 1.005);
        }
        else
        {
            isGrowing = false;
        }
    }
    else
    {
        if (text.getScale().x >= 1.0f)
        {
            text.scale(0.995f, 0.995f);
        }
        else
        {
            isGrowing = true;
        }
    }
}

void AnimatedText::drawText(sf::RenderWindow &window)
{
    window.draw(text);
}
