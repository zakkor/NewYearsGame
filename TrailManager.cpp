#include "TrailManager.h"

TrailManager::TrailManager()
{
    trailTexture.loadFromFile("Media/trail.png");
}

void TrailManager::addTrailAtPos(float x, float y, float rotation)
{
    Trail newTrail= Trail();
    newTrail.sprite.setTexture(trailTexture);
    newTrail.sprite.setPosition(x, y);
    newTrail.sprite.setRotation(rotation);
    newTrail.sprite.setOrigin(newTrail.sprite.getLocalBounds().width, newTrail.sprite.getLocalBounds().height / 2);
    trails.push_back(newTrail);
}

void TrailManager::handleDecay()
{
    sf::Time time = clock.getElapsedTime();
    if (time.asMilliseconds() >= 10)
    {
        for (auto &x : trails)
        {
            if (x.sprite.getColor().a == 0 || (x.sprite.getScale().x == 0 && x.sprite.getScale().y == 0))
            {
                trails.pop_front();
            }
            else
            {
                sf::Color newColor = x.sprite.getColor();
                newColor.a -= 5;
                x.sprite.setColor(newColor);
                x.sprite.scale(1, 0.95);
            }
        }
        clock.restart();
    }
}
