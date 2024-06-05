#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

#define WIDTH 50
#define HEIGHT 20

bool gameOver;
int dinoX, dinoY, obstacleX, score;
bool isJumping = false;
int jumpHeight = 0;

void Setup() {
    gameOver = false;
    dinoX = 5;
    dinoY = HEIGHT - 1;
    obstacleX = WIDTH - 1;
    score = 0;
}

void Draw() {
    system("cls"); // Clear the console

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#");

            if (i == dinoY && j == dinoX)
                printf("R"); // Dinosaurio
            else if (i == HEIGHT - 1)
                printf("_"); // Suelo
            else if (i == HEIGHT - 1 && j == obstacleX)
                printf("+"); // Cactus
            else
                printf(" ");

            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    printf("Score: %d\n", score);
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case ' ':
            if (!isJumping) {
                isJumping = true;
                jumpHeight = 0;
            }
            break;
        }
    }
}

void Logic() {
    if (isJumping) {
        dinoY--;
        jumpHeight++;
        if (jumpHeight > 2) {
            isJumping = false;
        }
    } else if (dinoY < HEIGHT - 1) {
        dinoY++;
    }

    obstacleX--;
    if (obstacleX < 0) {
        obstacleX = WIDTH - 1;
        score += 10;
    }

    if (obstacleX == dinoX && dinoY == HEIGHT - 1) {
        gameOver = true;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(50); // Ralentiza el juego
    }
    printf("Game Over!\n");
    printf("Final Score: %d\n", score);
    return 0;
}
