#include "Blackhole.h"

Blackhole::Blackhole(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& velocity)
    : velocity(velocity)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);

    // Scale down the blackhole to make it smaller
    sprite.setScale(0.3f, 0.3f);  // Adjust the scale factor as needed (this will reduce the size to 20% of the original)
}

void Blackhole::update(float deltaTime) {
    // Move the blackhole by its velocity
    sprite.move(velocity * deltaTime);
}

void Blackhole::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

const sf::Sprite& Blackhole::getSprite() const {
    return sprite;
}

void Blackhole::bounceOffWalls(const sf::RenderWindow& window) {
    sf::Vector2f position = sprite.getPosition();
    sf::Vector2u windowSize = window.getSize();
    float spriteWidth = sprite.getGlobalBounds().width;
    float spriteHeight = sprite.getGlobalBounds().height;

    // Bounce off the left or right edges
    if (position.x < 0 || position.x + spriteWidth > windowSize.x) {
        velocity.x = -velocity.x;  // Reverse horizontal direction
    }

    // Bounce off the top or bottom edges
    if (position.y < 0 || position.y + spriteHeight > windowSize.y) {
        velocity.y = -velocity.y;  // Reverse vertical direction
    }
}
