#include <SFML/Graphics.hpp>
#include <deque>
using std::deque;

class Particle
{
public:
    Particle();
    sf::Sprite sprite;
};

class ParticleSystem
{
public:
    ParticleSystem(float x, float y);
    deque<Particle> particles;
};

class ParticleManager
{
public:
    void addNewSystem(float x, float y, std::string particleFilename);

    void handleMovementAndDecay();

    void drawAllParticles(sf::RenderWindow &window);

    deque<ParticleSystem> particleSystems;
    sf::Clock clock;
    sf::Texture particleTexture;

};