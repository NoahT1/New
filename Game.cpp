#include "Game.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Player.h"
#include "AsteroidSpawner.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include "Opponent.h"


Game::Game()
    : window(sf::VideoMode(1200, 800), "Asteroids Game"),  // Initialize window first
    asteroidSpawner(asteroidTexture, window),  // Now asteroidSpawner can use window
    playerHealth(100.0f),
    score(0),
    playerAmmo(20),
    ammoPickupInterval(4.0f),
    isLaserActive(false),  // Medic pickup spawns after 250 points
    medicPickupActive(false),
    canSpawnMedicPickup(false),
    isScrolling(false),
    scrollSpeed(300.0f),
     gameStarted(false)
{
    window.setFramerateLimit(60);

    // Load the font for the welcome screen and other text
    if (!font.loadFromFile("C:/WINDOWS/FONTS/BELL.TTF")) {  // Change the path to your font
        throw std::runtime_error("Failed to load font");
    }

    // Initialize welcome screen resources
    welcomeScreen.loadResources(font);

    // Initialize the health bar
    healthBar.setSize(sf::Vector2f(200.0f, 20.0f));  // Health bar size
    healthBar.setFillColor(sf::Color::Green);        // Green color for full health
    healthBar.setPosition(10.0f, 40.0f);             // Position health bar

    // Load background texture
    if (!backgroundTexture.loadFromFile("C:/Users/liamt/OneDrive/Documents/Images/space.jpg")) {
        throw std::runtime_error("Failed to load background texture");
    }

    // Load textures for player, asteroids, and bullets
    if (!playerTexture.loadFromFile("C:/Users/liamt/OneDrive/Documents/Images/plane3.png") ||
        !asteroidTexture.loadFromFile("C:/Users/liamt/OneDrive/Documents/Images/rock.png") ||
        !bulletTexture.loadFromFile("C:/Users/liamt/OneDrive/Documents/Images/fire_blue.png")) {
        throw std::runtime_error("Failed to load textures");
    }

    // Load ammo texture
    if (!ammoTexture.loadFromFile("C:/Users/liamt/OneDrive/Documents/Images/832468_miscellaneous_512x512.png")) {
        throw std::runtime_error("Failed to load ammo texture");
    }

    // Load blackhole texture
    if (!blackholeTexture.loadFromFile("C:/Users/liamt/OneDrive/Documents/Images/trinidad-black-hole-clip-art-black-hole-thumbnail.jpg")) {
        throw std::runtime_error("Failed to load blackhole texture");
    }

    // Load the medic pickup texture
    if (!medicTexture.loadFromFile("C:/Users/liamt/OneDrive/Documents/Images/medic.png")) {
        throw std::runtime_error("Failed to load medic texture");
    }

    // Load the laser texture
    if (!laserTexture.loadFromFile("C:/Users/liamt/OneDrive/Documents/Images/image.jpg")) {
        throw std::runtime_error("Failed to load laser texture");
    }

    // Load the opponent texture
    if (!opponentTexture.loadFromFile("C:/Users/liamt/OneDrive/Documents/Images/spaceship.png") ||
        !opponentBulletTexture.loadFromFile("C:/Users/liamt/OneDrive/Documents/Images/fire_red.png")) {
        throw std::runtime_error("Failed to load opponent textures");
    }

    opponentActive = false;


    // Set up the font for score display
    if (!font.loadFromFile("C:/WINDOWS/FONTS/BELL.TTF")) {
        throw std::runtime_error("Failed to load font");
    }

    // Set up the laser sprite but keep it inactive initially
    laserSprite.setTexture(laserTexture);
    laserSprite.setScale(1.0f, 0.2f);
    laserSprite.setPosition(
        window.getSize().x / 2.0f - laserSprite.getGlobalBounds().width / 2.0f,
        window.getSize().y / 2.0f - laserSprite.getGlobalBounds().height / 2.0f
        );

    // Set up the ammo text
    ammoText.setFont(font);
    ammoText.setCharacterSize(30);
    ammoText.setFillColor(sf::Color::White);
    ammoText.setPosition(10, 50);  // Position below the score

    // Set up score text
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    // Add player
    gameObjects.push_back(std::make_unique<Player>(playerTexture));

    // Set up the background
    setupBackground();

    // Spawn the two blackholes
    spawnBlackholes();
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        if (!gameStarted) {
            // Handle welcome screen input and rendering
            welcomeScreen.handleInput(window, gameStarted);  // Check for input to start the game
            welcomeScreen.render(window);  // Render the welcome screen
        } else {
            // If the game has started, run the main game loop
            processEvents();
            float deltaTime = clock.restart().asSeconds();
            update(deltaTime);
            render();
        }
    }
}


