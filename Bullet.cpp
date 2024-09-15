#include "Bullet.h"

Bullet::Bullet(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& direction)
    : velocity(direction), speed(500.0f)  // Set the bullet's speed
{
    sprite.setTexture(texture);
    sprite.setPosition(position);

    // Make the bullet smaller by scaling the sprite (e.g., 50% size)
    sprite.setScale(0.4f, 0.4f);  // Adjust these values as needed for your game
}

void Bullet::update(float deltaTime) {
    // Move the bullet according to its velocity and speed
    sprite.move(velocity * speed * deltaTime);
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

const sf::Sprite& Bullet::getSprite() const {
    return sprite;
}
