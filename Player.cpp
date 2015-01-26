#include <iostream>
#include "Player.h"


Player::Player(sf::Texture &newTexture)
{
    this->speed.x = 0;
    this->speed.y = 0;

    this->sprite.setTexture(newTexture);
    this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2,
                              this->sprite.getLocalBounds().width / 2);
}

Player::Player()
{
    this->speed.x = 0;
    this->speed.y = 0;
    this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2,
                              this->sprite.getLocalBounds().width / 2);
}

void Player::addSpeed(sf::Vector2f speed)
{
    this->speed.x += speed.x;
    this->speed.y += speed.y;
}

void Player::setSpeed(sf::Vector2f speed)
{
    this->speed.x = speed.x;
    this->speed.y = speed.y;
}

sf::Vector2f Player::getSpeed()
{
    return this->speed;
}

void Player::handleMovement()
{
    //Convert angle to radians
    double angleRADS = (3.1415926536 / 180) * (sprite.getRotation());


    double speed_x = speed.x * cos(angleRADS);
    double speed_y = speed.y * -sin(angleRADS);


    //Natural friction
    if (getSpeed().y < 0)
    {
        addSpeed(sf::Vector2f(-0.03, 0.03));
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (fuel.currentFuel > 0)
        {
            fuel.currentFuel -= 0.5;
            addSpeed(sf::Vector2f(0.1, -0.1));
        }

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (getSpeed().y < 0)
        {
            addSpeed(sf::Vector2f(-0.5, 0.5));
        }
    }

    //keyboard rot8
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sprite.rotate((float) -0.5);
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            sprite.rotate(-5);
        }
        else
        {
            sprite.rotate(-2);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sprite.rotate((float) +0.5);
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            sprite.rotate(+5);
        }
        else
        {
            sprite.rotate(+2);
        }
    }

//    std::cout << "SPEED.X = " << speed.x << "\nSPEED.Y = " << speed.y << "\n";

    sprite.move(speed_x, speed_y);
}