void Game::spawnAmmoPickup() {
    sf::Vector2f position(rand() % window.getSize().x, rand() % window.getSize().y);
    ammoPickups.push_back(std::make_unique<AmmoPickup>(ammoTexture, position));
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::Resized) {
            // Adjust all background tiles to match the new window size
            for (auto& tile : backgroundTiles) {
                // You can reposition or adjust each tile's size based on the new window size
                tile.setTextureRect(sf::IntRect(0, 0, event.size.width, event.size.height));
            }
        }

        // Check for MouseButtonPressed event for shooting
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            Player* player = dynamic_cast<Player*>(gameObjects[0].get());

            if (player && playerAmmo > 0 && shootClock.getElapsedTime().asSeconds() > shootCooldown) {
                // Get the mouse position relative to the window
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f playerPosition = player->getPosition();

                // Calculate the direction from the player to the mouse
                sf::Vector2f direction(mousePosition.x - playerPosition.x, mousePosition.y - playerPosition.y);

                // Normalize the direction vector
                float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                if (length != 0) {
                    direction.x /= length;
                    direction.y /= length;
                }

                // Create a new bullet from the player's position, going in the direction of the mouse
                gameObjects.push_back(std::make_unique<Bullet>(bulletTexture, playerPosition, direction));

                // Deduct one ammo
                playerAmmo--;

                // Reset the clock to apply the cooldown
                shootClock.restart();
            }

        }
    }
}


void Game::setupBackground() {
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    // Determine how many tiles are needed in each direction
    int numColumns = (windowSize.x + textureSize.x - 1) / textureSize.x;  // Ceiling division
    int numRows = (windowSize.y + textureSize.y - 1) / textureSize.y;  // Ceiling division

    // Create background tiles
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numColumns; ++col) {
            sf::Sprite tile;
            tile.setTexture(backgroundTexture);
            tile.setPosition(col * textureSize.x, row * textureSize.y);
            backgroundTiles.push_back(tile);
        }
    }
}

void Game::spawnBlackholes() {
    // Set random initial positions and velocities for the blackholes
    sf::Vector2f position1(rand() % window.getSize().x, rand() % window.getSize().y);
    sf::Vector2f velocity1((rand() % 100 + 50) * (rand() % 2 ? 1 : -1), (rand() % 100 + 50) * (rand() % 2 ? 1 : -1));

    sf::Vector2f position2(rand() % window.getSize().x, rand() % window.getSize().y);
    sf::Vector2f velocity2((rand() % 100 + 50) * (rand() % 2 ? 1 : -1), (rand() % 100 + 50) * (rand() % 2 ? 1 : -1));

    // Add two blackholes to the game
    blackholes.push_back(std::make_unique<Blackhole>(blackholeTexture, position1, velocity1));
    blackholes.push_back(std::make_unique<Blackhole>(blackholeTexture, position2, velocity2));
}

// Vector to store opponent bullet velocities
std::vector<sf::Vector2f> opponentBulletVelocities;


