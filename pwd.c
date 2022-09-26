// verified
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h> // contains boolean realtons
#include "pwd.h"     // struct that conatins user id etc as its members
#include <ctype.h>
typedef long long element_type;
typedef char *stringg;
typedef char *stringg;
typedef struct passwd *main_struct;
typedef long long element_type;
#define MAX_LIMITS 1000
#define okay_limit 200
element_type check_valids(element_type argum)   //check if valid argument is passed
{
    if (argum > 1)
    {
        return 0;
    }
    return 1;
}
void pwd(element_type argc)
{
    element_type flag=1;
    flag = check_valids(argc);
    if (!flag)
    {
        printf("pwd can't have Too many arguments\n");
        return;
    }
    else
    {
        stringg cwd = (stringg)malloc(MAX_LIMITS * sizeof(char));
        getcwd(cwd, MAX_LIMITS);   // we get cwd using getcwd command
        printf("%s\n", cwd);
        free(cwd);
    }
}