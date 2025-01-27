# Escape the Fall Season - C++ Game

Escape the Fall Season is a fun 2D game where you play as a character avoiding falling logs and branches from a tree. The objective is to avoid collision with the branches and survive as long as possible while the logs continue to fall.

![Screenshot from 2025-01-27 17-05-36](https://github.com/user-attachments/assets/dc3974ba-fdcd-49b9-970c-8a7f163e6fc0)

## Features

- Player movement: Move left or right to avoid falling logs and branches.
- Dynamic log spawning with randomized positions.
- Score tracking: Earn points by avoiding branches.
- Game over screen when a collision with a branch occurs.
- Simple, intuitive controls.
- Fun and challenging gameplay.

## How to Play

1. **Run the game**: After starting the game, use the left and right arrow keys to move your character.
2. **Avoid the falling logs and branches**: The logs will fall from the top, and you need to move your player to avoid colliding with the branches attached to them.
3. **Score**: The score increases as you successfully avoid the falling branches.

## Requirements

Before running the game, make sure you have the following installed:

- **SFML** (Simple and Fast Multimedia Library): For graphics and handling window events.
- **C++ compiler**: Compatible with C++11 or later.
  
### Install SFML

If SFML is not already installed, follow the instructions on the [official SFML website](https://www.sfml-dev.org/download.php) for your operating system.

## Running the Game

To compile and run the game, you can use the following steps:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/ABHIGYAN-MOHANTA/Escape-the-Fall-Season-CPP-Game.git
   cd Escape-the-Fall-Season-CPP-Game
   ```

2. **Build the game and run it** using the `Makefile`:
   ```bash
   make
   ```

3. **Controls**:
   - Use the **Left Arrow** key to move the player to the left.
   - Use the **Right Arrow** key to move the player to the right.

4. **Game Over**: The game ends when the player collides with a falling branch.

## Game Assets

The game uses several graphical assets, including:
- Background
- Tree
- Clouds
- Logs
- Branches
- Player sprite
- "Game Over" screen

Make sure you have the necessary image files located in the appropriate directories for the game to load them correctly. You can find the images used in the game within the `./graphics/` directory, and the font in the `./fonts/` directory.

## Contributing

Feel free to fork the repository and submit pull requests for bug fixes or improvements! Please ensure your code follows the existing style.

## License

This project is open source and available under the [MIT License](LICENSE).

## Acknowledgments

- **SFML**: For the graphics, window, and input handling.
- **Font used**: KOMIKAP_ font.

---

Enjoy playing, and have fun escaping the fall season!
