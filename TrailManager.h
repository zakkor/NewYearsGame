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
    void addTrailAtPos(float x, float y, float rotation);
    void handleDecay();

    deque<Trail> trails;
private:
    sf::Texture trailTexture;
    sf::Clock clock;
};