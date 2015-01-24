#include "PowerupManager.h"
#include <stdlib.h>
#include <time.h>

PowerupManager::PowerupManager()
{
    powerupTexture.loadFromFile("Media/powerup.png");


    for (int i = 0; i < 500; ++i)
    {
        Powerup newPowerup;
        newPowerup.sprite.setPosition(rand()%10000, rand()%10000);
        newPowerup.sprite.setTexture(powerupTexture);
        powerups.push_back(newPowerup);
    }
}
