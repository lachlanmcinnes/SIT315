#include <iostream>   
#include <cstdlib>  
#include <pthread.h>  
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;
  
const int MaxData = 20;
const int ThreadCount = 2;
int data[MaxData];
pthread_t threads[ThreadCount];
int threadIndex = 0;
int region[ThreadCount][2];
pthread_mutex_t threadMutex;
  
int GetThreadNumber()
{
    if(threadIndex >= ThreadCount)
        return -1;
    int threadNumber;
    pthread_mutex_lock(&threadMutex);
    if(threadIndex < ThreadCount)
        threadNumber = threadIndex ++;
    else
        threadNumber = -1;
    pthread_mutex_unlock(&threadMutex);
    return threadNumber;
}  

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

void QuickSort(int begin, int end);
void* QuickSort_Procedure(void *data)
{
    QuickSort(((int*)data)[0], ((int*)data)[1]);
    return 0;
}  
  
void QuickSort(int begin, int end)
{
    int middle, i = begin, j = end;

    do{
        middle = data[end];
        while(data[i] < middle) i++;
        while(data[j] > middle) j--;
        if(i <= j)
            swap(&data[i++], &data[j--]);
    }while(i < j);
    
    if(begin < j){
        int idx = GetThreadNumber();
        if(idx != -1){
            region[idx][0] = begin, region[idx][1] = j;
            pthread_create(&threads[idx], 0, QuickSort_Procedure, region[idx]);
        }else{
            QuickSort(begin, j);
        }
    }
    if(i < end)
        QuickSort(i, end);
}

void printArray(int arr[], int size){
    int z;
    for (z = 0; z < size; z++){
        cout << arr[z] << endl;
    }
}
  
int main(int argc, char **argv)
{

    srand(time(NULL));

    pthread_mutex_init(&threadMutex, NULL);

    for(int i=0; i<MaxData; i++){
        data[i] = rand()%100+1;
    }

    int n = sizeof(data)/sizeof(data[0]);

    cout << "Unsorted Array:" << endl;
    printArray(data,n);

    auto start = high_resolution_clock::now();

    QuickSort(0, MaxData-1);  
    /* Wait for 2 threads to end */  
    for(int i=0; i<ThreadCount; i++){ 
        pthread_join(threads[i], 0);  
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start); 

    cout << "Sorted Array:" << endl;
    printArray(data,n);

    cout << "\nDuration is :" << duration.count() << "microseconds\n";

    pthread_mutex_destroy(&threadMutex);  
    return 0;  
}  