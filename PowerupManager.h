#include <SFML/Graphics.hpp>
#include <deque>
using std::deque;


struct Powerup
{
public:
sf::Sprite sprite;
};

class PowerupManager
{
public:
    PowerupManager();
    deque<Powerup> powerups;
private:
    sf::Texture powerupTexture;
};