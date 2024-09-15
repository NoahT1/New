#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "GameObject.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class Explosion : public GameObject {
public:
    Explosion(sf::Texture* texture, sf::Vector2f position, sf::Vector2u imageCount, float switchTime);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;

    // Return a const reference to the sprite, as per the GameObject base class
    const sf::Sprite& getSprite() const override;

    bool isFinished() const;  // Check if the explosion animation is complete

private:
    sf::Sprite sprite;  // Explosion sprite
    Animation animation;  // Animation handler
    bool finished;  // To track when the explosion is done
};

#endif // EXPLOSION_H
