
#include<stdio.h>
#include<time.h>
#include <sys/time.h>
#include <unistd.h>
#include<iostream>
#include <stdlib.h>

#include<pthread.h>

using namespace std;

pthread_mutex_t mut1, mut2;

void* task1(void* args) {

    cout<<" in thread1";
    sleep(5);
    pthread_mutex_lock(&mut1);
    printf("thread1 locked mut1");
    sleep(5);
    /*
    pthread_mutex_lock(&mut2);
    printf("thread1 locked mut2");
    sleep(5);
    pthread_mutex_unlock(&mut2);
    printf("thread1 unlocked mut2");
    sleep(5);
    */
   pthread_mutex_unlock(&mut1);

    printf("thread1 unlocked mut1");


    return NULL;
} 

void* task2(void* args) {
    cout<<" in thread1";
    sleep(5);
    pthread_mutex_lock(&mut2);
    printf("thread2 locked mut2");
    sleep(5);
    /*pthread_mutex_lock(&mut1);
    printf("thread2 locked mut1");
    sleep(5);
    pthread_mutex_unlock(&mut1);

    printf("thread2 unlocked mut1");
    sleep(5);
    */
    pthread_mutex_unlock(&mut2);
    printf("thread2 unlocked mut2");
 
    return NULL;
} 




int main(int argc, char** argv) {
    printf("in main thread!\n");
    pthread_mutex_init(&mut1, NULL);
    pthread_mutex_init(&mut2, NULL);

    pthread_t th1, th2;
    printf("creating new threads!\n");

    pthread_create(&th1,  NULL, task1, NULL);
    printf(" threads #1 done\n");
    pthread_create(&th2,  NULL, task2, NULL);
     printf(" threads #2 done\n");
    printf("threads started");
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    
    return 0;
}