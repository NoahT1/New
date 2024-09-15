#ifndef MEDICPICKUP_H
#define MEDICPICKUP_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class MedicPickup : public GameObject {
public:
    MedicPickup(const sf::Texture& texture, const sf::Vector2f& position);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    const sf::Sprite& getSprite() const override;

private:
    sf::Sprite sprite;
};

#endif // MEDICPICKUP_H
