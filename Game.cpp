#include <iostream>
#include "Game.h"

Game::Game()
{
    window.create(sf::VideoMode(1280, 720), "Rocket");
    window.setVerticalSyncEnabled(true);
//    window.setFramerateLimit(120);

    playerTexture.loadFromFile("Media/player.png");

    player = Player(playerTexture);
    player.sprite.setPosition(1280 / 2, 720 / 2);

    view.setSize(1280, 720);

    music.openFromFile("Media/song.ogg");
    music.setLoop(true);

    font.loadFromFile("Media/font.ttf");
    loseMessage.text.setFont(font);
    loseMessage.text.setString("PRESS R TO RESTART");
    loseMessage.text.setColor(sf::Color(255, 255, 255, 255));
    loseMessage.text.setCharacterSize(70);
    //center text
    sf::FloatRect textRect = loseMessage.text.getLocalBounds();
    loseMessage.text.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
    loseMessage.text.setPosition(sf::Vector2f(1280 / 2.0f, (720 / 2.0f) - 150));

    gameOver = false;

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
        if (event.type == sf::Event::KeyPressed)
        {
            // Restart game:
            if (event.key.code == sf::Keyboard::R)
            {
//                if (gameOver)
                {
                    gameOver = false;

                    player.sprite.setPosition(500, 500);
                    player.setSpeed(sf::Vector2f(0, 0));
                    speedManager.minSpeed = -10;
                    player.fuel.currentFuel = 50;
                    powerupManager.reloadPowerups();
                }
            }

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

        trailManager.spawnTrails(player.sprite.getPosition().x, player.sprite.getPosition().y,
                player.sprite.getRotation());


        // Update mouse position according to window & world
        sf::Vector2i windowPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(windowPos);
        // Calculate rotation to cursor
        double angle = atan2(player.sprite.getPosition().y - worldPos.y, player.sprite.getPosition().x - worldPos.x);
        angle = (angle * 180 / 3.1415926536) + 180;
        player.sprite.setRotation((int) angle);
    }
    else
    {
        gameOver = true;

        loseMessage.updateText();
    }

    // Update view TODO: replace with ViewHandler
    updateView();

    // Update background gradient
    background.updateGradient();

    // Update particles decay
    particleManager.handleMovementAndDecay();

    // Update the wall color
    wallManager.updateWalls();

    // Check for powerup collision with the player
    for (int i = 0; i < powerupManager.powerups.size(); ++i)
    {
        if (powerupManager.powerups.at(i).sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds()))
        {
            // add fuel
            if (powerupManager.powerups.at(i).powerupType == Fuel)
            {
                if (player.fuel.currentFuel + 15 <= player.fuel.maxFuel)
                {
                    player.fuel.currentFuel += 30;
                }
            }
            else if (powerupManager.powerups.at(i).powerupType == Boost)
            {
                player.addSpeed(sf::Vector2f(2, -2));
            }


            powerupManager.powerups.erase(powerupManager.powerups.begin() + i);

            // Add particles
            particleManager.addNewSystem(player.sprite.getPosition().x, player.sprite.getPosition().y, "particle.png");
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

            //Add particles
            particleManager.addNewSystem(player.sprite.getPosition().x, player.sprite.getPosition().y, "wallparticle.png");
        }
    }

    // Handle trail decay
    trailManager.handleDecay();


    // Update fuel bar
    player.fuel.updateFuelBar();

    // Update speed overlay
    speedOverlay.updateOverlay(player.getSpeed().x, speedManager.minSpeed);
}

void Game::render()
{
    window.clear();

    // Draw Gradient
    background.drawGradient(window);

    // Draw trails
    trailManager.drawTrails(window);

    // Draw powerups
    powerupManager.drawPowerups(window);

    // Draw walls
    wallManager.drawWalls(window);

    // Draw particles
    particleManager.drawAllParticles(window);

    // Draw player
    window.draw(player.sprite);

    // Draw UI start ---------------------
    window.setView(window.getDefaultView());

    // Draw Overlay
    speedOverlay.drawOverlay(window);

    if (gameOver)
    {
        loseMessage.drawText(window);
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
        view.setCenter(player.sprite.getPosition());
        cameraClock.restart();
    }

    // Make all the powerups scale with as the view scales
    for (auto &x : powerupManager.powerups)
    {
        x.sprite.setScale((player.getSpeed().x * 0.035 + 1), (player.getSpeed().x * 0.035 + 1));
    }


    view.setSize((player.getSpeed().x * 50) + 640, (player.getSpeed().x * 50) + 360);


//    view.setRotation(player.sprite.getRotation() + 90);


    window.setView(view);
}


