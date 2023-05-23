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
            if (getline(&buf, &n, stdin) == EOF)
            {
                break; // handle EOF
            }
    
            buf[_strlen(buf) - 1] = '\0'; //null terminating the input string
            
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
        if (isatty(STDIN_FILENO))
        {
            write(STDOUT_FILENO, "#cisfun$ ", 9);
            fflush(stdout);
        }
}

void fork_process(char **argv, int i)
{
    pid_t pid;
    int ex;
    char *path = get_env("PATH");
   
    pid = fork(); //create a child process
            if (pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (pid == 0)
            {
                    if (i < 1) // not more than one argument
                    {
                        perror("./shell ");
                        exit(EXIT_FAILURE);
                    }
                        
                    ex = execve(argv[0], argv, NULL);
                
                    if (ex == -1)
                    {
                        handle_path(path, argv);
                        perror("shell ");
                        exit(EXIT_FAILURE);
                    }
                    exit(EXIT_FAILURE);
            }
            else
            {
                wait(NULL); //parent waits for the child to finish
            }
}

void handle_path(char *path, char **argv)
{
    char *dir, *command;
    size_t path_len, dir_len, command_len;
    int ex;
    
    dir = strtok(path, ":");
            while (dir != NULL)
            {

                path_len = _strlen(dir);
                dir_len = _strlen(argv[0]);
                command_len = path_len + 1 + dir_len + 1; // +1 for '/' and +1 for null terminator
                command = malloc(command_len);

                _strncpy(command, dir, path_len);
                command[path_len] = '/';
                _strncpy(command + path_len + 1, argv[0], dir_len);
                command[path_len + 1 + dir_len] = '\0';
                // Check if the command is executable in the current directory
                if (access(command, X_OK) == 0)
                {
                    ex = execve(command, argv, NULL);
                    if (ex == -1)
                        perror("shell ");
                    exit(EXIT_FAILURE);
                }

                free(command);
                dir = strtok(NULL, ":");
            }
}