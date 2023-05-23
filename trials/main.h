#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>

void signalHandler(int sigint);
void prompt();
void handle_path(char *path, char **argv);
void fork_process();


/*  CUSTOM FUNCTIONS */

int _strlen(char *str);
int _strncmp(const char* str1, const char* str2, size_t n);
char *get_env(char *name);
char *_strncpy(char *dest, char *src, int n);

#endif