#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

struct Temperature
{
    float celsius;
};

struct ConvertedTemperature
{
    float fahrenheit;
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

        struct Temperature temp;
        struct ConvertedTemperature conv;

        temp.celsius = 25.00;

        write(pipe1[1], &temp, sizeof(temp));

        read(pipe2[0], &conv, sizeof(conv));

        printf("farenheit = %f \n", conv.fahrenheit);

        wait(NULL);

        close(pipe1[1]);
        close(pipe2[0]);

    }
    else if(pid == 0){
        close(pipe1[1]);
        close(pipe2[0]);

        struct Temperature temp;
        struct ConvertedTemperature conv;

        read(pipe1[0], &temp, sizeof(temp));

        printf("celsius = %f \n",temp.celsius );

        conv.fahrenheit = temp.celsius * 9.0 / 5.0 + 32.0;

        write(pipe2[1], &conv, sizeof(conv));

        close(pipe1[0]);
        close(pipe2[1]);

    }


    return 0;
}