#include <iostream>
#include "Game.h"

Game::Game()
{
    window.create(sf::VideoMode(1280, 720), "Rocket");
    window.setVerticalSyncEnabled(true);
//    window.setFramerateLimit(120);

    playerTexture.loadFromFile("Media/player.png");

    player = Player(playerTexture);
    player.sprite.setPosition(1280/2, 720/2);

    view.setSize(1280, 720);

    music.openFromFile("Media/song.ogg");
    music.setLoop(true);

    font.loadFromFile("Media/font.ttf");
    loseMessage.setFont(font);
    loseMessage.setString("PRESS R TO RESTART");
    loseMessage.setColor(sf::Color(255, 255, 255, 255));
    loseMessage.setCharacterSize(70);
    //center text
    sf::FloatRect textRect = loseMessage.getLocalBounds();
    loseMessage.setOrigin(textRect.left + textRect.width/2.0f,
            textRect.top  + textRect.height/2.0f);
    loseMessage.setPosition(sf::Vector2f(1280/2.0f, (720/2.0f) - 150));

    gameOver = false;

    loseMsgGrowing = true;

    goodSpeed.loadFromFile("Media/good_Speed.png");
    badSpeed.loadFromFile("Media/bad_Speed.png");
    goodSpr.setTexture(goodSpeed);
    badSpr.setTexture(badSpeed);

    goodSpr.setColor(sf::Color(255, 255, 255, 0));
    badSpr.setColor(sf::Color(255, 255, 255, 0));

    cameraPos = player.sprite.getPosition();
}

void Game::run()
{
    music.play();


    musicClock.restart();

    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void Game::update()
{
    // Update the minimum speed
    speedManager.updateSpeed();

    // Check if the game is over
    if (player.getSpeed().x >= speedManager.minSpeed)
    {
        player.handleMovement();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            trailManager.addTrailAtPos(player.sprite.getPosition().x, player.sprite.getPosition().y,
                    player.sprite.getRotation());
        }

        // Update mouse position according to window & world
        sf::Vector2i windowPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(windowPos);
        // Calculate rotation to cursor
        double angle = atan2(player.sprite.getPosition().y - worldPos.y, player.sprite.getPosition().x - worldPos.x);
        angle =   (angle * 180 / 3.1415926536) + 180;
        player.sprite.setRotation((int) angle);
    }
    else
    {
        gameOver = true;

        updateLoseMessage();
    }

    // Update view
    updateView();

    // Update background gradient
    updateGradient();

    // Update particles decay
    particleManager.handleMovementAndDecay();

    // Update the wall color
    wallManager.updateWallColor();

    // Check for powerup collision with the player
    for (int i = 0; i < powerupManager.powerups.size(); ++i)
    {
        if (powerupManager.powerups.at(i).sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds()))
        {
            // add fuel
            if (player.fuel.currentFuel + 15 <= player.fuel.maxFuel)
            {
                player.fuel.currentFuel += 30;
            }

            powerupManager.powerups.erase(powerupManager.powerups.begin() + i);

            // Add particles
            particleManager.addNewSystem(player.sprite.getPosition().x, player.sprite.getPosition().y);
        }
    }

    // Check player collision with walls
    for (int i = 0; i < wallManager.walls.size(); ++i)
    {
        if (wallManager.walls.at(i).sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds()))
        {
            // Half the players speed
            sf::Vector2f newVec = player.getSpeed();
            newVec.x /= 2;
            newVec.y /= 2;

            player.addSpeed(-newVec);
            wallManager.walls.erase(wallManager.walls.begin() + i);
        }
    }

    // Handle trail decay
    trailManager.handleDecay();


    // Update fuel bar
    player.fuel.updateFuelBar();

    updateSpeedTextures();
}

