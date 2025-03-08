/*Block-Stacks*/
//A Tetris Based game made in pure C++
//Made by vaishcodescape and sam5506
#include <iostream>
#include <vector>
#include <cstring> // For memcpy()
#include <cstdlib> // For rand()
#include <ctime>   // For seeding random

#ifdef _WIN32
    #include <conio.h>   // For _kbhit() and _getch()
    #include <windows.h> // For Sleep()
#else
    #include <unistd.h>  // For usleep()
    #include <termios.h> // For non-blocking keyboard input
    #include <fcntl.h>

    int _kbhit() {
        struct termios oldt, newt;
        int ch;
        int oldf;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);

        if (ch != EOF) {
            ungetc(ch, stdin);
            return 1;
        }

        return 0;
    }

    int _getch() {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }

    void Sleep(int ms) {
        usleep(ms * 1000); // Convert milliseconds to microseconds
    }
#endif

using namespace std;

// Game board size
const int WIDTH = 10;
const int HEIGHT = 20;
int board[HEIGHT][WIDTH] = {0}; // 0 means empty, 1 means filled

// Tetromino shapes (4x4 representation)
const int TETROMINOS[7][4][4] = {
    {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}},  // I
    {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},  // O
    {{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},  // T
    {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},  // S
    {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}},  // Z
    {{1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},  // J
    {{0,0,1,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}   // L
};

// Tetromino structure
struct Tetromino {
    int shape[4][4];
    int x, y; // Position

    // Constructor
    Tetromino(int type) {
        memcpy(shape, TETROMINOS[type], sizeof(shape));
        x = WIDTH / 2 - 2;
        y = 0;
    }

    // Rotate tetromino 90 degrees
    void rotate() {
        int temp[4][4] = {0};
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                temp[j][3 - i] = shape[i][j]; 
        memcpy(shape, temp, sizeof(shape));
    }
};

// Draw the game board and tetromino
void draw(Tetromino &t) {
    system("clear"); // Use "cls" on Windows
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            bool isTetromino = false;
            for (int r = 0; r < 4; r++)
                for (int c = 0; c < 4; c++)
                    if (t.shape[r][c] && i == t.y + r && j == t.x + c)
                        isTetromino = true;
            if (isTetromino)
                cout << "# ";
            else if (board[i][j])
                cout << "* ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}

// Move tetromino
void moveTetromino(Tetromino &t, int dx, int dy) {
    t.x += dx;
    t.y += dy;
}

// Place tetromino on board
void placeTetromino(Tetromino &t) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (t.shape[i][j])
                board[t.y + i][t.x + j] = 1;
}

// Main game loop
void gameLoop() {
    srand(time(0));
    Tetromino currentTetromino(rand() % 7);

    while (true) {
        draw(currentTetromino);

        if (_kbhit()) {
            char key = _getch();
            if (key == 'a') moveTetromino(currentTetromino, -1, 0);
            if (key == 'd') moveTetromino(currentTetromino, 1, 0);
            if (key == 'w') currentTetromino.rotate();
            if (key == 's') moveTetromino(currentTetromino, 0, 1);
        }

        // Move tetromino down every second
        Sleep(1000);
        moveTetromino(currentTetromino, 0, 1);

        // Collision check (basic)
        if (currentTetromino.y >= HEIGHT - 4) {
            placeTetromino(currentTetromino);
            currentTetromino = Tetromino(rand() % 7); // Generate a new tetromino
        }
    }
}

// Entry point
int main() {
    gameLoop();
    return 0;
}
