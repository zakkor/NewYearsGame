#include <SFML/Graphics.hpp>

class AnimatedText
{
public:
    AnimatedText();

    void updateText();

    void drawText(sf::RenderWindow &window);

    //TODO: make constructor to handle shit and then make it private
//private:
    sf::Text text;
    sf::Clock clock;
    bool isGrowing;
};