#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
    VideoMode vm(1920, 1080);
    // RenderWindow window(vm, "Timber", Style::Fullscreen);
    RenderWindow window(vm, "Timber");

    window.setFramerateLimit(60);

    // Create an object that will hold a graphics on the GPU
    Texture backgroundTexture, cloudTexture, treeTexture, beeTexture;
    if (!backgroundTexture.loadFromFile("graphics/background.png") ||
        !cloudTexture.loadFromFile("graphics/cloud.png") ||
        !treeTexture.loadFromFile("graphics/tree.png") ||
        !beeTexture.loadFromFile("graphics/bee.png")
    ) {
        // Handle error if the texture fails to load
        return -1;
    }

    // Create a sprite to display the texture
    Sprite backgroundSprite(backgroundTexture);
    Sprite cloud1(cloudTexture), cloud2(cloudTexture), cloud5(cloudTexture), cloud6(cloudTexture);
    cloud1.setPosition(-150, 0);
    cloud1.setScale(1, 1);
    cloud2.setPosition(-90, 0);
    cloud2.setScale(2, 1);

    cloud5.setPosition(1600, 0);
    cloud5.setScale(2, 1);

    cloud6.setPosition(1720, 0);
    cloud6.setScale(1, 1);

    // Bee
    Sprite bee(beeTexture);
    bee.setPosition(0, 500);

    bool beeActive = false;
    float beeSpeed = 0.0f;

    // Create a sprite for tree
    Sprite tree(treeTexture);
    tree.setPosition(1920/2 - tree.getLocalBounds().width/2, 0);
    tree.setScale(1,1);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Handle player input
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        // Update the scene
        // (You can add code for updating the game here)

        // Draw the scene
        // First, clear everything
        window.clear();

        // Draw the sprite with the background texture
        window.draw(backgroundSprite);
        window.draw(cloud1);
        window.draw(cloud2);

        window.draw(cloud5);
        window.draw(cloud6);

        window.draw(tree);
        window.draw(bee);

        // Show everything we draw
        window.display();
    }

    return 0;
}
