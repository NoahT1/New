#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Player : public GameObject {
public:
    Player(const sf::Texture& texture);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    float getSpeed() const;
    const sf::Sprite& getSprite() const;
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    void setRotation(float angle);
    int getAmmoCapacity() const;
    void increaseAmmo(int amount);


private:
    sf::Sprite sprite;
    float speed;
    int ammoCapacity;       // Current ammo capacity
    int maxAmmoCapacity;    // Maximum ammo capacity
};

#endif // PLAYER_H
