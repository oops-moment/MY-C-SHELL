
#ifndef __LS_H
#define __LS_H
#include <stdbool.h>
#include <sys/stat.h>
extern char home_directory[];

void ls(int argc, char *argv[]);
void print_files(char* file, long long flag_l, long long flag_a, long long count,char*path);
void perm_date_time(struct stat f_stat, char*file_paths);

#endif