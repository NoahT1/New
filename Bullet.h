#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Bullet : public GameObject {
public:
    Bullet(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& direction);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    const sf::Sprite& getSprite() const override;

private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    float speed;
};

#endif
