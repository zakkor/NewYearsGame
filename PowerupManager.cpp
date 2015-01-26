#include "PowerupManager.h"
#include <stdlib.h>
#include <time.h>

PowerupManager::PowerupManager()
{
    fuelTexture.loadFromFile("Media/fuel.png");
    boostTexture.loadFromFile("Media/boost.png");
    reloadPowerups();
}

void PowerupManager::drawPowerups(sf::RenderWindow &window)
{
    for (auto &x : powerups)
    {
        window.draw(x.sprite);
    }
}

void PowerupManager::reloadPowerups()
{
    powerups.clear();

    for (int i = 0; i < 500; ++i)
    {
        Powerup newPowerup;

        int aux = rand() % 10;

        if (aux == 1)
        {
            newPowerup.sprite.setTexture(boostTexture);
            newPowerup.powerupType = Boost;
        }
        else
        {
            newPowerup.sprite.setTexture(fuelTexture);
            newPowerup.powerupType = Fuel;
        }

        newPowerup.sprite.setPosition(rand()%10000, rand()%10000);


        powerups.push_back(newPowerup);
    }

}
