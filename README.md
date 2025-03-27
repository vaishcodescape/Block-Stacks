# **Block-Stacks**

## **Overview**
**Block-Stacks** is a Tetris-based game developed in pure C++ by **vaishcodescape (Aditya Vaish)** and **sam5506 (Samyak Shah)**. The game features colorful Tetromino pieces, dynamic gameplay, and a high-score tracking system. This project was part of our **Data Structure Lab Course IT-206 in the 2nd Semester of B.Tech (Engineering).**

## **Features**
- 🎮 **Classic Tetris-style gameplay**
- 🔄 **Smooth piece movement and rotation**
- 🏆 **High-score saving mechanism**
- 💻 **Supports Windows and Linux**
- 🎨 **Colorful blocks using ANSI escape codes**

## **Installation & Compilation**
### **Prerequisites**
- A **C++ compiler** (G++ or MSVC)
- **Terminal or command prompt** to run the game
- **Git** (for cloning the repository)

### **Cloning the Repository**
To clone the project from GitHub, run:
```sh
git clone https://github.com/your-username/block-stacks.git
cd block-stacks
```

### **Compilation**
#### **On Windows (using MinGW)**
```sh
g++ block_stacks.cpp -o block_stacks.exe
```
#### **On Linux/Mac**
```sh
g++ block_stacks.cpp -o block_stacks
```

## **Running the Game**
### **On Windows**
```sh
block_stacks.exe
```
### **On Linux/Mac**
```sh
./block_stacks
```

## **Controls**
- 🡄 **A** - Move left
- 🡆 **D** - Move right
- 🡇 **S** - Move down
- 🔄 **W** - Rotate piece

## **How to Play**
1. **Blocks (Tetrominoes) will fall from the top.**
2. **Move and rotate them to fit within the grid.**
3. **Complete horizontal lines to clear them and earn points.**
4. **The game speeds up as you score more points.**
5. **The game ends when the blocks reach the top.**

## **High Score**
🏆 The game saves the highest score to `highscore.txt` and updates it when a new high score is achieved.

## **Code Overview**
### **1. Classes and Structs**
- **Tetromino Class**: Handles Tetromino shapes and their movement.
- **Game Board**: Manages grid updates, row clearing, and scoring.
- **Input Handling**: Uses `_getch()` for real-time movement control.

### **2. Game Logic**
- **Gravity Mechanic**: Blocks fall at increasing speeds as the game progresses.
- **Collision Detection**: Prevents blocks from overlapping.
- **Score System**: Points increase with each cleared row.

### **3. Cross-Platform Compatibility**
- **Windows**: Uses `conio.h` for keyboard input.
- **Linux/macOS**: Uses `termios.h` for non-blocking input handling.

## **Contributing**
We welcome contributions! To contribute:
1. **Fork the repository.**
2. **Create a new branch** (`git checkout -b feature-branch`).
3. **Commit your changes** (`git commit -m "Add new feature"`).
4. **Push to your branch** (`git push origin feature-branch`).
5. **Open a Pull Request.**

## **License**
📜 This project is **open-source** and available for modification and distribution.

## **Contributors**
- **vaishcodescape (Aditya Vaish)**
- **sam5506 (Samyak Shah)**

Enjoy playing **Block-Stacks** and happy stacking! 🏗️🎮

