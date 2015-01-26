#include "SFML/Graphics.hpp"


class Background
{
public:
    Background();

    void updateGradient();

    void drawGradient(sf::RenderWindow &window);

    sf::Vertex gradient[4] =
    {
            sf::Vertex(sf::Vector2f(0, 0), sf::Color(0, 0, 0)),
            sf::Vertex(sf::Vector2f(0, 10000), sf::Color(0, 0, 0)),
            sf::Vertex(sf::Vector2f(10000, 10000), sf::Color(0, 0, 0)),
            sf::Vertex(sf::Vector2f(10000, 0), sf::Color(0, 0, 0))
    };

    sf::Clock clock;
};