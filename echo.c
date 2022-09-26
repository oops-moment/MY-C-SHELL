// verified
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h> // contains boolean realtons
#include <pwd.h>     // struct that conatins user id etc as its members
#include <ctype.h>
#include "echo.h"
typedef long long element_type;
typedef char *stringg;
#define MAX_LIMITS 1000
element_type check_valid(element_type argum) // check if valid arguments are passed
{
    if (argum < 0)
    {
        printf("Arguments are invalid\n");
        return 0;
    }
}
void echo(element_type no_arguments, stringg command_list[])
{
    element_type flag = 0;

    flag = check_valid(no_arguments);
    if (flag == 0)                       // invalid arguments
    {
        return;
    }
    for (element_type i = 1; i < no_arguments; i++)       // prints the command
    {
        printf("%s ", command_list[i]);
    }
    printf("\n");
}