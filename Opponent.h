#ifndef OPPONENT_H
#define OPPONENT_H

#include <SFML/Graphics.hpp>

class Opponent {
public:
    Opponent(const sf::Texture& texture, const sf::Vector2f& position);

    void update(float deltaTime);  // Make sure this method is declared
    void draw(sf::RenderWindow& window);
    void takeDamage(float amount);
    bool isDestroyed() const;
    // Modify the shoot method to include velocities
    void shoot(std::vector<sf::Sprite>& bullets, std::vector<sf::Vector2f>& bulletVelocities, const sf::Texture& bulletTexture, const sf::Vector2f& playerPosition);

      void updateHealthBar();
    const sf::Sprite& getSprite() const;

private:
    sf::Sprite sprite;
    float health;
    float shootCooldown;
    sf::Clock shootClock;
    sf::RectangleShape healthBar;
      float maxHealth;
};

#endif // OPPONENT_H
