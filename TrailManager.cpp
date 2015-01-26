#include <iostream>
#include "TrailManager.h"

TrailManager::TrailManager()
{
    trailTexture.loadFromFile("Media/trail.png");
}

void TrailManager::addTrailAtPos(float x, float y, float rotation, sf::Color color)
{
    Trail newTrail= Trail();
    newTrail.sprite.setTexture(trailTexture);
    newTrail.sprite.setPosition(x, y);
    newTrail.sprite.setRotation(rotation);
    newTrail.sprite.setOrigin(newTrail.sprite.getLocalBounds().width, newTrail.sprite.getLocalBounds().height / 2);
    newTrail.sprite.setColor(color);
    trails.push_back(newTrail);
}

void TrailManager::handleDecay()
{
    sf::Time time = decayClock.getElapsedTime();
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
        decayClock.restart();
    }
}

void TrailManager::drawTrails(sf::RenderWindow &window)
{
    for (auto &x : trails)
    {
        window.draw(x.sprite);
    }
}

void TrailManager::spawnTrails(float x, float y, float rotation)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
//        sf::Time time = alternateClock.getElapsedTime();
//        if (time.asMilliseconds() >= 50)
//        {
//            spawningCyan = !spawningCyan;
//            alternateClock.restart();
//        }
//
//        if (spawningCyan)
//        {
//            addTrailAtPos(x, y,
//                    rotation, sf::Color::Cyan);
//        }
//        else
//        {
            addTrailAtPos(x, y,
                    rotation, sf::Color::Red);
//        }

    }
    else
    {
        addTrailAtPos(x, y,
                rotation, sf::Color::White);
    }
}
