#ifndef __CD_H
#define __CD_H
extern char home_directory[]; // stores the path of  current working directory .. absolute path
extern char previous_dir[];
void cd(long long no_arguments,char *commmand_list[]);

#endif