// verified
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h> // contains boolean realtons
#include <pwd.h>
#include "display.h" // struct that conatins user id etc as its members
typedef char *stringg;
typedef struct passwd *main_struct;
typedef long long element_type;
#define MAX_LIMITS 1000
#define okay_limit 200
void print_prompt(element_type flag, stringg username, stringg system_name, stringg path, stringg current_path)
{
    if (fgo == 1) // if the process is background then we print the time i took
    {
        printf("\033[0;36m");
        printf("<%s@%s:%s %s> ", username, system_name, current_path, fgu);
        printf("\033[0;m");
        fgo = 0;
    }
    else
    {
        if (flag)
        {
            // printf('\033[32m');
            printf("\033[0;36m");
            printf("<%s@%s:%s> ", username, system_name, current_path);
            printf("\033[0;m");
        }
        else
        {
            printf("\033[0;36m");
            printf("<%s@%s:%s> ", username, system_name, path);
            printf("\033[0;m");
        }
    }
}
void background_status()
{
    int status_job;
    for (element_type i = 0; i < okay_limit; i++)
    {
        if (background_pid[i] != 0) // if some background pid exists
        {
          
            element_type check = waitpid(background_pid[i], &status_job, WNOHANG);
           if(check>0)
            {
                long long fg = WIFEXITED(status_job);
                // WIFEXITED TELLS IF THE PROCESS EXITED NORMALLY / ABNORMALLY
                if (fg)
                {
                    fprintf(stderr, "%s with PID %d exited %s\n", bgCommand[i], background_pid[i], "normally");
                }
                else
                {
                    fprintf(stderr, "%s with PID %d exited %s\n", bgCommand[i], background_pid[i], "abnormally");
                }
                // SInce the process has been terminated so remove that process from array and set it's pid as 0
                background_pid[i] = 0;
                free(bgCommand[i]); // this process has exited so you leave
            }
        }
    }
}
stringg present_directory(element_type *flag, element_type path_length, element_type home_directory_length, stringg path)
{  
    // SO we take the path of present directory that would be part of path excluding path of home dire
    stringg pre = (stringg)malloc(MAX_LIMITS * sizeof(char));
    if (path_length >= home_directory_length) // here you take your cureent working directory
    {
        if (*flag)
        {
            element_type min = home_directory_length;
            element_type full = path_length;
            min--;
            for (int i = min; i < full; i++)
            {
                pre[i - min] = path[i];
            }
        }
    }
    else
    {
        *flag = 0;
    }
    return pre;
}
void display(int status)
{    
    // this functions extract the user and the host name to be printed onto the prompt
    if(status==-1)
    {
        return ;
    }
    char current_path[1024] = "~"; // agar kuch bhi nhi h tih "~"
    stringg system_name = (stringg)malloc(MAX_LIMITS * sizeof(char));
    stringg path = (stringg)malloc(MAX_LIMITS * sizeof(char));
    char present_dir[MAX_LIMITS];
    getcwd(present_dir, MAX_LIMITS);
    stringg username = (stringg)malloc(MAX_LIMITS * sizeof(char));
    unsigned int user_id;
    user_id = geteuid(); // for username
    main_struct attribute = getpwuid(user_id);
    main_struct system_uid = attribute;
    username = system_uid->pw_name;
    gethostname(system_name, okay_limit); // for system name here asus tuf
    strcpy(path, present_dir);
    element_type flag = 1;
    element_type flag2 = 0;
    if (flag2)
    {
        present_directory(&flag, strlen(path), strlen(home_directory), path);
    }
    if (strlen(path) >= strlen(home_directory))
    {

        for (int i = strlen(home_directory); i < strlen(path); i++)
        {
            current_path[i - strlen(home_directory) + 1] = path[i];
        }
    }
    else
    {
        flag = 0;
    }
    print_prompt(flag, username, system_name, path, current_path); // for screen format
    background_status();                           // checks status of background process
}
