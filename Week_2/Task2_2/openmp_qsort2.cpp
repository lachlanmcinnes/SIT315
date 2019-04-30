#include <iostream>   
#include <cstdlib>  
#include <pthread.h>  
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;
  
const int MaxData = 20;
int arr[MaxData];

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high){
    int pivot = arr[high];
    int i = (low-1);

    for (int j = low; j<=high-1; j++){
        if (arr[j] <= pivot){
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1], &arr[high]);
    return(i+1);
}

void QuickSort(int arr[], int low, int high){

    int j;

    if (low < high){
        int j = partition(arr, low, high);

        #pragma omp task shared(arr) firstprivate(low,j)
        {
            QuickSort(arr,low,j-1);
        }
        #pragma omp task shared(arr) firstprivate(high,j)
        {
            QuickSort(arr,j+1,high);
        }


    }
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

    for(int i=0; i<MaxData; i++){
        arr[i] = rand()%100+1;
    }

    int n = sizeof(arr)/sizeof(arr[0]);

    cout << "Unsorted Array:" << endl;
    printArray(arr,n);

    auto start = high_resolution_clock::now();

    QuickSort(arr,0,MaxData-1);
    /* Wait for 2 threads to end */  

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start); 

    cout << "Sorted Array:" << endl;
    printArray(arr,n);

    cout << "\nDuration is :" << duration.count() << "microseconds\n";

    return 0;  
}  