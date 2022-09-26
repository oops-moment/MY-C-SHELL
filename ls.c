// verified
#include <pwd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <grp.h>
#include <time.h>
#include <stdlib.h>
#include "ls.h"
#include <string.h>
typedef char *stringg;
typedef struct passwd *main_struct;
typedef long long element_type;
#define MAX_LIMITS 1000
void remove_tilda(char path[], char file[])
{
    // sp here you remve tilda and extract the path
    element_type n = strlen(file);
    for (element_type i = 0; i < (n - 1); i++)
    {
        char temp = file[i + 1];
        file[i] = temp;
    }
    file[n - 1] = '\0';
    strcpy(path, home_directory);
    strcat(path, file);
}
void ls(int argc, char *argv[])
{
    element_type flag_l = false, flag_a = false;
    // checks which flag is present -l or -a or both
    for (long long i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-l") || !strcmp(argv[i], "-la") || !strcmp(argv[i], "-al"))
        {
            flag_l = 1;
        }
        if (!strcmp(argv[i], "-a") || !strcmp(argv[i], "-la") || !strcmp(argv[i], "-al"))
        {
            flag_a = 1;
        }
    }

    char *file_v[MAX_LIMITS];
    int file_c = 0;
     // here in file_v you stores the file names and file_c maintains the count
    for (int i = 1; i < argc; i++)
    {

        if (argv[i][0] == '-')
        {
            continue;
        }
        else
        {
            file_v[file_c] = argv[i];
            file_c = file_c + 1;
        }
    }
    char cwd[MAX_LIMITS];
    if (file_c == 0)
    {

        getcwd(cwd, MAX_LIMITS);
        file_v[0] = cwd;
        file_c = 1;
    }
    element_type total = file_c;
    for (element_type i = 0; i < total; i++)
    {

        print_files(file_v[i], flag_l, flag_a, total - 1, cwd);
        printf("\n");
    }
}
//checks using ISDIR if given path is that of folder
element_type check_isfolder(stringg path)
{
    char base[MAX_LIMITS];
    getcwd(base, MAX_LIMITS);
    strcat(base, "/");
    strcat(base, path);
    struct stat p_stat;
    stat(base, &p_stat);

    if (!S_ISDIR(p_stat.st_mode))
    {
        return 0;
    }
    return 1;
}
//checks using ISDIR if given path is that of executable file
element_type check_ifexec(stringg path)
{
    char base[MAX_LIMITS];
    getcwd(base, MAX_LIMITS);
    strcat(base, "/");
    strcat(base, path);
    struct stat p_stat;
    stat(base, &p_stat);

    if ((S_IEXEC) & (p_stat.st_mode))
    {

        return 1;
    }
    return 0;
}
void print_files(stringg file, element_type flag_l, element_type flag_a, element_type count, char *paths)
{
    char path[MAX_LIMITS];
    if (file[0] != '~')
    {
        strcpy(path, file);
    }
    else
    {
        remove_tilda(path, file);
    }

    struct stat p_stat;
    stat(path, &p_stat);

    if (!S_ISDIR(p_stat.st_mode))
    {
        if (flag_l == 1)
        {   
            // calcullate the specifications
            perm_date_time(p_stat, path);
        }

        if (check_isfolder(path))
        {
            int check_idot = 0;
                for (long long i = 0; i < strlen(path); i++)
                {
                    if (path[i] == '.')
                    {
                        check_idot = 1;
                        break;
                    }
                }
                if (!check_idot || !strcmp(path,".")||!strcmp(path,".."))
                    printf("\033[0;94m");
            printf("%s\n", path);
            printf("\033[0;m");
        }
        else if (check_ifexec(path))
        {
            if (!strcmp(path, "a.out"))
                printf("\033[0;32m");
            printf("%s\n", path);
            printf("\033[0;m");
        }
        else
        {
            printf("%s\n", path);
        }
    }
    else
    { // is a directory
        if (count != 0)
        {
            if (check_isfolder(path))
            {
                int check_idot = 0;
                for (long long i = 0; i < strlen(path); i++)
                {
                    if (path[i] == '.')
                    {
                        check_idot = 1;
                        break;
                    }
                }
                if (!check_idot || !strcmp(path,".")||!strcmp(path,".."))
                    printf("\033[0;94m");
                printf("\n%s:\n", path);
                printf("\033[0;m");
            }
            else if (check_ifexec(path))
            {

                if (!strcmp(path, "a.out"))
                    printf("\033[0;32m");
                printf("\n%s:\n", path);
                printf("\033[0;m");
            }
            else
            {
                printf("%s\n", path);
            }
        }
        struct dirent **files;
        // scans all the file in the directory given by path retun value is the number of files
        element_type t_files = scandir(path, &files, NULL, alphasort);
        for (element_type i = 0; i < t_files; i++)
        {
            struct dirent *fl = files[i];
            stringg f_names = (stringg)malloc(MAX_LIMITS * sizeof(char));

            stringg f_name;
            f_name = fl->d_name;
            if (flag_a == 0)
            {
                f_name = fl->d_name;
                if (!(strcmp(f_name, ".")))
                {
                    continue;
                }
                if (!strcmp(f_name, ".."))
                {
                    continue;
                }
            }
            if (flag_l == 1)
            {
                char f_path[2000];
                strcpy(f_path, path);
                strcat(f_path, "/");
                strcat(f_path, f_name);
                struct stat f_stat;
                stat(f_path, &f_stat);
                perm_date_time(f_stat, f_path);
            }

            if (check_isfolder(f_name))
            {
                int check_idot = 0;
                for (long long i = 0; i < strlen(f_name); i++)
                {
                    if (f_name[i] == '.')
                    {
                        check_idot = 1;
                        break;
                    }
                }
                if (!check_idot|| !strcmp(f_name,".") || !strcmp(f_name,".."))
                    printf("\033[0;94m");
                printf("%s\n", f_name);
                printf("\033[0;m");
            }
            else if (check_ifexec(path))
            {
                if (!strcmp(f_name, "a.out"))
                    printf("\033[0;32m");
                printf("%s\n", f_name);
                printf("\033[0;m");
            }
            else
            {
                printf("%s\n", f_name);
            }
            free(f_names);
        }
    }
}

