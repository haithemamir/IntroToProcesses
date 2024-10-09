#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>  // For exit(), random(), srandom()
#include <sys/wait.h>  // For wait()
#include <time.h>  // For time()

#define MAX_ITERATIONS 30

void ChildProcess(void);  // Child process prototype
void ParentProcess(void);

int main(void) {
    srandom(time(NULL));  // Seed the random number generator with the current time
    pid_t pid1, pid2;
    int status;

    // Create the first child process
    pid1 = fork();
    if (pid1 < 0) {
        perror("Failed to fork");
        exit(1);
    } else if (pid1 == 0) {
        ChildProcess();
        exit(0);
    }

    // Create the second child process
    pid2 = fork();
    if (pid2 < 0) {
        perror("Failed to fork");
        exit(1);
    } else if (pid2 == 0) {
        ChildProcess();
        exit(0);
    }

    ParentProcess();

    // Wait for the first child process to finish
    pid_t finished_pid1 = wait(&status);
    printf("Child Pid: %d has completed\n", finished_pid1);

    // Wait for the second child process to finish
    pid_t finished_pid2 = wait(&status);
    printf("Child Pid: %d has completed\n", finished_pid2);

    printf("*** Parent process is done waiting for both children ***\n");
    return 0;
}

void ChildProcess(void) {
    int i;
    int iterations = random() % MAX_ITERATIONS;
    pid_t pid = getpid();
    pid_t parent_pid = getppid();

    for (i = 0; i <= iterations; i++) {
        printf("Child Pid: %d is going to sleep!\n", pid);
        sleep(random() % 10);  // Sleep for a random amount of time between 0 and 9 seconds
        printf("Child Pid: %d is awake! Where is my Parent: %d?\n", pid, parent_pid);
    }
}

void ParentProcess(void) {
    printf("*** Parent process is waiting for both children ***\n");
}

// int main() {
//     // Creating first child
//     int n1 = fork();

//     // Creating second child
//     int n2 = fork();

//     if (n1 > 0 && n2 > 0) {
//         printf("\nParent process:\n");
//         printf("n1 = %d, n2 = %d\n", n1, n2);
//         printf("My ID: %d, My Parent ID: %d\n\n", getpid(), getppid());
//         sleep(1);  // Small delay for readability purposes
//     } else if (n1 == 0 && n2 > 0) {
//         printf("\nFirst child process:\n");
//         printf("n1 = %d, n2 = %d\n", n1, n2);
//         printf("My ID: %d, My Parent ID: %d\n\n", getpid(), getppid());
//         sleep(1);  // Small delay for readability purposes
//     } else if (n1 > 0 && n2 == 0) {
//         printf("\nSecond child process:\n");
//         printf("n1 = %d, n2 = %d\n", n1, n2);
//         printf("My ID: %d, My Parent ID: %d\n\n", getpid(), getppid());
//         sleep(1);  // Small delay for readability purposes
//     } else {
//         printf("\nGrandchild process (third child):\n");
//         printf("n1 = %d, n2 = %d\n", n1, n2);
//         printf("My ID: %d, My Parent ID: %d\n\n", getpid(), getppid());
//         sleep(1);  // Small delay for readability purposes
//     }
    
//     return 0;
// }
