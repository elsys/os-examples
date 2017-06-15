#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_THREADS 3
#define NUMBER_OF_INCREMENTS 5
#define VARIABLE_LIMIT 8
#define WATCH_INCREMENT 1000

int global_variable_count = 0;

pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cv;

void* IncrementVariable(void *id)
{
    int i;
    int threadID = (int)id;
    
    printf("Starting IncrementVariable(): thread %d\n", threadID);
    
    for (i=0; i < NUMBER_OF_INCREMENTS; i++) {
        pthread_mutex_lock(&count_mutex);
        global_variable_count++;
        if (global_variable_count == VARIABLE_LIMIT)
        {
            pthread_cond_signal(&count_threshold_cv);
            printf("IncrementVariable(): thread %d, count = %d  Limit reached.\n", threadID, global_variable_count);
        }
        printf("IncrementVariable(): thread %d, incrementing count, count = %d, unlocking mutex\n", threadID, global_variable_count);
        pthread_mutex_unlock(&count_mutex);
        
        sleep(1);
    }
    pthread_exit(NULL);
}

void* WatchVariable(void *id)
{
    int threadID = (int)id;
    
    printf("Starting WatchVariable(): thread %d\n", threadID);
    
    pthread_mutex_lock(&count_mutex);
    while (global_variable_count < VARIABLE_LIMIT) {
        pthread_cond_wait(&count_threshold_cv, &count_mutex);
        printf("WatchVariable(): thread %d Condition signal received.\n", threadID);
        global_variable_count += WATCH_INCREMENT;
        printf("WatchVariable(): thread %d count now = %d.\n", threadID, global_variable_count);
    }
    pthread_mutex_unlock(&count_mutex);
    pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
    int i;
    pthread_t threads[NUM_OF_THREADS];
    
    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init (&count_threshold_cv, NULL);

    pthread_attr_init(&attr);
    
    pthread_create(&threads[0], &attr, WatchVariable,     (void *)1);
    pthread_create(&threads[1], &attr, IncrementVariable, (void *)2);
    pthread_create(&threads[2], &attr, IncrementVariable, (void *)3);
    
    for (i=0; i < NUM_OF_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf ("Done.\n");
    
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_threshold_cv);
    
    return 1;
}
