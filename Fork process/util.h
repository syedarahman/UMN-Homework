/********************
 * util.h
 *
 * You may put your utility function definitions here
 * also your structs, if you create any
 *********************/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

// the following ifdef/def pair prevents us from having problems if 
// we've included util.h in multiple places... it's a handy trick
#ifndef _UTIL_H_
#define _UTIL_H_

#define INELIGIBLE 0
#define READY 1
#define RUNNING 2
#define FINISHED 3

typedef int bool;
#define TRUE 1
#define FALSE 0


#define MAX_LENGTH 1024
#define MAX_CHILDREN 10
#define MAX_NODES 10

// This stuff is for easy file reading
FILE * file_open(char*);
char * file_getline(char*, FILE*);
int is_file_exist(char *);
int get_file_modification_time(char *);
int compare_modification_time(char *, char *);
int is_empty(char *);


typedef struct target{
  char name[70];       
  struct target* dep[10]; 
	pid_t pid;
        bool isTarget;
	int nDependencyCount;
	char szDependencies[10][64];
	char szCommand[64];
	int nStatus;
  //	target_t next;
}target_t;

int makeargv(const char *s, const char *delimiters, char ***argvp);
void freemakeargv(char **argv);

#endif
