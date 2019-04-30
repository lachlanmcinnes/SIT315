#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stddef.h>
#include <mpi.h>
#include <ctime>
#include <chrono>

#define N 4

using namespace std;
using namespace std::chrono;

void print_results(int a[N][N]);

int main(int argc, char *argv[]){
    int i,j,k;
    int rank,size;
    int tag = 99;
    int blksz;
    int sum = 0;

    int a[N][N] = {{1,2,3,4},{5,6,7,8},{9,1,2,3},{4,5,6,7}};
    int b[N][N] = {{1,2,3,4},{5,6,7,8},{9,1,2,3},{4,5,6,7}};
    int c[N][N];
    int aa[N], cc[N];

    auto start = high_resolution_clock::now();

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Scatter(a, N*N/size, MPI_INT, a, N*N/size, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Bcast(b, N*N, MPI_INT, 0, MPI_COMM_WORLD);

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

    MPI_Gather(c, N*N/size, MPI_INT, c, N*N/size, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Finalize();

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start); 

    if (rank == 0){
        print_results(c);
        cout << "Execution time = " << duration.count() << " microseconds\n";
    }

}

void print_results(int a[N][N]){
    int i,j;

    for (i=0; i<N; i++){
        for (j=0; j<N; j++){
            cout << "\t" << a[i][j];
        }
        cout << "\n";
    }
}

