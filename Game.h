#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "AmmoPickup.h"
#include "Blackhole.h"
#include "GameObject.h"
#include "AsteroidSpawner.h"
#include "Bullet.h"
#include "Player.h"
#include "MedicPickup.h"
#include "WelcomeScreen.h"  // Include WelcomeScreen header
#include "Opponent.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    void spawnSmallerAsteroids(const sf::Vector2f& position, AsteroidSize size);
    void updateScoreText();
    void updateHealthBar();
    void spawnAmmoPickup();
    void spawnMedicPickup();
    void scrollBackground(float deltaTime);
    void spawnBlackholes();
    void setupBackground();

    sf::RenderWindow window;
    sf::Texture playerTexture;
    sf::Texture asteroidTexture;
    sf::Texture bulletTexture;
    sf::Texture ammoTexture;
    sf::Texture blackholeTexture;
    sf::Texture medicTexture;
    sf::Texture laserTexture;
    sf::Texture backgroundTexture;
    sf::Font font;

    sf::Text scoreText;
    sf::Text ammoText;

    sf::Sprite laserSprite;
    sf::RectangleShape healthBar;

    std::vector<std::unique_ptr<GameObject>> gameObjects;
    std::vector<std::unique_ptr<AmmoPickup>> ammoPickups;
    std::vector<std::unique_ptr<Blackhole>> blackholes;
    std::vector<sf::Sprite> backgroundTiles;

    std::unique_ptr<MedicPickup> medicPickup;

    AsteroidSpawner asteroidSpawner;

    float playerHealth;
    int score;
    int playerAmmo;
    float ammoPickupInterval;
    bool isLaserActive;
    bool medicPickupActive;
    bool canSpawnMedicPickup;
    bool isScrolling;
    float scrollSpeed;
    bool gameStarted;

    WelcomeScreen welcomeScreen;  // <--- Declare welcomeScreen as a member
    sf::Clock shootClock;  // <--- Declare shootClock here
    sf::Clock ammoPickupClock;      // <--- Declare ammoPickupClock here
    const float shootCooldown = 0.2f;  // <--- Declare shootCooldown as a constant

    std::unique_ptr<Opponent> opponent;
    bool opponentActive;
    std::vector<sf::Sprite> opponentBullets;
    sf::Texture opponentTexture;
    sf::Texture opponentBulletTexture;
};

#endif // GAME_H
