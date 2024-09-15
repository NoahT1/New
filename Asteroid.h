#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>

// Enum to define the size of the asteroid
enum AsteroidSize {
    Large,
    Medium,
    Small
};

// Enum to define the type of asteroid (can be expanded for different types if needed)
enum AsteroidType {
    Regular
};

class Asteroid {
public:
    // Constructor: initialize asteroid with texture, type, size, position, and velocity
    Asteroid(const sf::Texture& texture, AsteroidType type, AsteroidSize size, const sf::Vector2f& position, const sf::Vector2f& velocity);

    // Update asteroid position based on velocity and deltaTime, handle screen wrapping
    void update(float deltaTime);

    // Draw asteroid to the screen
    void draw(sf::RenderWindow& window) const;

    // Get the size of the asteroid
    AsteroidSize getSize() const;

    // Get the damage dealt by the asteroid (based on size)
    float getDamage() const;

    // Check if asteroid has already dealt damage
    bool hasDealtDamage() const;

    // Mark the asteroid as having dealt damage (to avoid dealing damage multiple times)
    void setDealtDamage();

    // Get the sprite of the asteroid (used for collision detection)
    const sf::Sprite& getSprite() const { return sprite; }

private:
    AsteroidType type;            // The type of asteroid (currently only Regular)
    AsteroidSize size;            // The size of the asteroid (Large, Medium, Small)
    sf::Sprite sprite;            // The sprite representing the asteroid
    sf::Vector2f velocity;        // The velocity of the asteroid (movement direction and speed)
    bool dealtDamage;             // Flag to track whether the asteroid has already dealt damage
};

#endif // ASTEROID_H
