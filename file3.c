
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

struct Arrstats{
    int max;
    int min;
    int average;
    int sum;
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

            struct Arrstats stats;

            int arr[4] = {5, 7, 8, 1};
            write(pipe1[1], arr, sizeof(arr));
            read(pipe2[0], &stats, sizeof(stats));

            printf("sum is: %d \n", stats.sum);
            printf("max is: %d \n", stats.max);
            printf("min is: %d \n", stats.min);
            printf("average is: %d \n", stats.average);

            wait(NULL);
            close(pipe1[1]);
            close(pipe2[0]);

        }
        else {
            close(pipe1[1]);
            close(pipe2[0]);

            struct Arrstats stats;

            int arr[4];

            read(pipe1[0], arr, sizeof(arr));


            stats.sum = 0;
            stats.max = arr[0];
            stats.min = arr[0];
            stats.average = 1;

            for(int i = 0; i < 4; i++){
                stats.sum += arr[i];
                if(arr[i] > stats.max){
                    stats.max = arr[i];
                }
                if(arr[i] < stats.min){
                    stats.min = arr[i];
                }
            }
            stats.average = stats.sum / 4;

            write(pipe2[1], &stats, sizeof(stats));

            close (pipe1[0]);
            close (pipe2[1]);
        }



    return 0;
}