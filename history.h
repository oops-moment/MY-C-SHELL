#ifndef __HISTORY_H
#define __HISTORY_H

extern char home_directory[];
extern int log_count;
extern char logs[256][21];
long long check_argu(long long arguments);
void history(int argc, char *argv[]);
void write_history(char *command);
void read_history();
void print_history();

#endif