#include "a1.h"
#include <stdio.h>
#include <semaphore.h>
// #include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

FILE *fp;
sem_t sem_name;

//thread function
void thread_runner(void * ptr)
{
    int x;
    x = *((int *) ptr); //cast thread's id

    int i=0;
    for(i=0; i<10; i++) //loop 10 times per assignment requirements
    {
        fprintf(stderr, "thread id=%d - iteration %d\n", x, i);
        
		sem_wait(&sem_name); //decrement semaphore

        char thread_id[15];
        sprintf(thread_id, "%d\n", x);

		//open up file to write thread ID
        fp= fopen("PROCTAB.txt", "a");
        if (fp!=NULL)
        {
            fputs (thread_id,fp);
            fclose (fp);
        }

        sem_post(&sem_name); //increment semaphore

        sleep(1); //sleep 1 sec. per assign. requirements
    }


    pthread_exit(0); /* exit thread */
}


int main (int argc, char const *argv[])
{
    pid_t childPID;

    int pid = getpid();
    char str[15];
    sprintf(str, "%d", pid);

	//create child process
    childPID = fork();

    if(childPID >= 0) // fork was successful
    {
        if(childPID == 0) // child process
        {
            fprintf(stderr, "child (forked) pid=%d\n", getpid());

			//routine to get pid as string
            char cpid_s[15];
            sprintf(cpid_s, "%d", getpid());

            //create file and write PID
            fp= fopen("PROCTAB.txt", "w+");
            if (fp!=NULL)
            {
                fputs (cpid_s,fp); 
                fclose (fp);
            }

            //init semaphore
            sem_init(&sem_name, 0, 10);

			//create ids for threads
            int i[10];
            i[0]=0;
            i[1]=1;
            i[2]=2;
            i[3]=3;
            i[4]=4;
            i[5]=5;
            i[6]=6;
            i[7]=7;
            i[8]=8;
            i[9]=9;

			//create 10 threads
            pthread_t thread_1;
            pthread_t thread_2;
            pthread_t thread_3;
            pthread_t thread_4;
            pthread_t thread_5;
            pthread_t thread_6;
            pthread_t thread_7;
            pthread_t thread_8;
            pthread_t thread_9;
            pthread_t thread_10;
            pthread_create (&thread_1, NULL, (void *) &thread_runner, (void *) &i[0]);
            pthread_create (&thread_2, NULL, (void *) &thread_runner, (void *) &i[1]);
            pthread_create (&thread_3, NULL, (void *) &thread_runner, (void *) &i[2]);
            pthread_create (&thread_4, NULL, (void *) &thread_runner, (void *) &i[3]);
            pthread_create (&thread_5, NULL, (void *) &thread_runner, (void *) &i[4]);
            pthread_create (&thread_6, NULL, (void *) &thread_runner, (void *) &i[5]);
            pthread_create (&thread_7, NULL, (void *) &thread_runner, (void *) &i[6]);
            pthread_create (&thread_8, NULL, (void *) &thread_runner, (void *) &i[7]);
            pthread_create (&thread_9, NULL, (void *) &thread_runner, (void *) &i[8]);
            pthread_create (&thread_10, NULL, (void *) &thread_runner, (void *) &i[9]);


			//wait for threads to finish
            pthread_join(thread_1, NULL);
            pthread_join(thread_2, NULL);
            pthread_join(thread_3, NULL);
            pthread_join(thread_4, NULL);
            pthread_join(thread_5, NULL);
            pthread_join(thread_6, NULL);
            pthread_join(thread_7, NULL);
            pthread_join(thread_8, NULL);
            pthread_join(thread_9, NULL);
            pthread_join(thread_10, NULL);


            sem_destroy(&sem_name); /* destroy semaphore */

            fprintf(stderr, "end child\n\n");
        }
        else //Parent process
        {
            fprintf(stderr, "parent pid=%d\n", pid);
        }
    }
    else // fork failed
    {
        fprintf(stderr, "\n Fork failed, quitting!!!!!!\n");
        return 1;
    }


    fprintf(stderr, "end parent\n");
    return 0;
}

