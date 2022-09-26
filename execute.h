#ifndef __EXECUTE_H
#define __EXECUTE_H
extern long long stooped;
extern int log_count;
extern long long cutu;
extern char logs[256][21];
extern int shell_stdout;
extern int shell_stdin;
extern int pidu;
extern char*final[100];
int check_validss(int argc, char stringgs[50]);
void execute(char *command, int check);
void pipe_line(char *command_list[], int argc, int check);
void handle(char *command_list[], int argc, int check);
extern int background_pid[200]; // array that stores pid's of backgroud process
extern char *bgCommand[200];
#endif
