#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation {
public:
    // Constructor to initialize the animation with a texture, number of frames, and switch time.
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

    // Updates the animation frame based on time.
    void update(float deltaTime);

    // Returns the portion of the texture that corresponds to the current frame.
    sf::IntRect getUvRect() const;

private:
    sf::Vector2u imageCount;  // Number of frames in the sprite sheet (columns x rows)
    sf::Vector2u currentImage;  // Current frame in the animation

    float totalTime;  // Time accumulator for switching frames
    float switchTime;  // Time to wait before switching frames

    sf::IntRect uvRect;  // The portion of the texture representing the current frame
};

#endif // ANIMATION_H
