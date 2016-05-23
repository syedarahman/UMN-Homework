/* CSci4061 S2016 Assignment 1
* login: tuomi075
* date: 02/17/16
* name: Vasiliy Grin, Jeffrey Tuomi, Syeda Rahman
* id: 4506267, 5106055, 4524416 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <unistd.h>

#include "util.h"



//representing DAG as an array of targets
target_t* targets [MAX_NODES]; 
int targetCount = 0;//counter to keep track of how many targets
bool n = FALSE;  //flags set for different situations
bool B = FALSE;
bool m = FALSE;



target_t* makeTarget(char* targetName){
    int n;
    for(n = 0; n < targetCount; n++)
    {
       if(!strcmp(targets[n]->name,targetName))
       { 
          return targets[n];
       }
   }
    //creating new node here and making room for it
    target_t* new = (target_t *) malloc(sizeof(target_t));
    new->nStatus = INELIGIBLE; //init status
    new->nDependencyCount = 0; //init dependecy count
    new->isTarget = FALSE;     //init target
    strcpy(new->name,targetName);
    
    targets[targetCount++]=new;
    //returning node type target
    return new;
}


target_t* find(char* tarName){
  int n;
  if(!strlen(tarName))
    {
      return targets[0];
    }
  for(n = 0; n < targetCount; n++)
    {
      if(!strcmp(targets[n]->name,tarName))
	{
	  return targets[n];
	}
    }
  return NULL;
}


//Parsing Function: parses makefile from user. If no input resorts to defult 
int parse(char * lpszFileName)
{//initisting varables 
	int nLine=0;
	char szLine[1024];
	char cpy[1024];
	char * lpszLine;
	char * target;
	char * szCommand;
	
	FILE * newFile = file_open(lpszFileName);
	target_t* current = NULL;
	target_t* dep = NULL;

	if(newFile == NULL)
	{
	   perror("Error: Can't open Makefile \n");
	   return -1;
	}

	while(file_getline(szLine, newFile) != NULL) 
	{
		nLine++;
		// this loop will go through the given file, one line at a time
		// this is where you need to do the work of interpreting
		// each line of the file to be able to deal with it later
		//Remove newline character at end if there is one
		lpszLine = strtok(szLine, "\n"); 
		//You need to check below for parsing. 
		//Skip if blank or comment.
		if (!lpszLine || 0 == (strchr(lpszLine,'#')-lpszLine))
		{
		    continue;
		}
		//remove leading white space
		strcpy(cpy,lpszLine);//store a temp copy
		char* toke = strtok(cpy," \t");
		if(toke == NULL)              
		  continue;                //Skip if whitespace-only.
		//Only single command is allowed.
		//If you found any syntax error, stop parsing.
		if(strchr(lpszLine,':'))
		{
		   target = strtok(lpszLine,": ");
		   if(strncmp(target, "\t", strlen("\t")) == 0)
		   {
		      fprintf(stderr,"Error in Syntax: tab in line %d\n",nLine);
		      exit(1);
		   }
    	   
		   current = makeTarget(target);
		   current->isTarget = TRUE;
		   while((target = strtok(NULL," ")))
		   {
		      dep = makeTarget(target);
		      current->dep[(current->nDependencyCount)++] = dep;
		   }
		}else if(strchr(lpszLine,'\t'))
		{
		   if(!current)
		   {
		      fprintf(stderr,"Error in syntac on line %d, target is unkown\n",nLine);
		      exit(1);
		   }
		   szCommand = strtok(lpszLine,"\t");
		   if(szCommand[0] == '#')
		   {
		      fprintf(stderr,"Error in syntax on line  %d, Invalid comment\n",nLine);
		      exit(1);
		   }
		   strcpy(current->szCommand,szCommand);
		   current = NULL;
		}else
		{
		  // must be a command line that starts with blanks
		   fprintf(stderr,"Syntax Error in line %d, Unexpected leading character\n",nLine);
		   exit(1);
		//If lpszLine starts with '\t' it will be command else it will be target.
		//It is possbile that target may not have a command as you can see from the example on project write-up. (target:all)
		//You can use any data structure (array, linked list ...) as you want to build a graph
		}
	}
	//Close the makefile. 
	fclose(newFile);
	return 0;
}

//TODO  check dependenscies function
bool checkDep(target_t* Target){
  int s;
  printf("checking depndencies..\n");
//check if target exists
  if(!Target)
  {
     return FALSE;
  }
  if(!Target->nDependencyCount)
  { //if this is aleaf then there are no dependencies
    if(Target->isTarget)
    {        
       Target->nStatus = READY;
       return TRUE;
    }else
    {
       if(is_file_exist(Target->name) != -1)
       {
	  Target->nStatus = FINISHED;
       }else
       {
	  printf("dependanct error: Cannot locate target %s\n",Target->name);
	  exit(1);
       }
    }
  }  
    // here is were you look at every sub tree recursivly 
  for(s = 0; s < Target->nDependencyCount; s++)
  {
     if(!checkDep(Target->dep[s]))
     {  
       return FALSE;
     } 
  }
    //update file status
  Target->nStatus = READY;
  return TRUE;
}

//fork
pid_t forkExec(char* szCommand, char* num)
{
  printf("calling forkExecute(command,'n'  \n");
    char **argv = (char **)malloc(sizeof(char *)*30);
    int count;
    int n;
    count = makeargv(szCommand,num,&argv);
    if(strlen(szCommand)!=0)
    { 
       printf(" Now executing: %s \n", szCommand);
    }
    //this is the child 
    pid_t next;
    next = fork();
    if(next == 0)
    {
      //this over here will return if succeful
        execvp(argv[0],&argv[0]);
	fprintf(stderr, "Error: child process did not create succecfully. %s is not working \n ", szCommand);
	exit(1);
    }
    //this were it is for parent
    freemakeargv(argv);
    printf("child created \n");
    return next;
}
  
//execute functions
int execute(target_t *aTarget) 
{
    printf("made it to execute() \n");
    pid_t child;
    int x;
    int result;
    int commandSize;
    int depCount;
    int prev;
    //above variable set
   
    
    // check for dependancies
    if(!aTarget->nDependencyCount)
    {
      //no command provided to execute()
        
	if(aTarget->nStatus == FINISHED)
	{
	   return 0;
	}
	if(strlen(aTarget->szCommand) == 0)
	  return 0;
       
	if(n)
	{
	  //in case of n entered, update status and quit
	   printf("\n %s\n ",aTarget->szCommand);
	   aTarget->nStatus = FINISHED;
	   return 0;
	}
	//now next we execute targets command in a sub process
	printf("Now building target: %s  \n",aTarget->name);
	child = forkExec(aTarget->szCommand," ");
	
	//parents process
	waitpid(child, &result, 0);
	aTarget->nStatus = FINISHED;
    }
    else
    {
      int no = 0;//keep track of dpenedencies
      int check;//compare time stamps
       for(x = 0; x < aTarget->nDependencyCount; x++)
       {
          execute(aTarget->dep[x]);
	  check = compare_modification_time(aTarget->name,aTarget->dep[x]->name);
	  if(check == 1 || check == 0)
	  {
	     no++;     
	  }  
       }
       //case were dependencies are up to date
       if(no == aTarget->nDependencyCount && !B)
       {	 
	    
	     printf(" %s was not built\n", aTarget->name);
	     return 0;
	  
       }
       //this is were Target builds itself
       //first check if there is command entered
       
       //then check the file status and see if it is already complete
       if(aTarget->nStatus == FINISHED)
       {
          return 0;
       }
       if(strlen(aTarget->szCommand) == 0)
	 return 0;
       if(n)
       {
           printf("Command Entered: %s\n",aTarget->szCommand);
           aTarget->nStatus = FINISHED;
	   printf("Status: %d\n", aTarget->nStatus);
           return 0;
       }
       printf("Now building: %s \n", aTarget->name);
       //execute target
       child = forkExec(aTarget->szCommand," ");
       waitpid(child, &result, 0);
       
       aTarget->nStatus = FINISHED;
       printf("Status: %d\n", aTarget->nStatus);
    }
    return 0;
}

      

	/*
	if(!checkDep(Target)) {
	for(s = 0; s < Target->nDependencyCount; n++){
		 fork(Target->dep[s]);
	}
}
if (Target->szCommand) {}
command = strtok(Target->szCommand, " ");
execvp(command, command, Target->szCommand);
kill((long)getpid(), 9);
}
	*/ 
