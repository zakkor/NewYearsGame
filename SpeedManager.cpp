#include <iostream>
#include "SpeedManager.h"

SpeedManager::SpeedManager()
{
    minSpeed = -5;

}

void SpeedManager::updateSpeed()
{
    minSpeed += 0.01;
}
