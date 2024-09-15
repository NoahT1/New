#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SFML/Graphics.hpp>

class HealthBar {
public:
    HealthBar(float maxHealth, float width, float height, const sf::Vector2f& position);
    void setHealth(float health);
    void draw(sf::RenderWindow& window) const;

private:
    float maxHealth;
    float currentHealth;
    sf::RectangleShape background;
    sf::RectangleShape foreground;
};

#endif // HEALTHBAR_H