void perm_date_time(struct stat f_stat, char *file_path)
{
     // caculate the time using memebers of struct time_str predefied
    stringg time_str = (stringg)malloc(70 * sizeof(char));
    struct tm filetime;
    time_t ft = f_stat.st_mtime;
    localtime_r(&ft, &filetime);
    struct tm today;
    time_t now = time(NULL);
    localtime_r(&now, &today);
    struct passwd *own_name = getpwuid(f_stat.st_uid);
    struct group *grp_name = getgrgid(f_stat.st_gid);
    char is_d;
    if (S_ISDIR(f_stat.st_mode))
    {
        is_d = 'd';
    }
    else
    {
        is_d = '-';
    }
    char user[4];
    char others[4];
    char group[4];
      // struct f_stat we extract the permisssions of all the user / group / owner as in assignment 1
    if (f_stat.st_mode & S_IRUSR)
    {
        user[0] = 'r';
    }
    else
    {
        user[0] = '-';
    }

    if (f_stat.st_mode & S_IWUSR)
    {
        user[1] = 'w';
    }
    else
    {
        user[1] = '-';
    }
    if (f_stat.st_mode & S_IXUSR)
    {
        user[2] = 'x';
    }
    else
    {
        user[2] = '-';
    }
    if (f_stat.st_mode & S_IRGRP)
    {
        group[0] = 'r';
    }
    else
    {
        group[0] = '-';
    }

    if (f_stat.st_mode & S_IWGRP)
    {
        group[1] = 'w';
    }
    else
    {
        group[1] = '-';
    }
    if (f_stat.st_mode & S_IXGRP)
    {
        group[2] = 'x';
    }
    else
    {
        group[2] = '-';
    }
    if (f_stat.st_mode & S_IROTH)
    {
        others[0] = 'r';
    }
    else
    {
        others[0] = '-';
    }

    if (f_stat.st_mode & S_IWOTH)
    {
        others[1] = 'w';
    }
    else
    {
        others[1] = '-';
    }
    if (f_stat.st_mode & S_IXOTH)
    {
        others[2] = 'x';
    }
    else
    {
        others[2] = '-';
    }

    int directory_links = f_stat.st_nlink;
    long file_size = f_stat.st_size;
// The strftime() function is used to convert date and time objects to their string representation. 
//It takes one or more input of formatted code and returns the string representation.
    strftime(time_str, sizeof(time_str), "%b %e %H:%M", &filetime);
    printf("%c%c%c%c%c%c%c%c%c%c ", is_d, user[0], user[1], user[2], group[0], group[1], group[2], others[0], others[1], others[2]);
    printf("%8d  %8s  %8s  %8ld ", directory_links, own_name->pw_name, grp_name->gr_name, file_size);
    printf("%s ", time_str);
    free(time_str);
}
