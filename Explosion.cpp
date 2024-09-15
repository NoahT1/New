#include "Explosion.h"

Explosion::Explosion(sf::Texture* texture, sf::Vector2f position, sf::Vector2u imageCount, float switchTime)
    : animation(texture, imageCount, switchTime), finished(false) {
    sprite.setTexture(*texture);
    sprite.setPosition(position);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

void Explosion::update(float deltaTime) {
    // Update the explosion animation
    animation.update(deltaTime);
    sprite.setTextureRect(animation.getUvRect());

    // If the animation has reached its last frame, mark the explosion as finished
    if (animation.getUvRect().left + animation.getUvRect().width >= sprite.getTexture()->getSize().x) {
        finished = true;
    }
}

void Explosion::draw(sf::RenderWindow& window) const {
    window.draw(sprite);  // Draw the explosion sprite
}

const sf::Sprite& Explosion::getSprite() const {
    return sprite;  // Return a const reference to the sprite, matching GameObject's signature
}

bool Explosion::isFinished() const {
    return finished;  // Return true if the explosion animation is done
}