void Game::render()
{
    window.clear();

    // Draw gradient
    window.draw(gradient, 4, sf::Quads);

    // Draw trails
    for (auto &x : trailManager.trails)
    {
        window.draw(x.sprite);
    }
    // Draw powerups
    for (auto &x : powerupManager.powerups)
    {
        window.draw(x.sprite);
    }
    // Draw walls
    for (auto &x : wallManager.walls)
    {
        window.draw(x.sprite);
    }
    // Draw particles
    for (auto &x : particleManager.particleSystems)
    {
        for (auto &y : x.particles)
        {
            window.draw(y.sprite);
        }
    }


    // Draw player
    window.draw(player.sprite);

    // Draw UI start ---------------------
    window.setView(window.getDefaultView());

    window.draw(goodSpr);
    window.draw(badSpr);

    if (gameOver)
    {
        window.draw(loseMessage);
    }
    else
    {
        window.draw(player.fuel.fuelBar);
    }

    window.setView(view);
    // Draw UI end -----------------------

    window.display();
}

void Game::updateView()
{
    sf::Time time = cameraClock.getElapsedTime();

    if (time.asMilliseconds() >= 5)
    {
//        if (cameraPos.x < player.sprite.getPosition().x)
//        {
//            cameraPos.x +=5;
//        }
//        if (cameraPos.x > player.sprite.getPosition().x)
//        {
//            cameraPos.x -=5;
//        }
//        if (cameraPos.y < player.sprite.getPosition().y)
//        {
//            cameraPos.x +=5;
//        }
//        if (cameraPos.y > player.sprite.getPosition().y)
//        {
//            cameraPos.x -=5;
//        }
//        view.setCenter(cameraPos.x, cameraPos.y);
        view.setCenter(player.sprite.getPosition());
        cameraClock.restart();
    }

    // Make all the powerups scale with as the view scales
    for (auto &x : powerupManager.powerups)
    {
        x.sprite.setScale((player.getSpeed().x * 0.035 + 1), (player.getSpeed().x * 0.035 + 1));
    }


    view.setSize((player.getSpeed().x * 50) +640 , (player.getSpeed().x * 50) + 360);


//    view.setRotation(player.sprite.getRotation() + 90);


    window.setView(view);
}

void Game::updateGradient()
{
    sf::Time time = musicClock.getElapsedTime();

    if (time.asMilliseconds() >= 30)
    {
        for (int i = 0; i <= 3; i++)
        {
            gradient[i].color.r += 2;
            gradient[i].color.g += 7;
            gradient[i].color.b += 4;
        }

        musicClock.restart();
    }
}

void Game::updateLoseMessage()
{
    sf::Time time = messageClock.getElapsedTime();

    if (time.asMilliseconds() >= 30)
    {
        loseMessage.setColor(sf::Color((sf::Uint8) (loseMessage.getColor().r + 3),
                (sf::Uint8) (loseMessage.getColor().g + 7),
                (sf::Uint8) (loseMessage.getColor().b + 5)));

        messageClock.restart();
    }

    if (loseMsgGrowing)
    {
        if (loseMessage.getScale().x <= 1.5f)
        {
            loseMessage.scale(1.005, 1.005);
        }
        else
        {
            loseMsgGrowing = false;
        }
    }
    else
    {
        if (loseMessage.getScale().x >= 1.0f)
        {
            loseMessage.scale(0.995f, 0.995f);
        }
        else
        {
            loseMsgGrowing = true;
        }
    }
}

void Game::updateSpeedTextures()
{
    double speedDiff = player.getSpeed().x - speedManager.minSpeed;
    if (speedDiff <= 10)
    {
        badSpr.setColor(sf::Color(255, 255, 255, (sf::Uint8) ((10 - speedDiff) * 255 / 10)));
//        goodSpr.setColor(sf::Color(255, 255, 255, 0));
    }
    else if (speedDiff > 10 && speedDiff < 20)
    {
//        badSpr.setColor(sf::Color(255, 255, 255, 0));
        goodSpr.setColor(sf::Color(255, 255, 255, (sf::Uint8) ((speedDiff - 10) * 255 / 20)));
    }

}
