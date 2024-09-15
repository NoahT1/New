#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
    : imageCount(imageCount), totalTime(0.0f), switchTime(switchTime) {
    currentImage.x = 0;  // Start at the first frame
    uvRect.width = texture->getSize().x / imageCount.x;  // Width of each frame
    uvRect.height = texture->getSize().y / imageCount.y;  // Height of each frame
}

void Animation::update(float deltaTime) {
    totalTime += deltaTime;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;  // Move to the next frame

        if (currentImage.x >= imageCount.x) {
            currentImage.x = 0;  // Loop back to the first frame
        }
    }

    // Set the part of the texture to display the current frame
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}

sf::IntRect Animation::getUvRect() const {
    return uvRect;
}
