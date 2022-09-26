// verified
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h> // contains boolean realtons
#include "pinfo.h"
typedef char *stringg;
typedef struct passwd *main_struct;
typedef long long element_type;
typedef char *stringg;
typedef struct passwd *main_struct;
typedef long long element_type;
#define MAX_LIMITS 1000
#define okay_limit 200
void check_arguments(long long arguments, int *flag) // checks arguments passed are correct or not
{
    if (arguments > 2)
    {
        printf("Too mny arguments\n");
        *flag = 0;
        return;
    }
    else if (arguments == 2)
    {

        *flag = 14;
        return;
    }
    else
    {
        *flag = 1;
        return;
    }
}
void final_ans(int proc_id, stringg process_status, stringg process_memory, stringg process_path) // prints final answer 
{
    printf("pid : %d\n", proc_id);
    printf("Process Status : %s\n", process_status);
    printf("memory : %s {Virtual Memory}\n", process_memory);
    printf("Executable Path : %s\n", process_path); // a.out in shell
}
void pinfo(element_type argc, stringg argv[])
{
    pid_t proc_id;
    stringg process_status = (stringg)malloc(MAX_LIMITS * sizeof(char));
    stringg process_memory = (stringg)malloc(MAX_LIMITS * sizeof(char));
    stringg process_path = (stringg)malloc(MAX_LIMITS * sizeof(char));
    int flag = 1;
    check_arguments(argc, &flag);
    if (flag == 0)
    {
        return;
    }
    else if (flag == 14)
    {
        proc_id = atoi(argv[1]);
    }
    else if (flag == 1)
    {
        proc_id = getpid();
        // pid of the current running process
    }
    stringg status = (stringg)malloc(MAX_LIMITS * sizeof(char));
    stringg exe = (stringg)malloc(MAX_LIMITS * sizeof(char));
    stringg stat = (stringg)malloc(MAX_LIMITS * sizeof(char));
    sprintf(stat, "/proc/%d", proc_id);               // creating file names for stat proc and exe files
    sprintf(status, "/proc/%d", proc_id);
    sprintf(exe, "/proc/%d", proc_id);
    strcat(stat, "/stat");
    strcat(status, "/status");
    strcat(exe, "/exe");
    FILE *main_file = fopen(stat, "r");

    if (main_file != 0)
    {                                              // scanning content from stat file
        char specs[40][40];
        // trying variety of scans ;p
        fscanf(main_file ,"%s",specs[0]);
        fscanf(main_file, "%s", specs[1]);
        fscanf(main_file, "%s", specs[2]);
        fscanf(main_file, "%s", specs[3]);
        fscanf(main_file, "%s", specs[4]);
        fscanf(main_file, "%s", specs[5]);
        fscanf(main_file, "%s", specs[6]);
        fscanf(main_file, "%s", specs[7]);
        fscanf(main_file, "%s", specs[8]);
        fscanf(main_file, "%s", specs[9]);
        fscanf(main_file, "%s", specs[10]);

        // printf("%s %S %s",spces[0],specs[1],specs[2]);
        // same as conti
        fscanf(main_file, "%s %s %s %s %s",specs[11], specs[12], specs[13], specs[14], specs[15]);
        fscanf(main_file, "%s %s %s %s %s", specs[16], specs[17], specs[18], specs[19], specs[20]);
        fscanf(main_file,"%s %s", specs[21], specs[22]);
        // scanned the content of stat file where 4th element stores group pid and 7 stores pid eq if fg
        element_type grp_p = atoi(specs[4]);
        element_type group_t = atoi(specs[7]);
        strcpy(process_status, specs[2]);

        element_type fore_ground = 0;
        if (grp_p == group_t)
        {
            fore_ground = 1;
        }
        if (fore_ground)
        {
            process_status[1] = '+';
            process_status[2] = 0;
        }
        else
        {
            process_status[1] = 0;
        }
        strcpy(process_memory, specs[22]);
        fclose(main_file);
    }
    else
    {
        printf("error while opening file\n");
        return;
    }

    // exe file
    stringg buffer = (stringg)malloc(MAX_LIMITS * sizeof(char));
    stringg tempo = (stringg)malloc(MAX_LIMITS * sizeof(char));
    element_type check = readlink(exe, buffer, MAX_LIMITS);
    strcpy(tempo, buffer);
    if (check == -1 || check == 0)
    {
        perror(exe);
        return;
    }
    else
    {

        int path_len = strlen(tempo);
        int home_len = strlen(home_directory);
        process_path[0] = '~';
        element_type flag = 1;
        home_len--;
        // exteracting path of pwd
        if (strlen(tempo) >= strlen(home_directory))
        {
            if (flag)
            {
                for (int i = home_len + 1; i < path_len; i++)
                {
                    process_path[i - home_len] = tempo[i];
                }
                process_path[path_len - home_len] = '\0';
                flag = 1;
            }
        }
        else
        {
            flag = 0;
        }

        if (flag == 0)
        {
            strcpy(process_path, tempo);
        }
    }

    final_ans(proc_id, process_status, process_memory, process_path);

    free(stat);
    free(status);
    free(exe);
    free(buffer);
    free(tempo);
    free(process_memory);
    free(process_path);
    free(process_status);
}