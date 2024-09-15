#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>

class GameObject {
public:
    virtual ~GameObject() = default;
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual const sf::Sprite& getSprite() const = 0;
};


#endif // GAMEOBJECT_H
