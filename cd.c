//verified
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h> // contains boolean realtons    // struct that conatins user id etc as its members
#include <ctype.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
typedef long long int element_type;
typedef char *stringg;
#define MAX_LIMITS 1000
#include "cd.h"
void cd(element_type no_arguments, stringg commmand_list[])
{
    int flag = 0;
    stringg dir = (stringg)malloc(MAX_LIMITS * sizeof(char));
    stringg path = (stringg)malloc(MAX_LIMITS * sizeof(char));
    stringg pwd = (stringg)malloc(MAX_LIMITS * sizeof(char));
    stringg tempa = (stringg)malloc(MAX_LIMITS * sizeof(char));
    getcwd(tempa, MAX_LIMITS);

    if (no_arguments > 2)
    {
        printf("Too many arguments\n");
        return;
    }
    switch (no_arguments)
    {
    case 1:
        strcpy(dir, "~");
        break;
    default:
        strcpy(dir, commmand_list[1]);
        break;
    }
    strcpy(pwd, tempa);            // we have pwd as cwd rn
    char determine = dir[0];
    switch (determine)
    {
    case '-': // shows you your previous directory
        if (strlen(dir) > 1)
        {
            printf("Invalid argument\n");
            return;
        }
        strcpy(path, previous_dir);              // just copy path of previous direc to path
        printf("%s\n", previous_dir);
        break;
    case '~':                           // tilda you go to home directory   
    {
        strcpy(path, home_directory);
        break;
    }
    case '.':

        if (strcmp(".", dir) == 0)              // if it's liek cd . you stay at the same 
        {
            flag = 0;
            strcpy(path, pwd);
        } 
        else if (strcmp("..", dir) == 0)         // cd .. you move to previous
        {
            flag = 0;
            sprintf(path, "%s/..", pwd);
        }
        else                             // other commands considered invalid
        {
            flag = 1;
            return;
        }
        if (flag == 1)
        {
            printf("The command is invalid\n");
        }
        break;
    default:
        strcpy(path, dir);
    }
    long long check=chdir(path);         // you check if path exists ekse give error 
    if (check < 0)
    {
        perror("error");
        return;
    }
    strcpy(previous_dir, pwd);
    free(dir);
    free(path);
    free(pwd);
}
