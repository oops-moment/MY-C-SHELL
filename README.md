# MY-C-SHELL
---

## Requirements

- GCC compiler
- Ubuntu

## Running Shell

From the root directory of project, run `make` followed by `./a.out`.

## File & Functions : appropriate comments added for explaination sake

### Supporting Files  :  Files containing functions required for proper functioning of the shell.
---
#### NOTE: Each .c file of function has it's corresponding .h file in which function prototype is defined.
## *`main.c`*
  - Welcomes user with welcome message :p.
  - reads previous history from history.txt file.
  - calls the display function for to print prompt.
  - takes the input and updates the history.
  - tokenize on the basis of ;.
  - calls the functions based upon the input user enters.
  - prints the history onto file if user press exit.
#### ASSUMPTIONS IN MAIN : 
- If input is just space/ tabs the program continues to  run ie asks user for next input ignoring space / tab entered previously.
-Maximum size of input assumed to be MAX_LIMITS is 2000.
---
## *`execute.c`*
  - Counts the total ampercant and tokenize on basis of ampercant.
  - After this tokenize on basis of tab and spaces.
  - Compare total ampercent with no of commands seperated with & then all are background else you have last as foreground and rest of background.
  - compares command with echo/ls/discover/history/pwd etc and calls corresponding functions.
  - When user enters "exit" then prints the last 20 processes onto history file
  - If command matches with none of defined processes then execvp runs it else commmand is declared invalid.
  -  It runs the foreground and background processes by forking and providing each background process with pid and printing adequate error . `&` (used for running process in background) can come anywhere in command.

  - *REDIRECTION* was taken care of by considering all three cases and adequately redirecting them using dup2 and stdout/stdin.

  - *PIPELINE* so pipeline is redirecting output of one command to another as input inbilt pipe function was used for the same.

  - *SIGNAL HANDLING* 
     - CTRL C:  handled via sendling signal SIGINT , on going fg process is terminated.
     - CTRL Z:  handled via SIGTSTP / WIFSTOPPED. Here fg process is sent to background and its status is set to stopped.
     - CTRL D: check by the empty buffer. ONce detected , user is logged out of terminal.

#### ASSUMPTIONS IN EXECUTE : 
- If prompt doesn't appear due to any reason press "ENTER"
- If you want to exit the program ie exit the shell don't forget to enter "EXIT" since it updates the history.txt.
- IN fg prompt total time of all fg processes is printed.el sleep 2 ; sleep 4 & sleep 6 will give took 8.(6+2)
- In *redirection* it's asssumed that there will be appropriate spaces.
---

## *`display.c`*

  - Prints prompt onto the screen make use of inbuilt    functons like getcwd, gethostname, geteuid for user id .
  - Checks for terminated child processes in case background process runs.
  - Prints appropriate statement onto screen depending on how to process has exited.
  - In case we have foreground process and it takes more than 1 sec  to execute then prompts prints the time along on just next prompt.
  ---

## *`echo.c`*

  - Prints tokenized arguments given after echo onto screen.
#### ASSUMPTIONS IN ECHO : 
- Any multiple spaces and tabs are ignored ie tokenized.
- Example echo hi (double tabs) fine is printed as hi fine.
---

## *`pwd.c`*

  - prints the present working directory onto the screen.
  ---

## *`pinfo.c`*

  - prints the desired information onto screen  which includes the process status such as S(Static)/R(R+ : running), virtual memory.
  - Information was extracted from /stat/ , /prc/ , /exec/ files via use of /status/ etc
  - 4th and 7th value helps checking if the process is fore ground or not.
  -for when no argument is passed along with pinfo then getpid() gives you the value of pid of current running shell.
  ---

## *`cd.c`*

  - Navigate to different directories depending on users input
  - cases of navigating to existing folder, home directory , '.',"..","~","-" etc are handled.
---
## *`ls.c`*

  - Prints all files/sub-directories in a location.
  - Flags implemented: `a` and `l` where a corresponds to printing "." and "..".
  - Multiple directories supported.
  - SCANDIR used for scanning file via struct dirent 
---
## *`history.c`*

  - Prints the minimum of (total commands entered, 10). Three functions work together for history these are read history from the history.txt file for previous executon , secondly write_history this regularly updates the history depending on command entered by user given not same as previous command.
  - Last recent 20 commmands are stored in history.txt file.
#### ASSUMPTIONS IN HISTORY :
 - NOTE before exiting any process one must enter "EXIT" because i put condition of writing onto file in this since you require txt file for next process.
 ---

## *`discover.c`*

- print all the content of directory given.
- in case no directory specified , home directory is assumed to be directory
- flags '-d' and '-f' were implemented for directory and files.
#### ASSUMPTIONS IN HISTORY :
 - IN discover if -d flag is there the file / file search won't be there since only since d flag.
 - Order should be considered fro input directory flags file name
 - if some file is searched then only its path is printed depening on flags (-f) should exist.
 ---

 ## *`sig.c`*

- it takes two parameter that is the serial numer og the job and signal number
- on getting a signal a corresponding kill is generated
#### ASSUMPTIONS IN SIG
- for knowing the job number user must enter the command : jobs first since ordering might change with time depending on executed commands.
---

## *`jobs.c`*

- it prints the list of all process in background
- takes flag as "-r" and "-s" where r is to print all running processes and "-s" for stopped , structure was used and was sorted on basis of q sort.
#### ASSUMPTIONS IN SIG
- Serial number of commands may keep varying from command to command as user might enter command such as "fg" which changes array by removing a process.
---

## *`fg.c`*

- it brings the process at given serial number to foreground and executes it.(state changed to runnning)
- once a process is brought ot foreground , its deleted from background array and hence the jobs are reordered.
#### ASSUMPTIONS IN FG
- not considered mentioning the time took for this case.
---

## *`bg.c`*

- it runs the given job number process in background.
- Process runs like a normal background process and terminates .
- Once terminated it's instance is removed from background array.

#### LEFT THE AUTO COMPLETION PART DUE TO YOUTH IGF EVENT ( VOLUNTEER ): hoping to do it sooner 
---


 



    

