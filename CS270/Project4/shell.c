#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shell.h"
#define BUF 2048

// initialize functions
void runShell(char* filename); // run loop for shell
char *grabline(); // grab a line
int cdFunc(char **args); // if call cd
int exitFunc(char **args); // if call exit
int setenvFunc(char **args); // if setenv called
int commandSelect(struct command *Given);
int call_redirected(char *program, char *args[], char *outfile);  // from lab 2
int commandList();
char* readFile(FILE * filename, int* guardian);

int main(int argc, char **argv)
{
    runShell(argv[1]); // calls the shell loop

    return EXIT_SUCCESS;
}

void runShell(char* filename)
{
    char *nextLine;
    int exitSent1 = 1;
    int exitSent2 = 1;
    struct command *input;
    FILE *file;

    if (filename != NULL)
        file = fopen(filename, "r");
    do{
        if (filename == NULL) // if there was no input file, wait for stdin
        {
            printf("SimpleShell> ");
            nextLine = grabline();
        }
        else // open from input file
            nextLine = readFile(file, &exitSent2);
        input = parse_command(nextLine);
        exitSent1 = commandSelect(input);
        free_command(input);
    }while (exitSent1 == 1 && exitSent2 == 1); // loop until sentinal change
    if (filename != NULL)
        fclose(file);
}

char *grabline()
{
    int buffSize = BUF;
    int placeHolder = 0;
    char *buff = malloc(sizeof(char) * BUF);
    int a;

    if (!buff)
    {
        fprintf(stderr, "Allocating caused error, returning...\n");
        exit(EXIT_FAILURE);
    }
    while (1) // loop until eof
    {
        a = getchar();
        if (a == EOF || a == '\n')
        {
            buff[placeHolder] = '\0';
            return buff;
        }
        else
            buff[placeHolder] = a;
        placeHolder++;
        if (placeHolder >= BUF)
        {
            buffSize += BUF;
            buff = realloc(buff, buffSize);
            if (!buff) // prints error message alloc error
            {
                fprintf(stderr, "Allocating caused error, returning...\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

int cdFunc(char **args)
{
    if (args[1] == NULL)
    {
        if (chdir(getenv("HOME")) != 0)
            perror("Error in change directory function.");
    }
    else
    {
        if (chdir(args[1]) != 0)
            perror("Error.");
    }
    return 1;
}

int exitFunc(char **args)
{
    return 0;
}

int setenvFunc(char **args)
{
    if (args[1] == NULL) // if setenv has no args
        perror("Error: setenv needs arguments.");
    else if (args[2] == NULL)
    {
        if (unsetenv(args[1]) != 0)
        perror("Error with unsetenv.");        
    }

    else
    {
        if (setenv(args[1], args[2], 1) != 0)
            perror("Error with setenv.");
    }
    return 1;
    
}

int commandSelect(struct command *Given)
{
    char *funcNames[] = { "cd", "exit", "setenv"}; // array with function names to go through
    int (*funcList[])(char **) = { &cdFunc, &exitFunc, &setenvFunc}; // pointers to function

    if (Given->args[0] == NULL) // no input
        return 1;
    for (int i = 0; i < sizeof(funcList) / sizeof(char *); i++)
    {
        if (strcmp(Given->args[0], funcNames[i]) == 0)
            return (*funcList[i])(Given->args); // calls function if it is one of the three
    }
    return (call_redirected(Given->in_redir, Given->args, Given->out_redir));
}

int call_redirected(char *program, char *args[], char *outfile) // from lab 2
{
    pid_t pid = fork(); // call fork

    if (pid < 0) //check if failed, child or parent
    {
        perror("fork failed");
        return 0;
    }
    else if (pid == 0)
    {
        if (outfile != '\0')
        {
            // child process
            int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666); // open and get file descriptor

            if (fd < 0) // check if failed else run dup2
            {
                perror("child open failed");
                exit(-1);
            }
            else
            {
                int dup = dup2(fd, 1);

                if (dup < 0) // check if dup2 failed
                {
                    perror("child dup2 failed");
                    exit(-1);
                }
            }
        }
        if (program != '\0')
        {
            int fd = open(program, O_RDONLY);
            if (fd < 0)
            {
                perror("Open failed");
                exit(EXIT_FAILURE);
            }
            int dup = dup2(fd, 0);
            if (dup < 0)
            {
                perror("dup2 failed for infile");
                exit(EXIT_FAILURE);
            }
        }
        execvp(args[0], args);
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        // parent process
        int exitstat = 0;
        pid_t wp = wait(&exitstat); // set exit staus int and pid for wait

        if (wp < 0) // check if failed
        {
            perror("parent wait failed");
            return 0;
        }
        else
        {
            if(WIFEXITED(exitstat) && WEXITSTATUS(exitstat) == 0)
                return 1;
            else
                return 0;
        }
    }
}

char* readFile(FILE * filename, int* guardian)
{
    int buff = BUF;
    int start = 0;
    char *buffer = malloc(sizeof(char) * buff);
    int a;

    if (filename == NULL)
    {
        perror("Error opening");
        exit(EXIT_FAILURE);
    }
    if (!buffer)
    {
        fprintf(stderr, "Error allocating.\n");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        a = fgetc(filename);
        if (a == EOF || a == '\n')
        {
            buffer[start] = '\0';
            if (a == EOF)
                *guardian = 0;
            return buffer;
        }
        else
            buffer[start] = a;
        start += 1;
        if (start >= buff)
        {
            buff += BUF;
            buffer = realloc(buffer, buff);
            if (!buff)
            {
                fprintf(stderr, "Error allocating.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}