void Game::update(float deltaTime) {
    Player* player = dynamic_cast<Player*>(gameObjects[0].get());

    // Handle player movement and boundary checking
    if (player) {
        sf::Vector2f movement(0.f, 0.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            movement.y -= player->getSpeed() * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            movement.y += player->getSpeed() * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            movement.x -= player->getSpeed() * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            movement.x += player->getSpeed() * deltaTime;
        }

        sf::Vector2f newPosition = player->getPosition() + movement;
        float spriteWidth = player->getSprite().getGlobalBounds().width;
        float spriteHeight = player->getSprite().getGlobalBounds().height;

        // Boundary checking
        if (newPosition.x < 0) newPosition.x = 0;
        else if (newPosition.x + spriteWidth > 1200) newPosition.x = 1200 - spriteWidth;

        if (newPosition.y < 0) newPosition.y = 0;
        else if (newPosition.y + spriteHeight > 800) newPosition.y = 800 - spriteHeight;

        player->setPosition(newPosition);

        // Handle medic pickup spawning and player interaction
        if (score >= 250 && !medicPickupActive) {
            spawnMedicPickup();
            medicPickupActive = true;
        }

        // Activate laser at 750 points
        if (score >= 750 && !isLaserActive) {
            isLaserActive = true;
        }

        // Check player collision with laser
        if (isLaserActive && player->getSprite().getGlobalBounds().intersects(laserSprite.getGlobalBounds())) {
            std::cout << "Player hit the laser! Game Over!" << std::endl;
            window.close();
            return;
        }

        // Check player collision with medic pickup
        if (medicPickup && player->getSprite().getGlobalBounds().intersects(medicPickup->getSprite().getGlobalBounds())) {
            playerHealth = std::min(playerHealth + 25.0f, 100.0f);
            updateHealthBar();
            medicPickup.reset();
            medicPickupActive = false;
        }

        // Scroll background when player reaches 500 points
        if (score >= 500 && !isScrolling) {
            isScrolling = true;
        }
        if (isScrolling) {
            scrollBackground(deltaTime);
        }

        // Rotate player to face mouse
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f playerPosition = player->getPosition();
        float dx = mousePosition.x - playerPosition.x;
        float dy = mousePosition.y - playerPosition.y;
        player->setRotation(std::atan2(dy, dx) * 180 / 3.14159265f + 90);
    }

    // Update ammo display
    ammoText.setString("Ammo: " + std::to_string(playerAmmo));


    // Check if opponent should spawn at score milestones (200, 400, 600, 800)
    if (!opponentActive && (score == 200 || score == 400 || score == 600 || score == 800)) {
        opponent = std::make_unique<Opponent>(opponentTexture, sf::Vector2f(600, 100));  // Spawns at the top center
        opponentActive = true;
    }

    // If the opponent is active, update its position, and check if it should shoot
    if (opponentActive) {
        opponent->update(deltaTime);  // Update opponent movement

        if (player) {
            // Opponent shoots bullets towards the player, now storing velocities
            opponent->shoot(opponentBullets, opponentBulletVelocities, opponentBulletTexture, player->getPosition());
        }

        // If the opponent is destroyed, deactivate it
        if (opponent->isDestroyed()) {
            opponentActive = false;
            opponent.reset();  // Remove the opponent
        }
    }

    // Move opponent bullets according to their velocities
    for (size_t i = 0; i < opponentBullets.size(); ++i) {
        opponentBullets[i].move(opponentBulletVelocities[i] * deltaTime);  // Move bullet by its velocity
    }

    // Remove opponent bullets that go off-screen and corresponding velocities
    for (size_t i = 0; i < opponentBullets.size(); ) {
        if (opponentBullets[i].getPosition().y > 800 || opponentBullets[i].getPosition().y < 0 ||
            opponentBullets[i].getPosition().x > 1200 || opponentBullets[i].getPosition().x < 0) {
            opponentBullets.erase(opponentBullets.begin() + i);  // Remove bullet
            opponentBulletVelocities.erase(opponentBulletVelocities.begin() + i);  // Remove corresponding velocity
        } else {
            ++i;
        }
    }

    // Handle collisions between opponent bullets and the player
    if (player) {
        for (size_t i = 0; i < opponentBullets.size(); ++i) {
            if (opponentBullets[i].getGlobalBounds().intersects(player->getSprite().getGlobalBounds())) {
                playerHealth -= 20.0f;  // Player now takes 20 damage when hit by an opponent bullet
                updateHealthBar();
                opponentBullets.erase(opponentBullets.begin() + i);  // Remove the bullet after it hits the player
                opponentBulletVelocities.erase(opponentBulletVelocities.begin() + i);  // Remove corresponding velocity
                break;  // Exit the loop after handling one bullet hit
            }
        }

        // If player's health drops to or below 0, the game ends
        if (playerHealth <= 0) {
            std::cout << "Player is dead! Game Over!" << std::endl;
            window.close();  // Close the game window
        }
    }


    // Handle player bullet-opponent collisions
    for (size_t i = 0; i < gameObjects.size(); ++i) {
        Bullet* bullet = dynamic_cast<Bullet*>(gameObjects[i].get());
        if (bullet && opponentActive) {
            // Check if the player's bullet intersects with the opponent's sprite
            if (bullet->getSprite().getGlobalBounds().intersects(opponent->getSprite().getGlobalBounds())) {
                opponent->takeDamage(10.0f);  // Opponent takes 10 damage when hit by a player's bullet
                gameObjects.erase(gameObjects.begin() + i);  // Remove the player's bullet
                break;  // No need to check this bullet anymore
            }
        }
    }

    // Update blackholes and check collision
    for (auto& blackhole : blackholes) {
        blackhole->update(deltaTime);
        blackhole->bounceOffWalls(window);
        if (player && blackhole->getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds())) {
            std::cout << "Player hit a blackhole! Game Over!" << std::endl;
            window.close();
            return;
        }
    }

    // Handle ammo pickup spawning
    if (ammoPickupClock.getElapsedTime().asSeconds() >= ammoPickupInterval) {
        spawnAmmoPickup();
        ammoPickupClock.restart();  // Reset the clock to track the next spawn time
    }


    // Check player collision with ammo pickups
    for (auto it = ammoPickups.begin(); it != ammoPickups.end();) {
        if (player && player->getSprite().getGlobalBounds().intersects((*it)->getSprite().getGlobalBounds())) {
            playerAmmo = std::min(playerAmmo + 5, 30);
            it = ammoPickups.erase(it);
        } else {
            ++it;
        }
    }

    // Check for game over condition at 1000 points
    if (score >= 1000) {
        std::cout << "Congratulations! You reached 1000 points. Game Over!" << std::endl;
        window.close();
        return;
    }

    // Set a limit for the maximum number of asteroids
    const int maxAsteroids = 10;  // Adjust this number to your desired limit

    // Check the number of asteroids on screen
    if (asteroidSpawner.asteroids.size() < maxAsteroids) {
        // Increase the asteroid spawn interval
        static sf::Clock asteroidSpawnClock;
        if (asteroidSpawnClock.getElapsedTime().asSeconds() > 1.5f) {  // Spawns every 1.5 seconds
            asteroidSpawner.spawnAsteroid();
            asteroidSpawnClock.restart();
        }
    }

    // Update asteroids
    asteroidSpawner.updateAsteroids(deltaTime);

    // Update game objects (bullets, etc.)
    for (auto& object : gameObjects) {
        object->update(deltaTime);
    }

    // Remove bullets off-screen
    gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(),
                                     [&](const std::unique_ptr<GameObject>& obj) {
                                         Bullet* bullet = dynamic_cast<Bullet*>(obj.get());
                                         if (bullet) {
                                             sf::Vector2f position = bullet->getSprite().getPosition();
                                             return position.y < 0 || position.y > 800 || position.x < 0 || position.x > 1200;
                                         }
                                         return false;
                                     }), gameObjects.end());

    // Handle player-asteroid collisions
    for (size_t i = 0; i < asteroidSpawner.asteroids.size(); ++i) {
        Asteroid& asteroid = asteroidSpawner.asteroids[i];
        if (player && player->getSprite().getGlobalBounds().intersects(asteroid.getSprite().getGlobalBounds())) {
            if (!asteroid.hasDealtDamage()) {
                playerHealth -= asteroid.getDamage();
                updateHealthBar();
                asteroid.setDealtDamage();

                if (playerHealth <= 0) {
                    std::cout << "Player is dead! Game Over!" << std::endl;
                    window.close();
                    return;
                }
            }
        }
    }

    // Handle bullet-asteroid collisions
    std::vector<size_t> bulletsToRemove;
    std::vector<size_t> asteroidsToRemove;

    for (size_t i = 0; i < gameObjects.size(); ++i) {
        Bullet* bullet = dynamic_cast<Bullet*>(gameObjects[i].get());
        if (bullet) {
            for (size_t j = 0; j < asteroidSpawner.asteroids.size(); ++j) {
                Asteroid& asteroid = asteroidSpawner.asteroids[j];

                // Check if the bullet collides with the asteroid
                if (bullet->getSprite().getGlobalBounds().intersects(asteroid.getSprite().getGlobalBounds())) {
                    bulletsToRemove.push_back(i);  // Mark the bullet for removal
                    asteroidsToRemove.push_back(j);  // Mark the asteroid for removal

                    // Spawn smaller asteroids based on the asteroid size
                    if (asteroid.getSize() == AsteroidSize::Large) {
                        spawnSmallerAsteroids(asteroid.getSprite().getPosition(), AsteroidSize::Medium);
                    } else if (asteroid.getSize() == AsteroidSize::Medium) {
                        spawnSmallerAsteroids(asteroid.getSprite().getPosition(), AsteroidSize::Small);
                    }

                    // Increase the player's score
                    score += 10;
                    updateScoreText();

                    // Break to avoid checking this asteroid further (as it's destroyed)
                    break;
                }
            }
        }
    }

    // Remove marked bullets in reverse order to avoid invalidating indices
    std::sort(bulletsToRemove.begin(), bulletsToRemove.end(), std::greater<size_t>());
    for (size_t index : bulletsToRemove) {
        gameObjects.erase(gameObjects.begin() + index);
    }

    // Remove marked asteroids in reverse order to avoid invalidating indices
    std::sort(asteroidsToRemove.begin(), asteroidsToRemove.end(), std::greater<size_t>());
    for (size_t index : asteroidsToRemove) {
        asteroidSpawner.asteroids.erase(asteroidSpawner.asteroids.begin() + index);
    }
}

