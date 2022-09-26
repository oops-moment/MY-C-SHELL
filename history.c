// verified
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h> // contains boolean realtons
#include "history.h"
#include <stdlib.h>
typedef char *stringg;
typedef struct passwd *main_struct;
typedef long long element_type;
#define MAX_LIMITS 1000
#define okay_limit 200
long long check_argu(long long arguments)     // check if vald arguments are passed
{
    if (arguments >= 2)
    {
        printf("More arguments than desired\n");
        return 0;
    }
}
void history(int argc, stringg argv[])          // history call
{
    int count;

    int flagu = check_argu(argc);
    if (flagu == 0)
    {
        return;
    }
    else if (argc == 1)
    {
        count = 10;
    }
    // int haha = min(10, log_count);
    int haha = 0;
    if (10 > log_count)
    {
        haha = log_count;
    }
    else
    {
        haha = 10;
    }
    for (int i = haha - 1; i >= 0; i--)                   // prints recents 10 onto screen
    {
        printf("%d %s\n",(haha-i), logs[i]);
    }
}

void write_history(stringg command)                  // updates history when new command is entered diff from prew
                                                    // recent one comes at top
{
    element_type flag = 0;
    long long len = strlen(command) - 1;
    if (command[len] == '\n')
    {
        command[len] = '\0';
    }
    if (strcmp(logs[0], command) == 0)
    {
        flag = 1;
    }
    if (flag == 0)
    {
        for (int i = log_count; i > 0; i--)
        {
            char str[okay_limit];
            strcpy(str, logs[i-1]);
            strcpy(logs[i], str);
        }

        long long len = (strlen(command) - 1);
        if (command[len] == '\n')
        {
            command[len] = '\0';
        }
        // printf("%s is the value of command\n",command);
        strcpy(logs[0], command);
        if (log_count < 20)
        {
            log_count++;
        }
    }
}

void read_history()                               // reads the histpry of past execution
{
    FILE *lf;
    lf = fopen("history.txt", "r");

    log_count = 0;

    char command[okay_limit];
    while (fgets(command, okay_limit, lf))
    {
        long long len = (strlen(command) - 1);
        if (command[len] == '\n')
        {
            command[len] = '\0';
        }
        strcpy(logs[log_count++], command);
    }
}
void print_history()                            // updates history.txt with new history
{
    FILE *lf;
    lf = fopen("history.txt", "w");

    for (int i = 0; i < log_count; i++)
    {
        chdir(home_directory);
        fprintf(lf, "%s\n", logs[i]);
    }
    fclose(lf);
}