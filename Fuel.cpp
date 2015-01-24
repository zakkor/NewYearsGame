#include "Fuel.h"

Fuel::Fuel()
{
    maxFuel = 100;
    currentFuel = 50;

    fuelBar.setOutlineThickness(1);
    fuelBar.setOutlineColor(sf::Color(255, 0, 0));
}

void Fuel::updateFuelBar()
{
    int fuelBarSize = currentFuel * 400 / maxFuel;

//    int barOpacity = (int) currentFuel * 255 / 100;

    fuelBar.setSize(sf::Vector2f(fuelBarSize, 30));
    fuelBar.setOrigin(fuelBar.getSize().x / 2, fuelBar.getSize().y / 2);
    fuelBar.setPosition(1280/2, 600);
    fuelBar.setFillColor(sf::Color(255, 63, 191, 255));
}
