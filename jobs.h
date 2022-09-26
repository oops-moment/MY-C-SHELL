#ifndef __JOBS_H
#define __JOBS_H

void jobs();
extern int background_pid[200]; // array that stores pid's of backgroud process
extern char *bgCommand[200];
extern char *final[100];
#endif