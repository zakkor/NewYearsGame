#include "WallManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Wall::Wall()
{

}

WallManager::WallManager()
{
    wallTexture.loadFromFile("Media/wall.png");

    for (int i = 0; i < 50; ++i)
    {
        Wall newWall;
        newWall.sprite.setPosition(rand()%10000, rand()%10000);
        newWall.sprite.setTexture(wallTexture);
        newWall.sprite.setScale(1, 5);
        newWall.sprite.setRotation(rand()%360);
        walls.push_back(newWall);
    }
}

void WallManager::updateWalls()
{
    for (auto &x : walls)
    {
        x.sprite.setColor(sf::Color((sf::Uint8) (x.sprite.getColor().r + 3),
                            (sf::Uint8) (x.sprite.getColor().g + 2),
                            (sf::Uint8) (x.sprite.getColor().b + 5)));
    }
}

void WallManager::drawWalls(sf::RenderWindow &window)
{
    for (auto &x : walls)
    {
        window.draw(x.sprite);
    }
}
