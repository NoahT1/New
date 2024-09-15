#include "AsteroidSpawner.h"
#include "Asteroid.h"
#include <cstdlib>  // For rand()

// Constructor: initialize with texture and window reference
AsteroidSpawner::AsteroidSpawner(const sf::Texture& texture, sf::RenderWindow& win)
    : asteroidTexture(texture), window(win) {}

// Method to spawn a new asteroid with a random size, position, and velocity
void AsteroidSpawner::spawnAsteroid() {
    // Random position on the screen (spawning above the window to simulate entry)
    float xPos = static_cast<float>(rand() % window.getSize().x);
    float yPos = -50.0f;  // Start slightly above the window

    sf::Vector2f position(xPos, yPos);

    // Random size: Large, Medium, or Small
    AsteroidSize randomSize = static_cast<AsteroidSize>(rand() % 3);  // 0 -> Large, 1 -> Medium, 2 -> Small

    // Set velocity based on size (smaller asteroids move faster)
    sf::Vector2f velocity = getRandomVelocity(randomSize);

    // Add the asteroid to the vector
    asteroids.emplace_back(asteroidTexture, Regular, randomSize, position, velocity);
}

// Overloaded method to spawn an asteroid at a specific position and velocity
void AsteroidSpawner::spawnAsteroid(const sf::Texture& texture, AsteroidSize size, const sf::Vector2f& position, const sf::Vector2f& velocity) {
    // Add a new asteroid with the given parameters
    asteroids.emplace_back(texture, Regular, size, position, velocity);
}

// Update all asteroids based on deltaTime
void AsteroidSpawner::updateAsteroids(float deltaTime) {
    for (auto& asteroid : asteroids) {
        asteroid.update(deltaTime);  // Update position and handle wrapping
    }
}

// Draw all asteroids on the screen
void AsteroidSpawner::drawAsteroids(sf::RenderWindow& window) {
    for (const auto& asteroid : asteroids) {
        asteroid.draw(window);  // Render each asteroid
    }
}

// Helper method to generate random velocity for asteroids based on their size
sf::Vector2f AsteroidSpawner::getRandomVelocity(AsteroidSize size) {
    float vx = static_cast<float>(rand() % 100 - 50);  // Random horizontal speed

    // Set vertical speed based on asteroid size (smaller is faster)
    float vy;
    switch (size) {
    case Large:
        vy = static_cast<float>(rand() % 50 + 50);  // Slow speed for large asteroids
        break;
    case Medium:
        vy = static_cast<float>(rand() % 100 + 100);  // Medium speed for medium asteroids
        break;
    case Small:
        vy = static_cast<float>(rand() % 150 + 150);  // Fast speed for small asteroids
        break;
    }

    return sf::Vector2f(vx, vy);
}