//TODO fork function
//Vas originally had "pid_t fork(char* cmd, char *delim)", and I wasn't sure why, so I took it out for now. 

// pid_t fork(char* cmd) { 
// pid_t pid = fork();
//   int  var = 3;
//   int  *ip;
//   ip = &var;
//   if (pid > 0) { 
// 	wait(ip);
//   }
//   if (pid==0) { 
//   	execv(“/bin/ls”, __?__); // I'm stuck HERE. 
//   }
//   else { // if == -1
//   	exit(EXIT_FAILURE);
//     	perror("Fork failed");
//   } 
// }

// Or...:
// pid_t fork(target_t *target)
// {
//   pid_t pid = fork();
//   if (pid > 0) //parent
//   { 
//     waitpid(pid);
//   }
//   if (pid==0) //child
//   { 
//     execute(*target);
//   }
//   else { 
//     exit(EXIT_FAILURE);
//     perror("Fork failed");
//   } 
//   return child;
// }

void show_error_message(char * lpszFileName)
{
	fprintf(stderr, "Usage: %s [options] [target] : only single target is allowed.\n", lpszFileName);
	fprintf(stderr, "-f FILE\t\tRead FILE as a mainfile.\n");
	fprintf(stderr, "-h\t\tPrint this message and exit.\n");
	fprintf(stderr, "-n\t\tDon't actually execute commands, just print them.\n");
	fprintf(stderr, "-B\t\tDon't check files timestamps.\n");
	fprintf(stderr, "-m FILE\t\tRedirect the output to the file specified .\n");
	exit(0);
}

