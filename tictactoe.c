#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>

struct threadInfo {
        char** board;
        int length;
        bool gameOver;
        int currentPlayer;
};

void printArray(char**, int);
bool gameOver(char**, int);
void* player1(void*);
void* player2(void*);

int main(int argc, char** argv){
        struct threadInfo info;
        int r = 3;
        int c = 3;
        info.board = (char**) malloc(r * sizeof(char));
        for(int i = 0; i < r; i++){
                info.board[i] = (char*) malloc(c * sizeof(char));
        }
        info.length = 3;
        info.currentPlayer = 1;
        info.gameOver = false;

        for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                        info.board[i][j] = '-';
                }
        }
        printf("Blank game board:\n");

        for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                        printf(" %c ", info.board[i][j]);
                }
                printf("\n");
        }
        srand(time(NULL));

        pthread_t id1;
        pthread_t id2;

        int err = pthread_create(&id1, NULL, player1, &info);

        if(err!= 0){
                printf("Error creating pthread\n");
                return 1;
        }
        if(pthread_detach(id1) != 0){
                printf("Error detaching player1\n");
                return 1;
        }

        err = pthread_create(&id2, NULL, player2, &info);

        if(err != 0){
                printf("Error creating pthread\n");
                return 1;
        }

        if(pthread_detach(id2) != 0){
                printf("Error detaching player2");
                return 1;
        }

        while(1){
                if(gameOver(info.board, info.length) == true){
                        printf("Finished game board.\n");
                        printArray(info.board, info.length);
                        return 0;
                }
        }
}
        void* player1(void* arg){
                struct threadInfo* info = (struct threadInfo*) arg;
                int row = rand() % 3;
                int column = rand() % 3;

                while(!info -> gameOver){
                        while(info -> currentPlayer != 1){
                                sleep(7);
                        }
                        while(info -> board[row][column] != '-'){
                                row = rand() % 3;
                                column = rand() % 3;
                        }
                        if(info -> board[row][column] = '-'){
                                info -> board[row][column] = 'x';
                        }
                        info -> currentPlayer = 2;
                        printf("Player 1\n");
                        printArray(info -> board, info -> length);
                }
        }

        void* player2(void* arg){
                struct threadInfo* info = (struct threadInfo*) arg;
                int row = rand() % 3;
                int column = rand() % 3;
                while(!info -> gameOver){
                        while(info -> currentPlayer != 2){
                                sleep(7);
                        }
                        while(info -> board[row][column] != '-'){
                                row = rand() % 3;
                                column = rand() % 3;
                        }
                        if(info -> board[row][column] = '-'){
                                info -> board[row][column] = 'o';
                        }
                        info -> currentPlayer = 1;
                        printf("Player 2\n");
                        printArray(info -> board, info -> length);
                }
        }

        void printArray(char** arr, int length){
                for(int i = 0; i < 3; i++){
                        for(int j = 0; j < 3; j++){
                                printf(" %c ", arr[i][j]);
                        }
                        printf("\n");
                }
        }

        bool gameOver(char** arr, int length){
                for(int i = 0; i < length; i++){
                        for(int j = 0; j < length; j++){
                                if(arr[i][j] == '-'){
                                        return false;
                                }
                        }
                }
                return true;
        }
