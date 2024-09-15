#ifndef AMMOPICKUP_H
#define AMMOPICKUP_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class AmmoPickup : public GameObject {
public:
    AmmoPickup(const sf::Texture& texture, const sf::Vector2f& position);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    const sf::Sprite& getSprite() const override;

private:
    sf::Sprite sprite;
};

#endif // AMMOPICKUP_H
