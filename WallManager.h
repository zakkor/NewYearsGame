#include <SFML/Graphics.hpp>
#include <deque>

using std::deque;

class Wall
{
public:
    Wall();
    sf::Sprite sprite;
};

class WallManager
{
public:
    WallManager();

    void updateWallColor();

    deque<Wall> walls;
private:
    sf::Texture wallTexture;
};