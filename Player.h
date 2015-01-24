#include <SFML/Graphics.hpp>
#include "Fuel.h"


class Player
{
public:
    Player();
    Player(sf::Texture &newTexture);
    void addSpeed(sf::Vector2f speed);
    sf::Vector2f getSpeed();
    void handleMovement();

    sf::Sprite sprite;

    Fuel fuel;



private:
    sf::Vector2f speed;
};

