#include "Asteroid.h"

// Constructor: initialize asteroid with texture, type, size, position, and velocity
Asteroid::Asteroid(const sf::Texture& texture, AsteroidType type, AsteroidSize size, const sf::Vector2f& position, const sf::Vector2f& velocity)
    : type(type), size(size), velocity(velocity), dealtDamage(false) {

    // Set texture and initial position for the asteroid
    sprite.setTexture(texture);
    sprite.setPosition(position);

    // Center the origin of the asteroid sprite (for better rotation and movement)
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

    // Scale the asteroid sprite based on its size (smaller sizes scale down)
    switch (size) {
    case Large:
        sprite.setScale(1.0f, 1.0f);  // Default size
        break;
    case Medium:
        sprite.setScale(0.6f, 0.6f);  // Medium asteroids are smaller
        break;
    case Small:
        sprite.setScale(0.3f, 0.3f);  // Small asteroids are even smaller
        break;
    }
}

// Update the asteroid's position based on its velocity and the elapsed time (deltaTime)
void Asteroid::update(float deltaTime) {
    // Move the asteroid based on its velocity
    sprite.move(velocity * deltaTime);

    // Screen wrapping logic: If the asteroid goes off one edge of the screen, wrap it to the other side
    if (sprite.getPosition().x < 0) sprite.setPosition(1200, sprite.getPosition().y);  // Wrap left to right
    if (sprite.getPosition().x > 1200) sprite.setPosition(0, sprite.getPosition().y);  // Wrap right to left
    if (sprite.getPosition().y < 0) sprite.setPosition(sprite.getPosition().x, 800);   // Wrap top to bottom
    if (sprite.getPosition().y > 800) sprite.setPosition(sprite.getPosition().x, 0);   // Wrap bottom to top
}

// Draw the asteroid to the screen
void Asteroid::draw(sf::RenderWindow& window) const {
    window.draw(sprite);  // Draw the asteroid sprite
}

// Get the size of the asteroid
AsteroidSize Asteroid::getSize() const {
    return size;  // Return the size (Large, Medium, Small)
}

// Get the damage dealt by the asteroid based on its size
float Asteroid::getDamage() const {
    // Larger asteroids deal more damage
    switch (size) {
    case Large: return 30.0f;
    case Medium: return 20.0f;
    case Small: return 10.0f;
    }
    return 0.0f;
}

// Check if the asteroid has already dealt damage
bool Asteroid::hasDealtDamage() const {
    return dealtDamage;
}

// Mark the asteroid as having dealt damage (so it doesn't deal damage again)
void Asteroid::setDealtDamage() {
    dealtDamage = true;
}
