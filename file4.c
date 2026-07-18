#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdlib.h>

struct TextStats
{
    int letters;
    int digits;
    int spaces;
    int lines;
};

int main(){

    int pipe1[2];
    int pipe2[2];

    pipe(pipe1);
    pipe(pipe2);

    pid_t pid = fork();

    if(pid < 0){
        perror("fork error");
        exit(1);
    }
    else if(pid > 0){

        close(pipe1[0]);
        close(pipe2[1]);

        struct TextStats stats;

        char text[100] = "Hello World123";

        write(pipe1[1], text, strlen(text) + 1);

        read(pipe2[0], &stats, sizeof(stats));

        printf("letters = %d \n", stats.letters);
        printf("digits = %d \n", stats.digits );
        printf("spaces = %d \n", stats.spaces);
        printf("lines = %d \n", stats.lines);
        
        wait(NULL);

        close(pipe1[1]);
        close(pipe2[0]);

    }
    else if(pid == 0){

        close(pipe1[1]);
        close(pipe2[0]);

        struct TextStats stats;

        char text[100];

        read(pipe1[0], text, sizeof(text));

        stats.digits = 0;
        stats.letters = 0;
        stats.spaces = 0;
        stats.lines = 1;

        for(int i = 0; text[i] != '\0'; i++){

            if(isalpha(text[i])){
                stats.letters++;
            }
            if(isdigit(text[i])){
                stats.digits++;
            }
            if(text[i] == ' '){
                stats.spaces++;
            }
            if(text[i] == '\n'){
                stats.lines++;
            }
        }

        write(pipe2[1], &stats, sizeof(stats));

        close(pipe1[0]);
        close(pipe2[1]);
    }

}