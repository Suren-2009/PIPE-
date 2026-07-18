
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    int pipe1[2];
    int pipe2[2];
    char buffer[100];
    char buffer1[100];

    pipe(pipe1);
    pipe(pipe2);

    pid_t pid = fork();

    if(pid < 0){
        perror("fork error");
        exit(1);
    }
    else if(pid >0){
        close(pipe1[0]);
        close(pipe2[1]);

        char massege[] = "Hello";

        write(pipe1[1], massege, strlen(massege) + 1);
        read(pipe2[0], buffer, sizeof(buffer));

        printf("from child: %s \n", buffer);
        wait(NULL);

        close(pipe1[1]);
        close(pipe2[0]);

    }
    else if(pid == 0){
        close (pipe1[1]);
        close(pipe2[0]);

        char massege2[] = "Thanks";

        read(pipe1[0], buffer1, sizeof(buffer1));
        write(pipe2[1], massege2, strlen(massege2) + 1);

        printf("from parent: %s \n", buffer1);

        close(pipe1[0]);
        close(pipe2[1]);
    }


    return 0;
}
