#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <deque>
using std::deque;

struct Trail
{
public:
    sf::Sprite sprite;
};

class TrailManager
{
public:
    TrailManager();
    void addTrailAtPos(float x, float y, float rotation, sf::Color color);

    void spawnTrails(float x, float y, float rotation);

    void handleDecay();

    void drawTrails(sf::RenderWindow &window);

    deque<Trail> trails;
private:
    sf::Texture trailTexture;
    sf::Clock decayClock, alternateClock;
    bool spawningCyan;
};