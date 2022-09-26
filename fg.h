#ifndef __FG_H
#define __FG_H
void calculate_fg(int argc, char *argv[]);
extern int background_pid[200]; // array that stores pid's of backgroud process
extern char *bgCommand[200];
extern int var_fg;
#endif
