#include "Player.h"

// Constructor for Player class
Player::Player(const sf::Texture& texture) : speed(200.0f) {
    sprite.setTexture(texture);         // Set the texture for the player sprite
    sprite.setScale(0.07f, 0.07f);        // Reset scaling if necessary (scale factor 1.0 keeps the original size)
    sprite.setPosition(600.0f, 400.0f); // Example initial position (center of the window)
}

// Update method for the player (called every frame)
void Player::update(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

    // Handle player movement with W/A/S/D or arrow keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movement.y -= speed * deltaTime;  // Move up
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += speed * deltaTime;  // Move down
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= speed * deltaTime;  // Move left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += speed * deltaTime;  // Move right
    }

    // Apply the movement to the player sprite
    sprite.move(movement);
}

// Draw the player sprite onto the render window
void Player::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}




int Player::getAmmoCapacity() const {
    return ammoCapacity;
}

void Player::increaseAmmo(int amount) {
    ammoCapacity = std::min(ammoCapacity + amount, maxAmmoCapacity);
}

// Return the player's speed
float Player::getSpeed() const {
    return speed;
}

// Return the player's sprite (const version for read-only access)
const sf::Sprite& Player::getSprite() const {
    return sprite;
}

// Set the player's position
void Player::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

// Get the player's current position
sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

// Set the player's rotation angle
void Player::setRotation(float angle) {
    sprite.setRotation(angle);
}