void Game::render() {
    window.clear();

    // Draw all background tiles
    for (const auto& tile : backgroundTiles) {
        window.draw(tile);
    }

    // Draw all game objects
    for (const auto& object : gameObjects) {
        object->draw(window);
    }

    // Draw the opponent if it's active
    if (opponentActive) {
        opponent->draw(window);

        // Draw opponent's bullets
        for (const auto& bullet : opponentBullets) {
            window.draw(bullet);
        }
    }

    // Draw all ammo pickups
    for (const auto& ammoPickup : ammoPickups) {
        ammoPickup->draw(window);
    }

    // Draw the blackholes
    for (const auto& blackhole : blackholes) {
        blackhole->draw(window);
    }

    // Draw the medic pickup if it exists
    if (medicPickup) {
        medicPickup->draw(window);
    }

    // If the laser is active, draw it in the middle of the screen
    if (isLaserActive) {
        window.draw(laserSprite);
    }

    // Draw all asteroids
    asteroidSpawner.drawAsteroids(window);

    // Draw score and ammo text
    window.draw(scoreText);
    window.draw(ammoText);
    window.draw(healthBar);

    window.display();
}

void Game::updateScoreText() {
    scoreText.setString("Score: " + std::to_string(score));
}

void Game::updateHealthBar() {
    // Ensure the health percentage stays within 0 to 100
    float healthPercentage = std::max(0.0f, playerHealth) / 100.0f;  // Assuming 100 is max health

    // Update the width of the health bar based on the player's health
    healthBar.setSize(sf::Vector2f(200.0f * healthPercentage, 20.0f));  // Shrink width as health decreases

    // Change color based on health percentage
    if (playerHealth > 80) {
        healthBar.setFillColor(sf::Color::Green);  // Healthy (green)
    } else if (playerHealth > 40) {
        healthBar.setFillColor(sf::Color::Yellow);  // Moderate (yellow)
    } else {
        healthBar.setFillColor(sf::Color::Red);  // Low health (red)
    }
}

