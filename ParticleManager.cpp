#include <iostream>
#include "ParticleManager.h"

ParticleSystem::ParticleSystem(float x, float y)
{
    for (int i = 0; i < 50; ++i)
    {
        Particle newParticle;

        int roll = rand() % 3;

        if (roll == 0)
        {
            newParticle.sprite.setPosition(x + rand() % 100, y + rand() % 100);
        }
        if (roll == 1)
        {
            newParticle.sprite.setPosition(x - rand() % 100, y + rand() % 100);
        }
        if (roll == 2)
        {
            newParticle.sprite.setPosition(x + rand() % 100, y - rand() % 100);
        }
        if (roll == 3)
        {
            newParticle.sprite.setPosition(x - rand() % 100, y - rand() % 100);
        }

        newParticle.sprite.setScale(rand() % 3, rand() % 3);
        newParticle.sprite.setRotation(rand() % 360);
        particles.push_back(newParticle);
    }
}

void ParticleManager::addNewSystem(float x, float y, std::string particleFilename)
{
    ParticleSystem newSystem(x, y);
    particleTexture.loadFromFile("Media/" + particleFilename);
    for (auto &j : newSystem.particles)
    {
        j.sprite.setTexture(particleTexture);
    }
    particleSystems.push_back(newSystem);
}

Particle::Particle()
{

}

void ParticleManager::handleMovementAndDecay()
{
    sf::Time time = clock.getElapsedTime();
    if (time.asMilliseconds() >= 10)
    {
        for (auto &x : particleSystems)
        {
            for (auto &y : x.particles)
            {
                if (y.sprite.getColor().a <= 0)
                {
                    x.particles.pop_front();
                }
                else
                {
                    sf::Color newColor = y.sprite.getColor();
                    newColor.a -= 5;
                    y.sprite.setColor(newColor);
                    y.sprite.scale(0.99, 0.99);
                }
            }
        }
        clock.restart();
    }
}

void ParticleManager::drawAllParticles(sf::RenderWindow &window)
{
    for (auto &x : particleSystems)
    {
        for (auto &y : x.particles)
        {
            window.draw(y.sprite);
        }
    }
}
