// CSci4061 S2016 Assignment 4

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "util.h"

// need these too
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define MAX_THREADS 100
#define MAX_QUEUE_SIZE 100
#define MAX_REQUEST_LENGTH 1024

// Initialize the basics
int buffCount = 0;
pthread_mutex_t buffLock;
pthread_mutex_t logLock;
pthread_mutex_t workerIDLock;
pthread_mutex_t dispatcherIDLock;
pthread_cond_t buffEmpty;
pthread_cond_t buffFull;

// Log file
FILE *logfile;
pthread_mutex_t logFileLock;

int dispatchersMade = 0;
int workersMade = 0;
int bufferIn = 0;
int bufferOut = 0;
int queue_length = 0;
int num_dispatchers;
int num_workers;
pthread_t dispatchers[MAX_THREADS];

pthread_t workers[MAX_THREADS];

// signal action for SIGINT when user does ctrl-C to exit program.
struct sigaction int_action;
sigset_t set;

// structure for queue.
typedef struct request_queue
{
    int m_socket;
    char m_szRequest[MAX_REQUEST_LENGTH];
} request_queue_t;

// create buffer
request_queue_t *buffer;

void * dispatch(void * arg) // Producer. Use acceptConnection(), get_request(), queue request on buffer.
{
    // lock critical section to keep track of threads by dispatcher. worker function should do the same. 
    int threadID;
    pthread_mutex_lock(&dispatcherIDLock);
        threadID = dispatchersMade;
        dispatchersMade++;
    pthread_mutex_unlock(&dispatcherIDLock);

    while(1)
    {
        request_queue_t req;
        req.m_socket = accept_connection();
        if(req.m_socket >= 0)
        {
printf("[D %d][%d] Is incoming request is on socket.\n",threadID, req.m_socket);
            if(get_request(req.m_socket, req.m_szRequest) != 0) // (fd, filename)
            {
                return_error(req.m_socket, "Get request failed");
                continue;
            }
            pthread_mutex_lock(&buffLock);
            while (buffCount==queue_length)
                pthread_cond_wait(&buffFull, &buffLock); // (condition, mutex)
            //buffer[bufferIn].m_socket=req.m_socket;
            memcpy(&(buffer[bufferIn]), (void *) &req, sizeof(request_queue_t));
            bufferIn = (bufferIn + 1) % queue_length;
            buffCount++;
            printf("[D %d][%d] Write request buffer slot %d, buffCount = %d\n",threadID,req.m_socket,bufferIn, buffCount);
            // signal worker because now it has a request from dispatcher. 
            pthread_cond_signal(&buffEmpty);
            pthread_mutex_unlock(&buffLock);
        }
    }
}


void * worker(void * arg) // Consumer
{
    //lock critial section: worker threads. just like dispatcher did.
    int threadID;
    pthread_mutex_lock(&workerIDLock);
        threadID = workersMade;
        workersMade++;
    pthread_mutex_unlock(&workerIDLock);
    int totalRequests = 0;

    while(1)
    {
        request_queue_t req;

        //lock to access queue. use CV. 
        pthread_mutex_lock(&buffLock);
        while (buffCount==0)
            pthread_cond_wait(&buffEmpty, &buffLock); //wait if buffer empty for signal

        //fetch element
        memcpy(&req,(void *) &(buffer[bufferOut]), sizeof(request_queue_t));
        bufferOut = (bufferOut + 1) % queue_length;
        buffCount--; // because worker has taken care of it

        //increment
        totalRequests++;

        //unlock it
        pthread_cond_signal(&buffFull); //wake up the dispatcher thread waiting for buffer to be empty
        pthread_mutex_unlock(&buffLock);

        //get file size in bytes
        struct stat statbuf;
        stat(req.m_szRequest+1, &statbuf);
        int file_size = statbuf.st_size;
        // TODO read requested file content into a buffer using fread(). must allocate space.
        // Q: should i be using this buffer somewhere..? is it the same buffer as "struct stat buf"?
        char *buf = (char *) malloc(file_size * sizeof (char));
        FILE *fp = fopen(req.m_szRequest + 1, "r");
        if (fp == NULL) {
                pthread_mutex_lock(&logFileLock);
                writetoLog(threadID,totalRequests,req.m_socket,req.m_szRequest,0, "File not found.");
                pthread_mutex_unlock(&logFileLock);
                if (return_error(req.m_socket, "File not found") != 0)
                {
                        printf("Couldn't return error, thread id=%d\n",threadID);
                }
                continue;
        }
        fread(buf, file_size, 1, fp); // should i fopen() m_szRequest ? 
        fclose(fp);
//get content type
        char content_type[24];
        char *ext = strtok(req.m_szRequest, ".");
        ext = strtok(NULL, ".");
        //strcpy(content_type, req.m_szRequest+(((int) strlen(req.m_szRequest)) -4)); //get last four chars in filepath
        if(strcmp(content_type,".htm") == 0 || strcmp(content_type,"html") == 0)
            strcpy(content_type,"text/html");
        else if (strcmp(content_type,".jpg") == 0)
            strcpy(content_type,"image/jpeg");
        else if (strcmp(content_type,".gif") == 0)
            strcpy(content_type,"image/gif");
        else strcpy(content_type,"text/plain"); // default

        //logfile should print out records of all requests
        pthread_mutex_lock(&logFileLock);
            writetoLog(threadID,totalRequests,req.m_socket,req.m_szRequest,file_size, NULL);
        pthread_mutex_unlock(&logFileLock);

        // return_result or return_error
        if (return_result(req.m_socket, content_type, buf, file_size) != 0)
        {
            printf("Couldn't return result, thread id=%d\n",threadID);
        }
    }
    return NULL;
}

