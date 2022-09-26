#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h> // contains boolean realtons
#include "execute.h"
#include "echo.h"
#include "display.h"
#include "history.h"
#include "ls.h"
#include "pwd.h"
#include "cd.h"
#include "jobs.h"
#include "pinfo.h"
#include "pwd.h"
#include "discover.h"
#include "jobs.h"
#include "fg.h"
#include "bg.h"
#include "sig.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
typedef char *stringg;
typedef struct passwd *main_struct;
typedef long long element_type;
#define MAX_LIMITS 1000
#include <time.h>
int fd;
int flag_check = 0;
int final_argc;
int checku = 0;
int var_fg = 0;
// check_valids is the function checks if valid arguments are passed
int check_validss(int argc, char stringgs[50])
{
    if (argc == 0)
    {
        return -1;
    }
    if (stringgs == NULL)
    {
        return -1;
    }
    return 0;
}
// This function handles redirection along with command calls.
void handle(char *command_list[], int argc, int check)
{

    int array_del[100];
    int count = 0;
    command_list[argc] = NULL;
    int check_v = check_validss(argc, command_list[0]);
    if (check_v == -1)
    {
        return;
    }
    for (int m = 0; m < argc; m++)
    {
        if (!strcmp(command_list[m], "<"))
        {
            flag_check = 1;
            // < file name as i+1 is assumed to be file name
            char *file_name = command_list[m + 1];
            int input_fd = open(file_name, O_RDONLY);
            fd = input_fd;
            int error_hai = 0;
            if (input_fd >= 0)
            {
                int dupp = dup2(input_fd, STDIN_FILENO); // stdin has been duped to standard input
                if (dupp < 0)
                {
                    perror("ERROR WHILE DUPLICATING STDIN \n");
                    error_hai = 1;
                }
                error_hai = 0;
            }
            else
            {
                perror("ERROR WHILE OPENING INPUT FILE\n");
                checku = -1;
                error_hai = 1;
            }
            if (error_hai == 1)
            {
                break;
            }
            else
            {
                // so we have this array_del that keeps account which index of command list has to be deleted
                // here < file_name needs to be deleted.
                array_del[count] = m;
                count++;
                array_del[count] = m + 1;
                count++;
            }
        }
        else if (strcmp(command_list[m], ">") == 0)
        {
            flag_check = 1;
            int error_hai1 = 0;
            char *file_name = command_list[m + 1];
            // creates outputfile and data is redirected .
            int output_fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            fd = output_fd;
            if (output_fd < 0)
            {
                perror("ERROR WHILE OPENING OUTPUT FILE\n");
                checku = -1;
                error_hai1 = 1;
            }
            else
            {
                // stdout be duplicated to to output_fd
                int dupp = dup2(output_fd, STDOUT_FILENO);
                if (dupp < 0)
                {
                    perror("ERROR WHILE DUPLICATING STDOUT\n");
                    error_hai1 = 1;
                }
                else
                {
                    error_hai1 = 0;
                }
            }
            if (error_hai1 == 1)
            {
                break;
            }
            else
            {
                // so we have this array_del that keeps account which index of command list has to be deleted
                // here > file_name needs to be deleted.
                array_del[count] = m;
                count++;
                array_del[count] = m + 1;
                count++;
            }
        }
        else if (strcmp(command_list[m], ">>") == 0)
        {
            flag_check = 1;
            int error_hai2 = 0;
            char *file_name = command_list[m + 1];
            int output_fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
            fd = output_fd;
            if (output_fd < 0)
            {
                perror("ERROR WHILE OPENING OUTPUT FILE\n");
                checku = -1;
                error_hai2 = 1;
            }
            else
            {
                // sicne we have to concatenate data so we dup the stdout to output fd
                int dupp = dup2(output_fd, STDOUT_FILENO);
                if (dupp < 0)
                {
                    printf("error while duplicating fd \n");
                    error_hai2 = 1;
                }
                else
                {
                    error_hai2 = 0;
                }
            }
            if (error_hai2 == 1)
            {
                break;
            }
            else
            {
                // so we have this array_del that keeps account which index of command list has to be deleted
                // here >> file_name needs to be deleted.
                array_del[count] = m;
                count++;
                array_del[count] = m + 1;
                count++;
            }
        }
    }

    if (count == 0)
    {
        // count =0 tells there was no redirection
        final_argc = argc;
        for (long long i = final_argc; i <= argc; i++)
        {
            command_list[final_argc] = NULL;
        }
    }
    else
    {
        // here we make a new command list removing the redirection
        char *final_command_redirecton[100];
        for (long long g = 0; g < 100; g++)
        {
            final_command_redirecton[g] = (char *)malloc(100 * sizeof(char));
        }
        // allocation of space has been done note count is total number of commands to be deleted
        int counter = 0;
        int counter2 = 0;
        for (int h = 0; h < argc; h++)
        {
            if (h == array_del[counter])

            {
                if (counter < count)
                    counter++;
            }
            else
            {
                // a new command list named as final_command _direction has counter 2 as it id
                strcpy(final_command_redirecton[counter2], command_list[h]);
                counter2++;
            }
        }
        final_command_redirecton[counter2] = NULL;

        final_argc = counter2;
        // we make our command list equal to final command list
        for (long long z1 = 0; z1 < counter2; z1++)
        {
            strcpy(command_list[z1], final_command_redirecton[z1]);
        }
        for (long long op = final_argc; op <= argc; op++)
        {
            command_list[op] = NULL;
        }
    }
    if (check == -1)
    {
        return;
    }
    if (command_list[0] == NULL)
    {
        return;
    }
    command_list[final_argc] = NULL;
    if (strcmp(command_list[0], "cd") == 0)
    {
        cd(final_argc, command_list);
    }
    else if (strcmp(command_list[0], "echo") == 0)
    {
        echo(final_argc, command_list);
    }
    else if (strcmp(command_list[0], "jobs") == 0)
    {
        // we are passing a argument that is bascially flag it can be "-r" or "-s"
        if (command_list[1] == NULL)
        {
            jobs(NULL);
        }
        else
        {
            jobs(command_list[1]);
        }
    }
    else if (strcmp(command_list[0], "pwd") == 0)
    {
        pwd(final_argc);
    }
    else if (strcmp(command_list[0], "fg") == 0)
    {

        calculate_fg(final_argc, command_list);
        if (var_fg < 0)
        {
            var_fg = -var_fg;
        }
    }
    else if (strcmp(command_list[0], "history") == 0)
    {

        history(final_argc, command_list);
    }
    else if (strcmp(command_list[0], "bg") == 0)
    {

        if (final_argc < 2)
        {
            printf("Error: TOO FEW ARGUMENTS\n");
        }
        else if (final_argc > 2)
        {
            printf("Error: TOO MANY ARGUMENTS\n");
        }
        else
        {
            calculate_bg(final_argc, command_list);
        }
    }
    else if (strcmp(command_list[0], "sig") == 0)
    {
        if (final_argc == 3)
        {
            int job_index = atoi(command_list[1]);
            int signal_index = atoi(command_list[2]);
            int jb_pid = background_pid[job_index - 1];
            sig(final_argc,jb_pid,signal_index);
        }
    }
    else if (strcmp(command_list[0], "ls") == 0)
    {
        ls(final_argc, command_list);
    }
    else if (strcmp(command_list[0], "pinfo") == 0)
    {
        pinfo(final_argc, command_list);
    }
    else if (strcmp(command_list[0], "discover") == 0)
    {
        discover(final_argc, command_list);
    }
    else if (!strcmp(command_list[0], "exit") || !strcmp(command_list[0], "EXIT"))
    {
        print_history();
        stooped = 1;
    }
    else
    {
        int pid = fork(); // creating a child process
        command_list[final_argc] = NULL;
        if (pid > 0)
        {
            if (check == 0 && pid > 0)
            {
                int ctrz_aya;
                time_t start = time(NULL);
                signal(SIGTTIN, SIG_IGN); // when some background process tries to read/ writefrom terminal then SIGTIN generated
                signal(SIGTTOU, SIG_IGN); // such read/w signal are said to be ignored
                waitpid(pid, &ctrz_aya, WUNTRACED);
                time_t end = time(NULL);
                signal(SIGTTIN, SIG_IGN); // when some background process tries to read/ writefrom terminal then SIGTIN generated
                signal(SIGTTOU, SIG_IGN);
                int diff = end - start;
                if (WIFSTOPPED(ctrz_aya)) // generated when ctrl z
                {
                    pidu = pid; // global variable that stores value of fg process
                    char command[100];
                    strcpy(command, command_list[0]);
                    long long len = strlen(command);
                    len++;

                    for (long long hj = 0; hj < 200; hj++)
                    {
                        if (background_pid[hj] == 0)
                        {
                            background_pid[hj] = pid;
                            bgCommand[hj] = (char *)malloc((len) * sizeof(char));
                            final[hj] = (char *)malloc(20 * sizeof(char));
                            if (!flag_check)
                            {
                                // so we have this bgCommand array externed to stores background commands
                                strcpy(bgCommand[hj], command_list[0]);
                                // this final is basically last part of the command which for sleep 7 is 7
                                if (command_list[1] == NULL)
                                {
                                    final[hj] = NULL;
                                }
                                else
                                {

                                    strcpy(final[hj], command_list[1]);
                                }
                            }
                            else
                            {
                                strcpy(bgCommand[hj], command_list[0]);
                                if (command_list[1] == NULL)
                                {
                                    final[hj] = NULL;
                                }
                                else
                                {
                                    strcpy(final[hj], command_list[1]);
                                }
                            }
                            break;
                        }
                    }
                }
                // performs the task of took.. time in fg processs
                if (diff >= 1)
                {
                    char *hey = (char *)malloc(1000 * sizeof(char));
                    cutu += end - start;
                    sprintf(hey, "took %lld", cutu);
                    fgo = 1;
                    strcpy(fgu, hey);
                    free(hey);
                }
            }
            else if (check == 1 && pid > 0)
            {
                // for bacground process here check is for if process is bacground
                printf("COMMAND- %s, PID : %d\n", command_list[0], pid);
                char command[100];

                strcpy(command, command_list[0]);
                long long len = strlen(command);
                len++;
                for (long long i = 0; i < 200; i++)
                { // store pid of the processes in pid array and name in background command array
                    if (background_pid[i] == 0)
                    {
                        background_pid[i] = pid;
                        bgCommand[i] = (char *)malloc((len) * sizeof(char));
                        final[i] = (char *)malloc(20 * sizeof(char));
                        if (!flag_check)
                        {
                            strcpy(bgCommand[i], command_list[0]);
                            if (command_list[1] == NULL)
                            {
                                final[i] = NULL;
                            }
                            else
                            {
                                strcpy(final[i], command_list[1]);
                            }
                        }
                        else
                        {
                            strcpy(bgCommand[i], command_list[0]);
                            if (command_list[1] == NULL)
                            {
                                final[i] = NULL;
                            }
                            else
                            {
                                strcpy(final[i], command_list[1]);
                            }
                        }
                        break;
                    }
                }
            }
        }
        else if (pid < 0)
        {
            // couldnt be forked
            perror("PROBLEM OCCURED");
            return;
        }
        else
        {
            if (check)
            {
                setpgid(0, 0);
                /*

The call setpgrp() is equivalent to setpgid(0,0). setpgid() sets the process group ID of the process specified by pid to pgid. If pid is zero, the process ID of the current process is used. If pgid is zero, the process ID of the process specified by pid is used.*/
            }

            if (execvp(command_list[0], command_list) < 0)
            {
                perror("Error");
                exit(1);
            }
        }
    }
    check = 1; // setting background to one
    argc = 0;  // so for next the new command list starts from zero
}
// implementation of pipeline
void pipe_line(char *command_list[], int argc, int check)
{
    // so we have this new command list to serve as argv for multiple pipe line recursive call
    stringg new_comand_list[50];
    for (element_type all = 0; all < 50; all++)
    {
        new_comand_list[all] = (stringg)malloc(sizeof(char) * 100);
    }

    int pipe_index = -1; // default set to -1 indeed
    int checkk = 0;
    // this function checks of we have pipe in the command ..so  sets the pipe index to index where pipe is
    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(command_list[i], "|"))
        {
            pipe_index = i;
            checkk = 1;
        }
        if (checkk == 1)
        {
            break;
        }
    }
    if (pipe_index != -1)
    {
        int virtual_pipe[2];
        // creating virtual pipe in which default command pipe redirects it
        int pipe_success = 0;
        pipe_success = pipe(virtual_pipe);
        if (pipe_success == -1)
        {
            perror("| COULN'T REDIRECT\n");
            return;
        }
        // Duplicate FD to FD2, closing FD2 and making it open on the same file
        int stdoutt = STDOUT_FILENO;
        int stdinn = STDIN_FILENO;
        int duplicate_out = 0;
        duplicate_out = dup2(virtual_pipe[1], stdoutt);
        if (duplicate_out == -1)
        {
            perror("| CAN'T BE DUPLICATED TO STDOUT\n");
            return;
        }
        command_list[pipe_index] = NULL;
        // calling cat output.txt for case cat output.txt | head -5 | tail-3 say
        handle(command_list, pipe_index, check);
        dup2(shell_stdout, stdoutt);
        close(virtual_pipe[1]);
        int duplicate_in = dup2(virtual_pipe[0], stdinn);
        if (duplicate_in == -1)
        {
            perror("| CAN'T BE DUPLICATED TO STDIN\n");
            return;
        }
        // recursviely calling pipe for further command after the first pipe
        int start_new_cmd_list = pipe_index + 1;
        for (int j = start_new_cmd_list; j < argc; j++)
        {
            int new_cmd_lst_ind = j - pipe_index - 1;
            strcpy(new_comand_list[new_cmd_lst_ind], command_list[j]);
        }
        int new_argc = argc - pipe_index - 1;
        new_comand_list[new_argc] = NULL;
        // new argc become tota argc- (pipeindex+1)(already executed command till this)
        pipe_line(new_comand_list, new_argc, check);
       close(virtual_pipe[0]);
        // in case not dupped due to anyreason output and input are brought back to standard input and output
        dup2(shell_stdin, STDIN_FILENO);
        dup2(shell_stdout, STDOUT_FILENO);
    }
    else
    {
        command_list[argc] = NULL;
        // no pipe so simply argc and argv remains the same
        handle(command_list, argc, check);
        // in case not dupped due to anyreason output and input are brought back to standard input and output
        dup2(shell_stdin, STDIN_FILENO);
        dup2(shell_stdout, STDOUT_FILENO);
    }
}
void execute(stringg command, int check)
{

    check = 1;

    char *command_list_1[MAX_LIMITS];
    element_type argc2 = 0;
    int total_ampercent = 0;
    // counting total ampercant
    for (long long i = 0; i < strlen(command); i++)
    {
        if (command[i] == '&')
        {
            total_ampercent++;
        }
    }
    // tokenizing on ampercant
    stringg tokenize = strtok(command, "&");
    do
    {
        command_list_1[argc2++] = tokenize;
        tokenize = strtok(NULL, "&");

    } while (tokenize != NULL);
    command_list_1[argc2] = NULL;

    for (long long k = 0; k < argc2; k++)
    {
        char *command_list[MAX_LIMITS];
        int argc = 0;
        // its checking that if total commands == total ampercant then all are background
        // otherwise we have last one has foreground rest as background , so we put check =0 for that particular fg pricess
        if (((argc2 - 1) == total_ampercent) && (k == (argc2 - 1)))
        {
            check = 0;
        }
        // tokenize on basis of space and tabs.
        stringg tokenize1 = strtok(command_list_1[k], " \t\r\n\a");
        do
        {
            command_list[argc++] = tokenize1;
            tokenize1 = strtok(NULL, " \t\r\n\a");

        } while (tokenize1 != NULL);
        command_list[argc] = NULL;
        pipe_line(command_list, argc, check);
    }
}
