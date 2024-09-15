#include <cmath>  // Required for std::sqrt
#include "Opponent.h"

Opponent::Opponent(const sf::Texture& texture, const sf::Vector2f& position)
    : health(50.0f), shootCooldown(2.0f), maxHealth(50.0f) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

    // Initialize the health bar
    healthBar.setSize(sf::Vector2f(50.0f, 5.0f));  // Health bar size (50px width, 5px height)
    healthBar.setFillColor(sf::Color::Green);  // Full health is green
    healthBar.setPosition(sprite.getPosition().x, sprite.getPosition().y + sprite.getGlobalBounds().height / 2 + 10);  // Place below opponent sprite
}

void Opponent::update(float deltaTime) {
    // Move the opponent horizontally
    sprite.move(100.0f * deltaTime, 0.0f);  // Move right at 100 units per second

    // If the opponent moves off the right side, reset to the left
    if (sprite.getPosition().x > 1200) {  // Assuming 1200 is the width of the screen
        sprite.setPosition(-sprite.getGlobalBounds().width, sprite.getPosition().y);  // Move to the left side of the screen
    }

    // Update the position of the health bar based on the opponent's current position
    healthBar.setPosition(sprite.getPosition().x - healthBar.getSize().x / 2, sprite.getPosition().y + sprite.getGlobalBounds().height / 2 + 10);
}

void Opponent::draw(sf::RenderWindow& window) {
    window.draw(sprite);  // Draw the opponent
    window.draw(healthBar);  // Draw the health bar under the opponent
}

void Opponent::takeDamage(float amount) {
    health -= amount;
    updateHealthBar();  // Update the health bar when opponent takes damage
}

bool Opponent::isDestroyed() const {
    return health <= 0;
}

void Opponent::updateHealthBar() {
    // Calculate the health percentage
    float healthPercentage = std::max(0.0f, health / maxHealth);

    // Update the size of the health bar
    healthBar.setSize(sf::Vector2f(50.0f * healthPercentage, 5.0f));  // Shrink the width as health decreases

    // Update the color of the health bar based on the health percentage
    if (healthPercentage > 0.6f) {
        healthBar.setFillColor(sf::Color::Green);  // Healthy (green)
    } else if (healthPercentage > 0.3f) {
        healthBar.setFillColor(sf::Color::Yellow);  // Moderate (yellow)
    } else {
        healthBar.setFillColor(sf::Color::Red);  // Low health (red)
    }
}

void Opponent::shoot(std::vector<sf::Sprite>& bullets, std::vector<sf::Vector2f>& bulletVelocities, const sf::Texture& bulletTexture, const sf::Vector2f& playerPosition) {
    // Shoot bullets at intervals defined by shootCooldown
    if (shootClock.getElapsedTime().asSeconds() > shootCooldown) {
        sf::Sprite bullet;
        bullet.setTexture(bulletTexture);
        bullet.setPosition(sprite.getPosition());

        // Calculate direction towards the player
        sf::Vector2f direction = playerPosition - sprite.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) {
            direction.x /= length;  // Normalize the direction
            direction.y /= length;
        }

        // Set the velocity for the bullet
        sf::Vector2f velocity = direction * 300.0f;  // Bullet speed is 300 units per second

        // Add the bullet and its velocity to the vectors
        bullets.push_back(bullet);
        bulletVelocities.push_back(velocity);  // Store the bullet's velocity

        // Restart the shoot clock
        shootClock.restart();
    }
}

const sf::Sprite& Opponent::getSprite() const {
    return sprite;
}
