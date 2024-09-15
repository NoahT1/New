#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Blackhole : public GameObject {
public:
    Blackhole(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& velocity);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    const sf::Sprite& getSprite() const override;

    void bounceOffWalls(const sf::RenderWindow& window);  // Handles bouncing behavior

private:
    sf::Sprite sprite;
    sf::Vector2f velocity;  // Direction and speed
};

#endif // BLACKHOLE_H
