#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <pthread.h>

using namespace std;
using namespace std::chrono;

#define N 10
#define MAX_THREAD 4

int a[N][N];
int b[N][N];
int c[N][N];
int step_i = 0;

void* multi(void *arg){
    int core = step_i++;

    for (int i = core*N/MAX_THREAD; i<(core + 1)*N/MAX_THREAD;i++){
        for (int j = 0; j< N; j++){
            for (int k = 0;k<N;k++){
                c[i][j] += a[i][k]*b[k][j];
            }
        }
    }

    return 0;
}

int main() {

    cout << "Hello World!" << "\n";

    int i,j;

    srand(time(NULL));

    cout << "Creating matrix A:" << endl;
    for (i = 0; i<N; i++ ){
        
        for (j=0;j<N;j++){
            a[i][j] = rand()%10+1;
            //cout << a[i][j] << "\t";
        }
        //cout << endl;
    }

    cout << "Creating matrix B:" << endl;
    for (i = 0; i<N; i++ ){
        
        for (j=0;j<N;j++){
            b[i][j] = rand()%10+1;
            //cout << b[i][j] << "\t";
        }
        //cout << endl;
    }

    pthread_t threads[MAX_THREAD];

    auto start = high_resolution_clock::now();

    for (i=0;i<MAX_THREAD;i++){
        int* p;
        pthread_create(&threads[i],NULL,multi,(void*)(p));
    }

    for(i=0;i<MAX_THREAD;i++){
        pthread_join(threads[i],NULL);
    }

    auto stop = high_resolution_clock::now();

    /*
    cout << endl << "Multiplication of the 2 random matrix:" << endl;
    for (i=0;i<N;i++){
        for (j=0;j<N;j++){
            cout << c[i][j] << "\t";
        }
        cout << endl;
    }
    */

    auto duration = duration_cast<microseconds>(stop - start); 

    cout << "\nDuration is :" << duration.count() << "microseconds\n";

    return 0;

}