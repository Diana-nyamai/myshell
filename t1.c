#include "main.h"

/**
 * main - Entry point
 * Return: (0) always success
 */
 
int main()
{
        // pid_t pid;
        char *buf = NULL, *argv[64], *token;
        size_t n = 0;
        int i;
        
        signal(SIGINT, signalHandler);
        while (1)
        {
            i = 0;
            prompt();
            if (getline(&buf, &n, stdin) == -1)
            {
                // printf("\n");
                break; // handle EOF
            }
    
            buf[strlen(buf) - 1] = '\0'; //null terminating the input string
            
            for (token = strtok(buf, " "); token != NULL; token = strtok(NULL, " "))
                argv[i++] = token;

            argv[i] = NULL; //setting the last element to null
            
            fork_process(argv, i);
                
        }
    free(buf);
    return (0);
}

void signalHandler(int sigint)
{
    write(STDOUT_FILENO, "\n", 1);
    exit(EXIT_SUCCESS);
}

void prompt()
{
        if (isatty(STDOUT_FILENO))
        {
            write(STDOUT_FILENO, "#cisfun$ ", 9);
            fflush(stdout);
        }
}

void fork_process(char **argv, int i)
{
    pid_t pid;
    int ex;
    pid = fork(); //create a child process
            if (pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
                
            if (pid == 0)
            {
                    if (i != 1) // not more than one argument
                    {
                        perror("./shell ");
                        exit(EXIT_FAILURE);
                    }
                        
                    ex = execve(argv[0], argv, NULL);
                
                    if (ex == -1)
                        perror("./shell ");
            }
            else
            {
                wait(NULL); //parent waits for the child to finish
            }
}