int main(int argc, char **argv) 
{
	// Declarations for getopt
	extern int optind;
	extern char * optarg;
	int ch;
	char * format = "f:hnBm:";
	
	bool isValid = FALSE;

	// Default makefile name will be Makefile
	char szMakefile[64] = "Makefile";
	char szTarget[64];
	char cpy[64];
	char szLog[64];
	szTarget[0] = '\0';

	while((ch = getopt(argc, argv, format)) != -1) 
	{
		switch(ch) 
		{
		case 'f':  //gets name of file
		   strcpy(szMakefile, strdup(optarg));
		  break;
		 case 'n':
		        n = TRUE;
	        	break;
		case 'B'://recompile
		      B = TRUE;
		     	break;
		case 'm':// -m log1.txt
	              m = TRUE;
		     strcpy(szLog, strdup(optarg));
			break;
	 
			default:
			  printf("no arguments \n ");
				show_error_message(argv[0]);
				exit(1);


				//TODO
		}
		//check target definitions
		if (optind < argc && argv[optind][0] != '-' && !strlen(szTarget))
		{// Target hasn't been defined
		    strcpy(szTarget,argv[optind++]);
		}else if(optind < argc && argv[optind][0] != '-' && strlen(szTarget)>0)
		{ //Target is already defined
		   fprintf(stderr, "Too many targets were specified\n");
		   show_error_message(argv[0]);
		}

	}

	argc -= optind;
	argv += optind;

	// at this point, what is left in argv is the targets that were 
	// specified on the command line. argc has the number of them.
	// If getopt is still really confusing,
	// try printing out what's in argv right here, then just running 
	// with various command-line arguments.

	if(argc == 1)
	{
	  if(strlen(szTarget) == 0)
            strcpy(szTarget,argv[0]);
          else{
	    fprintf(stderr, "Too many targets were specified\n");
	    show_error_message(argv[0]);
	  }
	}

	//You may start your program by setting the target that make4061 should build.
	//if target is not set, set it to default (first target from makefile)
	else if(argc > 1)
	{
	    show_error_message(argv[0]);
	    return EXIT_FAILURE;
	} 


	if(is_file_exist(szMakefile) == -1){
	  fprintf(stderr, "'%s' : mo such file \n", szMakefile);
	}

	if(m){
	  if(is_file_exist(szLog)!= -1){ 
	    remove(szLog);
	  }
	  FILE* newFile = fopen(szLog, "a+");
	  if(!newFile){
	    perror("cant open file\n");
	    return EXIT_FAILURE;
	  }
	  else
	  {
	    //save and close
	    dup2(fileno(newFile), 1);
	    fclose(newFile);
	  } 
	}
	
	/* Parse graph file or die */
	if((parse(szMakefile)) == -1) 
	{
	  printf("Parsing Failed \n");
		return EXIT_FAILURE;
	}

	//after parsing the file, you'll want to check all dependencies (whether they are available targets or files)
	//then execute all of the targets that were specified on the command line, along with their dependencies, etc.
	//check if exists
	target_t *Target = find(szTarget);
	if(!Target){
	  fprintf(stderr, "Target doesn't exist \n");
	  return EXIT_FAILURE;
	}
 
	//check for dependencies
	printf("checking for dependingcies in target \n");
	
	if(checkDep(Target)){
	  execute(Target);
	}else{
	  printf("target not built: error in dependencies: Execution not succesful  \n");
	  return EXIT_FAILURE;
	}
        printf("target executed succefully\n");
	return EXIT_SUCCESS;
}
