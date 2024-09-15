#ifndef ASTEROIDSPAWNER_H
#define ASTEROIDSPAWNER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Asteroid.h"

class AsteroidSpawner {
public:
    // Constructor: initialize with texture and window reference
    AsteroidSpawner(const sf::Texture& texture, sf::RenderWindow& window);

    // Method to spawn a new asteroid with a random size, position, and velocity
    void spawnAsteroid();

    // Overloaded method to spawn an asteroid at a specific position with a specific size and velocity
    void spawnAsteroid(const sf::Texture& texture, AsteroidSize size, const sf::Vector2f& position, const sf::Vector2f& velocity);

    // Update all asteroids based on deltaTime
    void updateAsteroids(float deltaTime);

    // Draw all asteroids in the window
    void drawAsteroids(sf::RenderWindow& window);

    // Vector to store asteroids
    std::vector<Asteroid> asteroids;

private:
    // Helper method to generate random velocity based on asteroid size
    sf::Vector2f getRandomVelocity(AsteroidSize size);

    // Texture for the asteroid
    const sf::Texture& asteroidTexture;

    // Reference to the game window (for screen bounds, etc.)
    sf::RenderWindow& window;
};

#endif // ASTEROIDSPAWNER_H
