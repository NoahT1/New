#include "WelcomeScreen.h"

WelcomeScreen::WelcomeScreen() {
    // You don't need to initialize the font here, it will be passed in loadResources
}

void WelcomeScreen::loadResources(sf::Font& font) {
    // Set up the welcome text
    welcomeText.setFont(font);
    welcomeText.setString("Welcome! Press Enter to Start");
    welcomeText.setCharacterSize(50);  // Set the size of the text
    welcomeText.setFillColor(sf::Color::White);  // Set the text color
    welcomeText.setPosition(150, 300);  // Set the position of the text on screen
}

void WelcomeScreen::handleInput(sf::RenderWindow& window, bool& gameStarted) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // When Enter is pressed, start the game
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            gameStarted = true;
        }
    }
}

void WelcomeScreen::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(welcomeText);  // Draw the welcome text
    window.display();
}
