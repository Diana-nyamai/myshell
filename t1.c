#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void signalHandler(int sigint)
{
    printf("\n");
    exit(EXIT_SUCCESS);
}

int main()
{
    pid_t pid;
    char *buf = NULL, *argv[64], *token;
    size_t n = 0;
    int ex, i;

    signal(SIGINT, signalHandler);

    while (1)
    {
        i = 0;
        printf("#cisfun$ ");
        ssize_t read = getline(&buf, &n, stdin);
        if (read == -1)
        {
            // Handle EOF
            printf("\n");
            break;
        }
        if (strcmp(buf, "\n") == 0)
        {
            // Empty input line, continue to the next iteration
            continue;
        }

        buf[strlen(buf) - 1] = '\0'; // Null terminate the input string

        for (token = strtok(buf, " "); token != NULL; token = strtok(NULL, " "))
            argv[i++] = token;

        argv[i] = NULL; // Set the last element to null

        pid = fork(); // Create a child process
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            if (i > 1)
            {
                perror("./shell");
                exit(EXIT_FAILURE);
            }
            ex = execve(argv[0], argv, NULL);
            if (ex == -1)
                perror("./shell");
        }
        else
            wait(NULL); // Parent waits for the child to finish
    }

    free(buf);
    return (0);
}
