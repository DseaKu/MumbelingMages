# MumblingMages

MumblingMages is a 2D action game developed in C using the [Raylib](https://www.raylib.com/) library.

## Gameplay

![Project Demo](assets/demo.gif)

## Description

Control a mage, fight off enemies, and explore the map. The game features projectile combat, enemy AI (Goblins), and a power-up system.

## Features

- **Player Combat:** Cast spells and shoot projectiles (fireballs) to defeat enemies.
- **Enemies:** Fight against Goblins with their own animations and behaviors.
- **Power-ups & Progression:** Collect orbs and power-ups to gain experience and enhance your abilities.
- **2D Graphics:** Sprite-based animations and tile-based maps.

## Tech Stack

- **Language:** C (C99)
- **Library:** Raylib (Graphics, Input, Audio)
- **Build System:** CMake

## Prerequisites

To build and run this project, you need:

- **C Compiler:** GCC, Clang, or MSVC.
- **CMake:** Version 3.11 or higher.
- **Git:** Required to automatically fetch Raylib during the build process.

## Build Instructions

1. **Clone the repository:**

    ```bash
    git clone <repository-url>
    cd MumbelingMages
    ```

2. **Create a build directory:**

    ```bash
    mkdir build
    cd build
    ```

3. **Configure the project:**

    ```bash
    cmake ..
    ```

4. **Build the game:**

    ```bash
    cmake --build .
    ```

## Running the Game

After building, the executable will be located in the `build` directory (or a subdirectory depending on your compiler/OS).

```bash
./game
```

Assets are automatically copied to the build directory, so you should be able to run it directly.

## Project Structure

- `src/`: Source code files.
- `includes/`: Header files.
- `assets/`: Game assets (sprites, maps).
- `docs/`: Documentation and roadmap.
