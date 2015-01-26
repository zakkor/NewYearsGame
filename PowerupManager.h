#include <SFML/Graphics.hpp>
#include <deque>
using std::deque;


enum PowerupTypes
{
    Fuel,
    Boost
};



struct Powerup
{
public:
    sf::Sprite sprite;

    PowerupTypes powerupType;
};

class PowerupManager
{
public:
    PowerupManager();

    void reloadPowerups();

    void drawPowerups(sf::RenderWindow &window);

    deque<Powerup> powerups;

private:
    sf::Texture fuelTexture, boostTexture;
};