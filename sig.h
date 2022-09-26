#ifndef __SIG_H
#define __SIG_H
extern int background_pid[200]; // array that stores pid's of backgroud process
extern char *bgCommand[200];
int check_v(int argc);
int check_pid(int pid);
void sig(int argc, int pid, int signal_index);
#endif
