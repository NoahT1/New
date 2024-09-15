#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <SFML/Graphics.hpp>

class WelcomeScreen {
public:
    WelcomeScreen();

    // Load resources for the welcome screen
    void loadResources(sf::Font& font);

    // Handle input for the welcome screen
    void handleInput(sf::RenderWindow& window, bool& gameStarted);

    // Render the welcome screen
    void render(sf::RenderWindow& window);

private:
    sf::Text welcomeText;  // Text for displaying the welcome message
};

#endif // WELCOMESCREEN_H
