#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "bg.h"

void calculate_bg(int argc, char *argv[])     // function call for bg passing number of arguments
{
  if (argc > 2)
  {
    printf("TOO MANY ARGUMENTS\n");
    return;
  }
  else if (argc < 2)
  {
    printf("TOO FEW ARGUMENTS \n");
    return;
  }
  else
  {
    // basically we have to bring that process to running like then terminate it normally
    int job_num = atoi(argv[1]);                  // converson of string to integer
    int pid_job = background_pid[job_num - 1];     // Extracting jobs's pid from background_pid array
    int check = kill(pid_job, SIGCONT);            // Runs the given id process
  
    if (check < 0)                 // if job couldn't be continued it throws error
    {
      perror("ERROR\n");
      return;
    }
  }
}