void Game::spawnMedicPickup() {
    // Generate a random position within the window bounds
    float xPosition = static_cast<float>(rand() % window.getSize().x);
    float yPosition = static_cast<float>(rand() % window.getSize().y);

    // Create a new medic pickup at the random position
    medicPickup = std::make_unique<MedicPickup>(medicTexture, sf::Vector2f(xPosition, yPosition));

    medicPickupActive = true;  // Mark the medic pickup as active
}

void Game::scrollBackground(float deltaTime) {
    // Move all background tiles down the screen (visual effect)
    for (auto& tile : backgroundTiles) {
        sf::Vector2f newPosition = tile.getPosition();
        newPosition.y += scrollSpeed * deltaTime;  // Scroll downward (increase Y)

        // If the tile moves completely out of view, reposition it at the top to create an endless scrolling effect
        if (newPosition.y > window.getSize().y) {
            newPosition.y = -tile.getGlobalBounds().height;  // Move the tile back to the top
        }

        tile.setPosition(newPosition);
    }
}

void Game::spawnSmallerAsteroids(const sf::Vector2f& position, AsteroidSize newSize) {
    for (int i = 0; i < 2; ++i) {  // Break into 2 smaller pieces
        sf::Vector2f velocity(
            static_cast<float>(rand() % 200 - 100),  // Random horizontal movement
            static_cast<float>(rand() % 200 + 100)   // Random vertical movement (faster downward)
            );

        // Create the smaller asteroid and add it to the asteroid spawner's list
        asteroidSpawner.asteroids.emplace_back(asteroidTexture, Regular, newSize, position, velocity);
    }
}
