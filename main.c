// verified , entered comments
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <pwd.h>    
#include "discover.h"
#include "echo.h"
#include "display.h"
#include "history.h"
#include "ls.h"
#include "execute.h"
#include "jobs.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int pidu;                                 // KEEPS TRACK OF PID OF CURRENTLY RUNNING FOREGROUND PROCESS
#define MAX_LIMIT 2000
#define okay_limit 200
pid_t shell_id;                           // PID OF SHELL
long long stooped = 0;                   
typedef long long int element_type;       
char logs[256][21];                       // FOR STORING HISTORY
char fgu[70];
int log_count;
typedef char *stringg;
long long fgo = 0;
long long cutu = 0;
int shell_stdout;
int shell_stdin;
char home_directory[MAX_LIMIT];             // FOR STORING HOME_DIRECTORY
char previous_dir[MAX_LIMIT];               // FOR STORING PREVIOUS DIRECTORY
int background_pid[okay_limit];             // FOR STORING BACKGROUND PID
char *bgCommand[okay_limit];                // FOR STORING BACKGROUND COMMANDS
char *final[100];
int background = 1;
void ctrlChandler()
{
    if (background == 1)
    {
        printf("\n");
        display(-1);                         // DISPLAY PROMPT MAKE SURE IF -1 PROMPT DON'T PRINTS AGAIN
    }
    else
    {
        background = 1;
    }
}
void ctrlZhandler()
{

    if (background == 1)
    {
        printf("\n");
        display(-1);
    }
    else
    {
        kill(pidu, SIGTSTP);                   // BASICALLY SIGTSTP SERVES TO STOP PROCESS.
        background = 1;
    }
}
void call_command(stringg command_list[], element_type total, int background)
{
      // EXECUTING SEMICOLON BASED SEPERATED PROCESSES ONE BY ONE
    for (long long i = 0; i < total; i++)
    {
        if (command_list[i] == NULL)
        {
            return;
        }

        execute(command_list[i], background); 
    }
}
int main()
{
    printf("\n\t\t\t\t\033[01;33m WELCOME TO MY SHELL !! \033[01;00m\n\n");

    element_type running = 1;
    getcwd(home_directory, MAX_LIMIT);
    getcwd(previous_dir, MAX_LIMIT);
    element_type total_commands = 0;
    read_history();                          //READS THE HISTORY FROM FILE 
    signal(SIGINT, ctrlChandler);            // IF CTRL-C THEN SIGINT IS GENERATED
    signal(SIGTSTP, ctrlZhandler);           // IF  CTRL-Z THEN SIGTSTP IS GENERATEDD

    for (long long i = 0; running > 0; i++)
    {
        display(1);             // CALLS PROMPT FUNCTION TO CALL
        cutu = 0;
        total_commands = 0;
        stringg input = (stringg)malloc(sizeof(char) * MAX_LIMIT);
        char *ctrld;
        ctrld = fgets(input, MAX_LIMIT, stdin);
        if (ctrld == NULL)       // CTRL-D EMPTIES THE BUFFER
        {
            print_history();
            exit(0);
        }
        write_history(input);    // UPDATE HISTORY WITH NEWLY ENTERED INPUT
        if (strcmp(input, "\n") == 0)
        {
            continue;
        }
        if (input == NULL)
        {
            continue;
        }
        stringg commands_list[MAX_LIMIT];
        stringg tokenize = (stringg)malloc(sizeof(char) * MAX_LIMIT);
        // SEMICOLON BASED TOKENIZATION
        tokenize = strtok(input, ";");
        do
        {
            commands_list[total_commands] = tokenize;
            tokenize = strtok(NULL, ";");
            total_commands++;
        } while (tokenize != NULL);
        commands_list[total_commands] = NULL;
        // STORE THE VALUE OF STANARD INPUT AND OUTPUT AND EXTERN THIS VARIABLE
        shell_stdin = dup(STDIN_FILENO);
        shell_stdout = dup(STDOUT_FILENO);
        call_command(commands_list, total_commands, background);
        free(input);
        free(tokenize);
        total_commands = 0;
        // YOU WRITE THE CONTENTS ONTO HISTORY.TXT
        if (stooped)
        {
            FILE *lf;
            lf = fopen("history.txt", "w");
            for (int i = 0; i < log_count; i++)
            {
                fprintf(lf, "%s\n", logs[i]);
            }
            fclose(lf);
            return 0;
        }
        // FINALLY YOU DUP2 TO STANDARD INPUT / FINAL.
        dup2(shell_stdin, STDIN_FILENO);
        dup2(shell_stdout, STDOUT_FILENO);
    }
}
