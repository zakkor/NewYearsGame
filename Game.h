#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureHandler.h"
#include "Player.h"
#include "TrailManager.h"
#include "PowerupManager.h"
#include "WallManager.h"
#include "ParticleManager.h"
#include "SpeedManager.h"
#include "AnimatedText.h"
#include "SpeedOverlay.h"
#include "Background.h"
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


    //TODO: need to refactor all these into objects
    void updateView();

    sf::RenderWindow window;

    Background background;

    Player player;

    sf::Vector2f cameraPos;

    SpeedManager speedManager;
    TrailManager trailManager;
    PowerupManager powerupManager;
    WallManager wallManager;
    ParticleManager particleManager;


    bool gameOver;


    sf::View view;

    sf::Texture playerTexture;

    SpeedOverlay speedOverlay;

    sf::Music music;

    sf::Font font;

    AnimatedText loseMessage;

    sf::Clock musicClock, cameraClock;
};