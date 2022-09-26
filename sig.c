#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sig.h"
int check_v(int argc)
{
    if (argc > 3)
    {
        printf("TOO MANY ARGUMENTS \n");
        return -1;
    }
    if (argc < 3)
    {
        printf("TOO FEW ARGUMENTS \n");
        return -1;
    }
    return 0;
}
int check_pid(int pid)
{
    if (pid < 0)
    {
        perror("Invalid PID");
        return -1;
    }
    return 0;
}
void sig(int argc, int pid, int signal_index)
{
    int check_if_v = check_v(argc);
    if (check_if_v == -1)
    {
        return;
    }
    int check_valid_pid = check_pid(pid);
    if (check_valid_pid == -1)
    {
        return;
    }
    // you call kill with corresponding sig_num as in third argument you process getskilled with given command
    int sig_term= kill(pid,signal_index);
    if (sig_term==-1)
    {
        perror("SIG ERROR");
        return;
    }
}