//verified
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "discover.h"
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define okay_limit 200
typedef char *stringg;
void discover(int argc, stringg argv[])
{
    long long count = 0;
    if (argc == 1)
    {
        recursive_call(".", ".", 1, 1, NULL, count);
        return;
    }
    else
    {
        int flag_files = 0;
        int flag_folder = 0;
        int no_flags = 0;
        int is_file = 0;
        for (long long i = 1; i < argc; i++)
        {
            if (argv[i][0] == '"')
            {
                is_file = 1;
            }
            if (strcmp(argv[i], "-f") == 0)
            {
                flag_files = 1;

                no_flags++;
            }
            if (strcmp(argv[i], "-d") == 0)
            {
                flag_folder = 1;
                no_flags++;
            }
        }
        if (argc == 2)
        {
            if (argv[1][0] != '-')
            {
                if (argv[1][0] == '"')
                {
                    char f_name[100];
                    long long i = 0;
                    for (i = 0; i < strlen(argv[1]) - 2; i++)
                    {
                        f_name[i] = argv[1][i + 1];
                    }
                    f_name[i] = '\0';
                    // printf("%s name\n",f_name);
                    recursive_call(".", ".", 1, 1, f_name, count);
                }
                else
                {
                    recursive_call(argv[1], argv[1], 1, 1, NULL, count);
                }
            }
            else
            {
                if (strcmp(argv[1], "-d") == 0)
                    recursive_call(".", ".", 0, 1, NULL, count);
                else
                    recursive_call(".", ".", 1, 0, NULL, count);
            }
        }
        else if (argc == 3)
        {

            if (no_flags == 0)
            {

                char f_names[100];
                long long i = 0;

                for (i = 0; i < strlen(argv[2]) - 2; i++)
                {
                    f_names[i] = argv[2][i + 1];
                }
                f_names[i] = '\0';
                recursive_call(argv[1], argv[1], 1, 1, f_names, count);
            }
            else if (no_flags == 1)
            {
                if (is_file)
                {
                    recursive_call(".", ".", flag_files, flag_folder, argv[4], count);
                }
                else
                {
                    recursive_call(argv[1], argv[1], flag_files, flag_folder, NULL, count);
                }
            }
            else if (no_flags == 2)
            {
                recursive_call(".", ".", flag_files, flag_folder, NULL, count);
            }
        }
        else if (argc == 4)
        {
            if (no_flags == 1)
            {
                char f_name[100];
                long long i = 0;
                for (i = 0; i < strlen(argv[3]) - 2; i++)
                {
                    f_name[i] = argv[3][i + 1];
                }
                f_name[i] = '\0';
                // printf("%s name\n",f_name);
                recursive_call(argv[1], argv[1], flag_files, flag_folder, f_name, count);
            }
            else if (no_flags == 2)
            {
                if (is_file)
                {
                    char f_name[100];
                    long long i = 0;
                    for (i = 0; i < strlen(argv[3]) - 2; i++)
                    {
                        f_name[i] = argv[3][i + 1];
                    }
                    f_name[i] = '\0';
                    // printf("%s name\n",f_name);
                    recursive_call(".", argv[1], flag_files, flag_folder, f_name, count);
                }
                else
                {
                    recursive_call(argv[1], argv[1], flag_files, flag_folder, NULL, count);
                }
            }
        }
        else if (argc == 5)
        {
            recursive_call(argv[1], argv[1], atoi(argv[2]), atoi(argv[3]), argv[4], count);
        }
        else
        {
            printf("Too many argument\n");
            return;
        }
    }

    return;
}

void recursive_call(stringg intial_path, stringg path_f, int flag_f, int flag_d, char file_name[100], long long count)
{
    // printf("path is %s\n",intial_path);

    if (strcmp(intial_path, "~") == 0)
    {
        strcpy(intial_path, home_directory);
    }
    char path[1000];
    struct dirent *file_ptr;
    DIR *dir = opendir(intial_path);
    int file_find = 0;
    if (file_name != NULL)
    {
        file_find = 1;
    }

    if (dir == 0)
    {
        return;
    }

    while ((file_ptr = readdir(dir)) != NULL)
    {
        if (strcmp(file_ptr->d_name, ".") != 0 && strcmp(file_ptr->d_name, "..") != 0)
        {

            if ((file_ptr->d_type == 4 && flag_d == 1) && (file_find == 0))
            {

                //  printf("%s \n", file_ptr->d_name);
                char help_path[1000];
                // getcwd(help_path, 1000);
                if (count == 0)
                {
                    printf(".\n");
                    count++;
                }
                if (intial_path[0] != '.')
                {
                    strcpy(help_path, "./");
                    strcat(help_path, intial_path);
                    strcat(help_path, "/");
                    strcat(help_path, file_ptr->d_name);
                    printf("%s\n", help_path);
                }
                else
                {
                    strcpy(help_path, intial_path);
                    strcat(help_path, "/");
                    strcat(help_path, file_ptr->d_name);
                    printf("%s\n", help_path);
                }
            }
            if (((file_ptr->d_type == 8) && (flag_f == 1)))
            {

                if (file_find == 1)
                {
                    if (!strcmp(file_name, file_ptr->d_name))
                    {

                        // printf("file was found\n");
                        char help_path[1000];
                        if (intial_path[0] != '.')
                        {
                            strcpy(help_path, "./");
                            strcat(help_path, intial_path);
                            strcat(help_path, "/");
                            strcat(help_path, file_ptr->d_name);
                            printf("%s\n", help_path);
                        }
                        else
                        {
                            strcpy(help_path, intial_path);
                            strcat(help_path, "/");
                            strcat(help_path, file_ptr->d_name);
                            printf("%s\n", help_path);
                        }
                    }
                }
                else
                {
                    if (flag_d)
                    {
                        if (count == 0)
                        {
                            printf(".\n");
                            count++;
                        }
                    }
                    // printf("%s \n", file_ptr->d_name);
                    char help_path[1000];
                    if (intial_path[0] != '.')
                    {
                        strcpy(help_path, "./");
                        strcat(help_path, intial_path);
                        strcat(help_path, "/");
                        strcat(help_path, file_ptr->d_name);
                        printf("%s\n", help_path);
                    }
                    else
                    {
                        strcpy(help_path, intial_path);
                        strcat(help_path, "/");
                        strcat(help_path, file_ptr->d_name);
                        printf("%s\n", help_path);
                    }
                }
            }
            strcpy(path, intial_path);
            strcat(path, "/");
            strcat(path, file_ptr->d_name);
            recursive_call(path, path_f, flag_f, flag_d, file_name, count);
        }
    }

    closedir(dir);
}