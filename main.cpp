#include <SFML/Graphics.hpp>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <vector>   // For dynamic management of logs and branches
#include <iostream> // For debugging purposes

// Struct to hold log and branch info
struct Log
{
    sf::Sprite logSprite;
    sf::Sprite branchSprite;
    float fallSpeed = 0.f;
    float gravity = 0.002f;  // Gravity effect for logs
    bool isActive = true;
    int placement = -1;  // 0 for left, 1 for right
};

// Function to update log and branch movement
void updateLog(Log& log) {
    log.fallSpeed += log.gravity;  // Apply gravity to fallSpeed
    log.logSprite.move(0.f, log.fallSpeed);
    log.branchSprite.move(0.f, log.fallSpeed); // Move the branch with the log
}

// Function to handle player movement
void updatePlayerPosition(sf::Sprite& playerSprite, const sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && playerSprite.getPosition().x > 0) {
        playerSprite.move(-5.f, 0.f); // Move left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && playerSprite.getPosition().x + playerSprite.getGlobalBounds().width < window.getSize().x) {
        playerSprite.move(5.f, 0.f); // Move right
    }
}

// Function to check for collision between player and branch
bool checkCollision(const sf::Sprite& playerSprite, const Log& log) {
    // Get the bounding box of the player and the branch
    sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
    sf::FloatRect branchBounds = log.branchSprite.getGlobalBounds();

    // Check if the player's bounding box intersects with the branch's bounding box
    if (playerBounds.intersects(branchBounds)) {
        return true; // Collision detected
    }
    return false; // No collision
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    // Create the window
    sf::RenderWindow window(sf::VideoMode(1280, 960), "Escape the Fall Season!");

    // Load resources
    sf::Texture backgroundTexture, treeTexture, cloudTexture, logTexture, branchTexture, playerTexture, ripTexture;
    if (!backgroundTexture.loadFromFile("./graphics/background-1280-720.png") ||
        !treeTexture.loadFromFile("./graphics/tree.png") ||
        !cloudTexture.loadFromFile("./graphics/cloud.png") ||
        !logTexture.loadFromFile("./graphics/log.png") ||
        !branchTexture.loadFromFile("./graphics/branch.png") ||
        !playerTexture.loadFromFile("./graphics/player.png") ||
        !ripTexture.loadFromFile("./graphics/rip.png"))
    {
        std::cerr << "Error loading textures!" << std::endl;
        return -1;
    }

    // Load font
    sf::Font font;
    if (!font.loadFromFile("./fonts/KOMIKAP_.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    // Create background, tree, and clouds
    sf::Sprite backgroundSprite(backgroundTexture);
    sf::Sprite treeSprite(treeTexture);
    treeSprite.setPosition(window.getSize().x / 2 - treeSprite.getGlobalBounds().width / 2, 0.f);
    treeSprite.setScale(1.f, 2.f);  // Scale tree for proper size

    sf::Sprite cloud1(cloudTexture), cloud2(cloudTexture), cloud3(cloudTexture), cloud4(cloudTexture);
    cloud1.setPosition(-150.f, 50.f);
    cloud1.setScale(2.5f, 0.5f);
    cloud4.setPosition(900.f, 100.f);
    cloud4.setScale(2.7f, 0.5f);

    // Create player sprite
    sf::Sprite playerSprite(playerTexture);
    playerSprite.setPosition(window.getSize().x / 2 - playerSprite.getGlobalBounds().width / 2, window.getSize().y - playerSprite.getGlobalBounds().height);

    // Tint the player sprite blue to visualize the collision
    // playerSprite.setColor(sf::Color(0, 0, 255, 255)); // Blue tint

    // Prepare log and branch sprites
    std::vector<Log> logs;  // Container for logs and branches
    int score = 0;
    bool gameOver = false;

    // Clock to manage log creation every 1 second
    sf::Clock clock;
    sf::Time spawnInterval = sf::seconds(1); // Spawn a new log every second

    // Create text for score
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(window.getSize().x - 250.f, 10.f); // Position at top right

    // Create rectangle to show collision area
    sf::RectangleShape collisionArea(sf::Vector2f(window.getSize().x, 60.f));
    collisionArea.setPosition(0.f, window.getSize().y - 60.f); // Position just above the bottom
    collisionArea.setFillColor(sf::Color(255, 0, 0, 100)); // Translucent red (alpha = 100)

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!gameOver) {
            // Update player position
            updatePlayerPosition(playerSprite, window);

            // Check if it's time to spawn a new log (every second)
            if (clock.getElapsedTime() >= spawnInterval)
            {
                // Create a new log
                Log newLog;
                newLog.logSprite.setTexture(logTexture);
                newLog.branchSprite.setTexture(branchTexture);

                // Set the branch sprite color to yellow (adding tint)
                newLog.branchSprite.setColor(sf::Color(255, 255, 0, 255));  // Yellow tint

                // Randomize log and branch placement (left or right)
                int randomPlacement = rand() % 2;  // 0 for left, 1 for right
                newLog.placement = randomPlacement; // Save placement for later logging

                float centerX = window.getSize().x / 2.f;

                // Set log position at the top
                newLog.logSprite.setPosition(centerX - newLog.logSprite.getGlobalBounds().width / 2, 0.f);

                // Set branch position relative to the log (left or right)
                if (randomPlacement == 0) {
                    newLog.branchSprite.setRotation(180.f);  // Rotate branch for left side
                    newLog.branchSprite.setPosition(newLog.logSprite.getPosition().x, newLog.logSprite.getPosition().y + newLog.logSprite.getGlobalBounds().height / 2);
                }
                else {
                    newLog.branchSprite.setRotation(0.f);  // No rotation for right side
                    newLog.branchSprite.setPosition(newLog.logSprite.getPosition().x + newLog.logSprite.getGlobalBounds().width, newLog.logSprite.getPosition().y + newLog.logSprite.getGlobalBounds().height / 2);
                }

                // Add new log and branch to the vector
                logs.push_back(newLog);

                // Reset clock for next spawn
                clock.restart();
            }

            // Update and move logs and branches
            for (auto& log : logs)
            {
                if (log.isActive) {
                    updateLog(log);  // Update position based on gravity

                    // Check if the log has fallen off screen
                    if (log.logSprite.getPosition().y > window.getSize().y) {
                        log.isActive = false;  // Mark log as inactive once off-screen
                    }

                    // Check for collision with the branch sprite
                    if (checkCollision(playerSprite, log)) {
                        gameOver = true;  // Game over if collision with branch occurs
                    } else {
                        // Increase score if branch and player are on different sides
                        score++;
                    }
                }
            }

            // Remove inactive logs (those that fell off screen)
            logs.erase(std::remove_if(logs.begin(), logs.end(), [](const Log& log) {
                return !log.isActive;
            }), logs.end());
        }

        // Update score text
        scoreText.setString("Score: " + std::to_string(score));

        // Clear and draw everything
        window.clear();
        window.draw(backgroundSprite);
        window.draw(treeSprite);
        window.draw(cloud1);
        window.draw(cloud4);

        // Draw collision area to visualize the check zone
        window.draw(collisionArea);

        // Draw logs and branches
        for (const auto& log : logs) {
            window.draw(log.branchSprite);  // Only draw the branch
        }

        // Draw player sprite
        window.draw(playerSprite);

        // Display "Game Over" if game is over
        if (gameOver) {
            sf::Sprite gameOverSprite(ripTexture);
            gameOverSprite.setPosition(window.getSize().x / 2 - gameOverSprite.getGlobalBounds().width / 2, window.getSize().y / 2 - gameOverSprite.getGlobalBounds().height / 2);
            window.draw(gameOverSprite);
        }

        // Draw score
        window.draw(scoreText);

        window.display();
    }

    return 0;
}
