# Tic-Tac-Toe in C++ with SFML 🎮

A clean and simple Tic-Tac-Toe game built with C++ and the modern multimedia library [SFML](https://www.sfml-dev.org/).
This project features a classic player vs. AI gameplay loop within a responsive graphical window.

![Gameplay demo](gifs/GameDemo.gif)


# About This Project
This project was initially developed as part of an online course to practice object-oriented programming (OOP) principles in C++ and to learn the fundamentals of the SFML library.

While the core game logic and structure are based on the course curriculum, I have made several key modifications and improvements:

*Modernization:* 

The original code was updated to be fully compatible with the latest SFML 3.x API, which required significant changes from older versions.

*Personal Enhancements:*

Designed and implemented unique game-over screens for each possible outcome (Win, Loss, and Draw), enhancing the user experience.

*Code Refinements:* 

The codebase was refactored in several areas for better readability and maintainability.

This project serves as a practical demonstration of my ability to understand, adapt, and build upon an existing C++ codebase.

# Features ✨
Classic 3x3 Tic-Tac-Toe gameplay.

Engaging Player vs. AI mode.

Clear win, lose, and draw state detection.

A clean, window-based UI powered by SFML.

Well-structured and commented source code, ideal for learning.

# Requirements 🔧
A C++17 compliant compiler (like GCC, Clang, or MSVC).

SFML 3.0 or newer (Graphics, Window, and System modules).

# Building and Running 🚀
1. Clone the Repository
Bash

git clone https://github.com/HighsR/SFML-Tic-Tac-Toe.git
cd SFML-Tic-Tac-Toe

2. Compile the Code
The following is a basic compilation command using g++. You must update the paths to your SFML installation.

Bash

# Make sure you are in the project's root directory
g++ -std=c++17 -I/path/to/your/sfml/include -L/path/to/your/sfml/lib \
    src/*.cpp -o TicTacToe \
    -lsfml-graphics -lsfml-window -lsfml-system

Note: 

For a more robust and cross-platform build process, using a build system like CMake is highly recommended.

3. Run the Game
Once compiled successfully, an executable file will be created.

Bash

# On Linux / macOS
./TicTacToe

# On Windows
TicTacToe.exe
