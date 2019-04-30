#include <stdio.h>
#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

int quickSort(int arr[], int low, int high)  
{  
    int l = low;
    int h = high;
    int pivot = arr[high];

    do{  
        while(arr[l]<pivot) ++l;  
        while(arr[h]>pivot) --h;  
        if(l<=h) swap(arr[l++], arr[h--]);  
    }while(l<h);  
    if(low<h) quickSort(arr, low, h);  
    if(l<high) quickSort(arr, l, high);  
}

void printArray(int arr[], int size){
    int i;
    for (i = 0; i < size; i++){
        cout << arr[i] << endl;
    }
}

int main() {

    cout << "Hello World!" << "\n";

    int Num = 20;
    int arr[Num];

    srand(time(NULL));

    for (int i = 0; i<Num; i++){
        arr[i] = rand()%100+1;
    }
    
    int n = sizeof(arr)/sizeof(arr[0]);

    cout << "Unsorted Array:" << endl;
    printArray(arr,n);

    auto start = high_resolution_clock::now();

    quickSort(arr, 0, n-1);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start); 

    cout << "Sorted Array:" << endl;
    printArray(arr,n);

    cout << "\nDuration is :" << duration.count() << "microseconds\n";

    return 0;
}