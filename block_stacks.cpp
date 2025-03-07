/*Block-Stacks*/
//A Tetris Based game made in pure C++
//Made by vaishcodescape and sam5506

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <unistd.h>
    #include <termios.h>
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
        usleep(ms * 1000);
    }
#endif

using namespace std;

const int WIDTH = 10, HEIGHT = 20;
int board[HEIGHT][WIDTH] = {0};
const int TETROMINOS[7][4][4] = { 
    {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}},
    {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},
    {{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},
    {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    {{1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    {{0,0,1,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}
};

struct Tetromino {
    int shape[4][4];
    int x, y;
    
    Tetromino(int type) {
        memcpy(shape, TETROMINOS[type], sizeof(shape));
        x = WIDTH / 2 - 2;
        y = 0;
    }
    
    void rotate() {
        int temp[4][4] = {0};
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                temp[j][3 - i] = shape[i][j];
        memcpy(shape, temp, sizeof(shape));
    }
};

bool isValidMove(Tetromino &t, int dx, int dy) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (t.shape[i][j]) {
                int newX = t.x + j + dx;
                int newY = t.y + i + dy;
                if (newX < 0 || newX >= WIDTH || newY >= HEIGHT || board[newY][newX])
                    return false;
            }
    return true;
}

void placeTetromino(Tetromino &t) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (t.shape[i][j])
                board[t.y + i][t.x + j] = 1;
}

void clearRows() {
    for (int i = HEIGHT - 1; i >= 0; i--) {
        bool full = true;
        for (int j = 0; j < WIDTH; j++)
            if (!board[i][j]) full = false;
        if (full) {
            for (int k = i; k > 0; k--)
                memcpy(board[k], board[k - 1], sizeof(board[k]));
            memset(board[0], 0, sizeof(board[0]));
            i++;
        }
    }
}

void draw(Tetromino &t) {
    system("clear");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            bool isTetromino = false;
            for (int r = 0; r < 4; r++)
                for (int c = 0; c < 4; c++)
                    if (t.shape[r][c] && i == t.y + r && j == t.x + c)
                        isTetromino = true;
            cout << (isTetromino ? "# " : board[i][j] ? "* " : ". ");
        }
        cout << endl;
    }
}

void gameLoop() {
    srand(time(0));
    Tetromino current(rand() % 7);

    while (true) {
        draw(current);
        if (_kbhit()) {
            char key = _getch();
            if (key == 'a' && isValidMove(current, -1, 0)) current.x--;
            if (key == 'd' && isValidMove(current, 1, 0)) current.x++;
            if (key == 'w') {
                current.rotate();
                if (!isValidMove(current, 0, 0)) current.rotate(); 
            }
            if (key == 's' && isValidMove(current, 0, 1)) current.y++;
        }
        Sleep(200);
        if (!isValidMove(current, 0, 1)) {
            placeTetromino(current);
            clearRows();
            current = Tetromino(rand() % 7);
            if (!isValidMove(current, 0, 0)) {
                cout << "Game Over!" << endl;
                break;
            }
        } else current.y++;
    }
}

int main() {
    gameLoop();
    return 0;
}
