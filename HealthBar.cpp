#include "HealthBar.h"

HealthBar::HealthBar(float maxHealth, float width, float height, const sf::Vector2f& position)
    : maxHealth(maxHealth), currentHealth(maxHealth) {
    // Background of the health bar
    background.setSize(sf::Vector2f(width, height));
    background.setPosition(position);
    background.setFillColor(sf::Color::Black);

    // Foreground of the health bar (shows current health)
    foreground.setSize(sf::Vector2f(width, height));
    foreground.setPosition(position);
    foreground.setFillColor(sf::Color::Green);
}

void HealthBar::setHealth(float health) {
    currentHealth = health;
    float healthPercentage = currentHealth / maxHealth;
    foreground.setSize(sf::Vector2f(background.getSize().x * healthPercentage, background.getSize().y));

    // Change color to red if health is low
    if (currentHealth < maxHealth * 0.25f) {
        foreground.setFillColor(sf::Color::Red);
    } else {
        foreground.setFillColor(sf::Color::Green);
    }
}

void HealthBar::draw(sf::RenderWindow& window) const {
    window.draw(background);
    window.draw(foreground);
}
