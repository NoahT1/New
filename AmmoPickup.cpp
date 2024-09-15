#include "AmmoPickup.h"

AmmoPickup::AmmoPickup(const sf::Texture& texture, const sf::Vector2f& position) {
    sprite.setTexture(texture);
    sprite.setPosition(position);

    // Scale down the sprite to make it smaller
    sprite.setScale(0.1f, 0.1f);  // Adjust this value as needed to get the desired size
}

void AmmoPickup::update(float deltaTime) {
    // No behavior for now, but could be added later
}

void AmmoPickup::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

const sf::Sprite& AmmoPickup::getSprite() const {
    return sprite;
}
