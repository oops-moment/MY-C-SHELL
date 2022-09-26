#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h> // contains boolean realtons
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "jobs.h"
// struct that consists of name of command , its pid and its status
typedef struct
{
    int pid_process;
    char command[100];
    char last_name[50];
    char status[100];
} job_items;
// comaprator function that compares sort on basis of entered command
int comparator(const void *p0, const void *p1)
{
    return strcmp(((job_items *)p0)->command, ((job_items *)p1)->command);
}

void jobs(char *command)
{

    job_items *arraya = malloc(100 * sizeof *arraya);
    // allocating memory to array of structs
    int count = 0;
    char run_stop;
    for (int i = 0; i < 200; i++)
    {
        char file_name[1000];
        if (background_pid[i] == 0)
        {
            continue;
        }
        else
        {
            // opening proc stat file to know stopped/running status
            sprintf(file_name, "/proc/%d", background_pid[i]);
            strcat(file_name, "/stat");
            FILE *file_scan = fopen(file_name, "r");
            char tempo[100];
            int a;
            char str[50];
            if (file_scan)
            {
                fscanf(file_scan, "%d %s %c", &a, str, &run_stop);
                // if that's T it means the process is stopped else running
                if (run_stop == 'T')
                {
                    strcpy(tempo, "stopped");
                }
                else
                {
                    strcpy(tempo, "running");
                }
                if (command == NULL)
                {
                    // allocating value to member of struct
                    strcpy(arraya[count].command, bgCommand[i]);
                    if (final[i] != NULL)
                    {

                        strcpy(arraya[count].last_name, final[i]);
                    }
                    arraya[count].pid_process = background_pid[i];
                    strcpy(arraya[count].status, tempo);
                    count++;
                }
                else if (!strcmp(command, "-r"))
                {
                    // allocating value to member of struct
                    if (!strcmp(tempo, "running"))
                    {
                        if (final[i] != NULL)
                        {
                            strcpy(arraya[count].last_name, final[i]);
                        }
                        strcpy(arraya[count].command, bgCommand[i]);
                        arraya[count].pid_process = background_pid[i];
                        strcpy(arraya[count].status, tempo);
                        count++;
                    }
                }
                else if (!strcmp(command, "-s"))
                {
                    // allocating value to member of struct
                    if (!strcmp(tempo, "stopped"))
                    {
                        if (final[i] != NULL)
                        {
                            strcpy(arraya[count].last_name, final[i]);
                        }
                        strcpy(arraya[count].command, bgCommand[i]);
                        arraya[count].pid_process = background_pid[i];
                        strcpy(arraya[count].status, tempo);
                        count++;
                    }
                }
                fclose(file_scan);
            }
            else
            {

                continue;
            }
        }
    }
    // sorting structures based upon the comparator function, inbuilt qsort used
    qsort(arraya, count, sizeof(*arraya), comparator);
    for (int h = 0; h < count; h++)
    {
        if (arraya[h].last_name != NULL)
        {

            printf("[%d] %s %s %s [%d]\n", h + 1, arraya[h].status, arraya[h].command, arraya[h].last_name, arraya[h].pid_process);
        }
        else
        {
            printf("[%d] %s %s [%d]\n", h + 1, arraya[h].status, arraya[h].command, arraya[h].pid_process);
        }
    }
}
