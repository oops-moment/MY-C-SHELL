#include "fg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
int abso(int var_fg)
{
    if(var_fg>0)
    {
        return var_fg;
    }
    else
    {
        return -var_fg;
    }
}
void calculate_fg(int argc, char *argv[])
{
    int status;
    if (argc > 2)
    {
        printf("TOO MANY ARGUMENTS\n");
        return;
    }
    else if (argc < 2)
    {
        printf("LESS ARGUMENTS");
        return;
    }
    else
    {
        // converts argument 2 to integer and calculate the pid of job corresponding to that number
        int job_number = (atoi)(argv[1]);
        int pid_job = background_pid[job_number - 1];
        //     The setpgid() function is used to either join an existing process group or create a new process group within the session of the calling proces
        setpgid(pid_job, getpgid(0));
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        // if the process has a controlling terminal, tcsetpgrp() shall set the foreground process group ID associated with the terminal to pgid_id.
        tcsetpgrp(0, pid_job);
        // here we resume the process
        int check = kill(pid_job, SIGCONT);
        if (check < 0)
        {
            perror("error");
        }
        else
        {
            // printf("han chal rha \n");
        }
        // in foreground process we wait till we are done with given pid process
        // WUNTRACED :Status for traced children which have stopped is provided
        waitpid(pid_job, &status, WUNTRACED);
        tcsetpgrp(0, getpgid(0));
        // SIGDFL: informs the kernel that there is no user signal handler for the given signal, and that the kernel should take default action for it
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        //. WIFSTOPPED evaluates to true (1) when the process for which the wait() call was made is stopped, or to false (0) otherwise.
        if (WIFSTOPPED(status))
        {
            var_fg = 0;
            return;
        }
        if (WIFEXITED(status) != 0)
        {
            var_fg = pid_job;
        }
        else
        {
            var_fg = -pid_job;
        }
        if (var_fg == 0)
        {
            return;
        }
        var_fg=abso(var_fg);
        int check_bg = 0;

        for (int i = 1; i < 200; i++)
        {
            if (background_pid[i] == var_fg)
            {
                background_pid[i] = 0;
                check_bg = 1;
            }
            if (check_bg == 1)
            {
                free(bgCommand[i]);
                break;
            }
        }
    }
}
