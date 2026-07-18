// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>
// #include <sys/wait.h>
// #include <stdlib.h>

// int main(){

//     int fd[2];
//     pid_t pid;
//     char buffer[100];

//     pipe(fd);

//     pid = fork();

//     if(pid < 0){
//         perror("fork is break");
//         exit(1);
//     }
//     else if(pid > 0){
//         close(fd[0]);

//         char massege[100] = "Hello Child!";

//         write(fd[1], massege, strlen(massege) + 1);
//         wait(NULL);
//     }
//     else if(pid == 0){
//         close(fd[1]);
//         read(fd[0], buffer, sizeof(buffer));

//         printf("%s", buffer);

//     }


//     return 0;
// }

// #include <stdio.h>
// #include <string.h>
// #include <sys/wait.h>
// #include <stdlib.h>
// #include <unistd.h>

// int main(){

//     int pipe1[2];
//     int pipe2[2];
//     char buffer[100];
//     char buffer1[100];

//     pipe(pipe1);
//     pipe(pipe2);

//     pid_t pid = fork();

//     if(pid < 0){
//         perror("fork error");
//         exit(1);
//     }
//     else if(pid >0){
//         close(pipe1[0]);
//         close(pipe2[1]);

//         char massege[] = "Hello";

//         write(pipe1[1], massege, strlen(massege) + 1);
//         read(pipe2[0], buffer, sizeof(buffer));

//         printf("from child: %s \n", buffer);
//         wait(NULL);

//         close(pipe1[1]);
//         close(pipe2[0]);

//     }
//     else if(pid == 0){
//         close (pipe1[1]);
//         close(pipe2[0]);

//         char massege2[] = "Thanks";

//         read(pipe1[0], buffer1, sizeof(buffer1));
//         write(pipe2[1], massege2, strlen(massege2) + 1);

//         printf("from parent: %s \n", buffer1);

//         close(pipe1[0]);
//         close(pipe2[1]);
//     }


//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/wait.h>
// #include <string.h>
// #include <unistd.h>

// struct Arrstats{
//     int max;
//     int min;
//     int average;
//     int sum;
// };

// int main(){


//         int pipe1[2];
//         int pipe2[2];

//         pipe(pipe1);
//         pipe(pipe2);

//         pid_t pid = fork();

         

//         if(pid < 0){
//             perror("fork error");
//             exit(1);
//         }
//         else if(pid > 0){
//             close(pipe1[0]);
//             close(pipe2[1]);

//             struct Arrstats stats;

//             int arr[4] = {5, 7, 8, 1};
//             write(pipe1[1], arr, sizeof(arr));
//             read(pipe2[0], &stats, sizeof(stats));

//             printf("sum is: %d \n", stats.sum);
//             printf("max is: %d \n", stats.max);
//             printf("min is: %d \n", stats.min);
//             printf("average is: %d \n", stats.average);

//             wait(NULL);
//             close(pipe1[1]);
//             close(pipe2[0]);

//         }
//         else {
//             close(pipe1[1]);
//             close(pipe2[0]);

//             struct Arrstats stats;

//             int arr[4];

//             read(pipe1[0], arr, sizeof(arr));


//             stats.sum = 0;
//             stats.max = arr[0];
//             stats.min = arr[0];
//             stats.average = 1;

//             for(int i = 0; i < 4; i++){
//                 stats.sum += arr[i];
//                 if(arr[i] > stats.max){
//                     stats.max = arr[i];
//                 }
//                 if(arr[i] < stats.min){
//                     stats.min = arr[i];
//                 }
//             }
//             stats.average = stats.sum / 4;

//             write(pipe2[1], &stats, sizeof(stats));

//             close (pipe1[0]);
//             close (pipe2[1]);
//         }



//     return 0;
// }
