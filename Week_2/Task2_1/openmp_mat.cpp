#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
//#include <omp.h>

using namespace std;
using namespace std::chrono;

#define N 1000
#define MAX_THREAD 2

int a[N][N];
int b[N][N];
int c[N][N];

int main(){

    cout << "Helo World!" << endl;

    int i,j,k;

    srand(time(NULL));

    cout << "Creating matrix A:" << endl;
    for (i = 0; i<N; i++ ){
        for (j=0;j<N;j++){
            a[i][j] = rand()%10+1;
            //cout << a[i][j] << "\t";
        }
        //cout << endl;
    }

    cout << endl;

    cout << "Creating matrix B:" << endl;
    for (i = 0; i<N; i++ ){
        for (j=0;j<N;j++){
            b[i][j] = rand()%10+1;
            //cout << b[i][j] << "\t";
        }
        //cout << endl;
    }

    cout << endl;

    auto start = high_resolution_clock::now();

    #pragma omp parallel shared(a,b,c) private(i,j,k)
    {
        #pragma omp for schedule(static)

        for (i=0;i<N;i++){
            for (j=0;j<N;j++){
                for(k=0;k<N;k++){
                    c[i][j] += a[i][k]*b[k][j];
                }
            }
        }
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start); 

    /*
    int x,y;

    for(x=0;x<N;x++){
        for(y=0;y<N;y++){
            cout<<"\t"<<c[x][y];
        }
        cout<<"\n";
    }
    */

    cout << "\nDuration is :" << duration.count() << "microseconds\n";

    return 0;
}