#include <SFML/Graphics.hpp>

class Fuel
{
public:
    Fuel();

    void updateFuelBar();
    

    int maxFuel;

    int currentFuel;

    sf::RectangleShape fuelBar;
    sf::RectangleShape fuelOutline;
};
