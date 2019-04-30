#include<iostream>
#include <pthread.h>
#include<unistd.h>
#include <sys/time.h>

using namespace std;

#define MAX 10
#define THREADS 2
int data[MAX] = {10,10,10,10,10,10,10,10,10,10};
pthread_mutex_t multex1, mutex2;
void* say_hello(void* pars) {
    //sleep(rand()%10);
    std::string str = "params" +  std::to_string( ( (long)pars));
    
   
    cout<<str<<endl; 
 
    return NULL;
}

void* say_bye(void* pars) {
     //sleep(rand()%10);
     cout<<"bye bye from the slave thread!! \n"<<endl;

    return NULL;
}

int global_sum = 0;
void* sum(void* thread_id) {
     //sleep(rand()%10);
    long sum = 0;
    long id = (long)thread_id;
    int range = MAX/THREADS;
    int start = id*range;
    int end =   start + range;
    for(int i = start; i < end ; i++ ) {
        sum += data[i];
    }

    pthread_mutex_lock(&multex1);
    global_sum += sum;
   // cout<<"sum in thread = "<<sum<<" and global = "<<global_sum<<endl;
    pthread_mutex_unlock(&multex1);
    pthread_exit((void*)sum);
    
}

int main() {
    cout<<"Hello world from the master thread!! \n";
    
   

    srand(time(0));
    for(int i = 0; i < MAX; i++) {
        data[i] = rand()%10;
    }
    
    pthread_mutex_init(&multex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
   
    pthread_t threads[2];
    long thread_id = 0;
    pthread_create(&threads[0], NULL, sum, (void*) thread_id );
    thread_id = 1;
    pthread_create(&threads[1], NULL, sum, (void*)  thread_id);
    
     void* sum_temp ;
    long sum = 0;
    for(int th = 0; th < THREADS; th++) {
        sum_temp = 0;
        pthread_join(threads[th], &sum_temp);
        
        sum += (long)sum_temp;
        cout<<"sum joun ="<< sum<<" and temp = "<<(long)sum_temp<<endl;
    }

    for(int i = 0; i < MAX; i++) {
        cout<<data[i]<<" ";
    }
    cout<<"sumXXX ="<< sum<<endl;
    cout<<"global sum ="<< global_sum<<endl;
    return 0;
}