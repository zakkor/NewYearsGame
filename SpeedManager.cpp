#include <iostream>
#include "SpeedManager.h"

SpeedManager::SpeedManager()
{
    minSpeed = -10;

}

void SpeedManager::updateSpeed()
{
    minSpeed += 0.01;
    std::cout << "MIN SPEED = " << minSpeed << "\n";
}
