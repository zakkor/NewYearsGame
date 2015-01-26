#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class SpeedOverlay
{
public:
    SpeedOverlay();

    void updateOverlay(float playerSpeed, float minSpeed);

    void drawOverlay(sf::RenderWindow &window);

private:
    sf::Texture greenGradient, redGradient;
    sf::Sprite redSprite, greenSprite;
};