#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureHandler.h"
#include "Player.h"
#include "TrailManager.h"
#include "PowerupManager.h"
#include "WallManager.h"
#include "ParticleManager.h"
#include "SpeedManager.h"
//#include <random>

class Game
{
public:
    Game();
    void run();

private:

    void processEvents();
    void update();
    void render();

    void updateView();

    void updateGradient();

    void updateSpeedTextures();

    void updateLoseMessage();

    sf::RenderWindow window;


    Player player;

    SpeedManager speedManager;
    TrailManager trailManager;
    PowerupManager powerupManager;
    WallManager wallManager;
    ParticleManager particleManager;


    bool gameOver;


    sf::View view;
    sf::Vector2f cameraPos;


    sf::Vertex gradient[4] =
    {
        sf::Vertex(sf::Vector2f(0, 0), sf::Color(0, 0, 0)),
        sf::Vertex(sf::Vector2f(0, 10000), sf::Color(0, 0, 0)),
        sf::Vertex(sf::Vector2f(10000, 10000), sf::Color(0, 0, 0)),
        sf::Vertex(sf::Vector2f(10000, 0), sf::Color(0, 0, 0))
    };

    sf::Texture playerTexture,
            goodSpeed, badSpeed;
    sf::Sprite badSpr, goodSpr;

    sf::Music music;

    sf::Font font;

    sf::Text loseMessage;
        bool loseMsgGrowing;


    sf::Clock musicClock, cameraClock, messageClock;
};