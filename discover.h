#ifndef __DISCOVERF_H
#define __DISCOVERF_H
#include <stdbool.h>


void recursive_call(char *basePath, char *path_f, int flag_f, int flag_d, char file_name[100], long long count);
void discover(int argc,char*argv[]);
extern char home_directory[];
#endif