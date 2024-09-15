#include "MedicPickup.h"

MedicPickup::MedicPickup(const sf::Texture& texture, const sf::Vector2f& position) {
    sprite.setTexture(texture);
    sprite.setPosition(position);

    // Scale the medic pickup to the desired size (optional)
    sprite.setScale(0.1f, 0.1f);  // Adjust the scale if needed
}

void MedicPickup::update(float deltaTime) {
    // No special behavior for now
}

void MedicPickup::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

const sf::Sprite& MedicPickup::getSprite() const {
    return sprite;
}