// print request info inside logfile
// TODO FIX WRITETOLOG PARAMS
void writetoLog(int threadID, int totalRequests, int m_socket, char * m_szRequest, int file_size, char * error)
{
    // [ThreadID#][Request#][fd][Request string][bytes/error]
    // Example: [6][1][5][/image/jpg/31.jpg][17772]
        if (error == NULL)
    fprintf(logfile, "[%d][%d][%d][%s][%d]\n", threadID, totalRequests, m_socket, m_szRequest, file_size);
        else
    fprintf(logfile, "[%d][%d][%d][%s][%s]\n", threadID, totalRequests, m_socket, m_szRequest, error);
// TODO flush log
fflush(logfile);
}

// When user types ctrl-C, program will clean up buffer and exit. 
void inthandler(int sig)
{
    printf("\nSignal handler is killing threads, freeing and exiting program.\n");
    int i;
    for (i = 0; i < num_dispatchers; i++)
    {
        if(pthread_cancel(dispatchers[i]) != 0) {
            printf("Dispatcher thread %d/%d was not killed\n", i+1, num_dispatchers );
        }
    }
    printf("dispatcher threads killed\n");
    for (i = 0; i < num_workers; i++)
    {
        if(pthread_cancel(workers[i]) != 0)
        {
            printf("Worker thread %d/%d was not killed\n", i+1, num_workers);
        }
    }
    printf("worker threads killed\n");
    free(buffer);
    pthread_cond_destroy(&buffEmpty);
    pthread_cond_destroy(&buffFull);
    pthread_mutex_destroy(&buffLock);
    pthread_mutex_destroy(&logLock);
    pthread_mutex_destroy(&workerIDLock);
    pthread_mutex_destroy(&dispatcherIDLock);
    printf("freed memory\n");
    printf("clean up complete\nand exiting\n");
    exit(0);
}

int main(int argc, char **argv)
{
    //Error check first.
    if(argc != 6 && argc != 7)
    {
        printf("usage: %s port path num_dispatcher num_workers queue_length [cache_size]\n", argv[0]);
        return -1;
    }

    printf("Call init() first and make a dispather and worker threads\n");

    int port = atoi(argv[1]); //atoi converts string to int
    char path[624]; // in case path is super long
    strcpy(path, argv[2]); // so path something like Project4/testing
    num_dispatchers = atoi(argv[3]);
    num_workers = atoi(argv[4]);
    queue_length = atoi(argv[5]);

    logfile = fopen("web_server_log","a+");

    // sig handler
    int_action.sa_handler = inthandler;
    sigaction(SIGINT,&int_action,NULL);

    // make a sigset to block SIGINT in the threads
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_SETMASK,&set,NULL);
     // establish route directory.
    if(chdir(path)==-1)
    {
        perror("failed to chdir to path. probably wrong file path entered.");
        printf("exit.\n");
        return 0;
    }

    init(port);

    // Commenting out until write mutex locks for worker(), or might error. 
    // if (error = pthread_mutex_init(&workerIDLock, NULL))
    //         fprintf(stderr, "Failed to initialize workerIDLock:%s\n", strerror(error)); 
    // if (error = pthread_mutex_init(&dispatcherIDLock, NULL))
    //         fprintf(stderr, "Failed to initialize dispatcherIDLock:%s\n", strerror(error));
    // if (error = pthread_mutex_init(&logLock, NULL))
    //         fprintf(stderr, "Failed to initialize logLock:%s\n", strerror(error));    
    // if (error = pthread_mutex_init(&buffLock, NULL))
    //         fprintf(stderr, "Failed to initialize buffLock:%s\n", strerror(error));
    // if (error = pthread_cond_init(&buffEmpty, NULL))
    //         fprintf(stderr, "Failed to initialize buffEmpty:%d %s\n", error, strerror(error));
    // if (error = pthread_cond_init(&buffFull, NULL))
    //         fprintf(stderr, "Failed to initialize buffFull:%s\n", strerror(error));

    // create buffer space
    buffer = (request_queue_t *)malloc(sizeof(request_queue_t)*queue_length);
    // spawn dispatcher threads in a loop
    pthread_t dispatcher_id[num_dispatchers];
    int i;
    for (i = 0; i < num_dispatchers; i++)
    {
        //pthread_t aThread = i;
        if (pthread_create(&dispatcher_id[i], NULL, dispatch,NULL) == -1)
        {
            printf("error when spawn dispatcher thread.\n");
            return -1;
        }
        //pthread_detach(aThread);
        //dispatchers[i] = aThread;
    }

    // spawn worker threads in a loop
    pthread_t worker_id[num_workers];
    for (i = 0; i < num_workers; i++)
    {
        pthread_t aThread = i;
        if (pthread_create(&worker_id[i], NULL, worker,NULL) == -1)
        {
            printf("error when spawn worker thread.\n");
            return -1;
        }
        //pthread_detach(aThread);
        //workers[i] = aThread;
    }

    printf("%d dispatcher threads and %d worker threads spawned. ctrl-c to quit.\n",num_dispatchers,num_workers);
    
    sigemptyset(&set); // clear SIGINT from signal set. 
    pthread_sigmask(SIG_SETMASK, &set, NULL);

    for (i = 0; i < num_dispatchers; i++)
    {
        pthread_join(dispatcher_id[i],NULL);
    }
    for (i = 0; i < num_workers; i++)
    {
        pthread_join(worker_id[i],NULL);
    }
    fclose(logfile);
    return 0;
}