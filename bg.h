#ifndef __BG_H
#define __BG_H
void calculate_bg(int argc, char *argv[]);
extern int background_pid[200]; // array that stores pid's of backgroud process
extern char *bgCommand[200];    // stores background_commands
#endif
