#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){

    int fd[2];
    pid_t pid;
    char buffer[100];

    pipe(fd);

    pid = fork();

    if(pid < 0){
        perror("fork is break");
        exit(1);
    }
    else if(pid > 0){
        close(fd[0]);

        char massege[100] = "Hello Child!";

        write(fd[1], massege, strlen(massege) + 1);
        wait(NULL);
    }
    else if(pid == 0){
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));

        printf("%s", buffer);

    }


    return 0;
}

