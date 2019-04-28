#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {

    cout << "Hello World!" << "\n";

    int N = 1000;

    int a[N][N];
    int b[N][N];

    int i,j;

    srand(time(NULL));

    for (i = 0; i<N; i++ ){
        for (j=0;j<N;j++){
            a[i][j] = rand()%10+1;
            b[i][j] = rand()%10+1;
        }
    }

    int a_rows = sizeof(a)/sizeof(a[0]);
    int a_cols = sizeof(a[0])/sizeof(a[0][0]);

    int b_rows = sizeof(b)/sizeof(b[0]);
    int b_cols = sizeof(b[0])/sizeof(b[0][0]);

    if(a_cols == b_rows){
        cout << "Multiplication is possible" << "\n";

        int c[a_rows][b_cols];

        int x,y,z;

        auto start = high_resolution_clock::now();

        for (x=0; x<a_rows; x++) {
            for (y=0; y<b_cols; y++) {
                c[x][y] = 0;
                for (z=0; z<b_rows; z++) {
                    c[x][y] += a[x][z]*b[z][y];
                }
            }
        }

        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start); 

        /*
        for(x=0;x<a_rows;x++)
        {
            for(y=0;y<b_cols;y++)
            {
                cout<<"\t"<<c[x][y];
            }
            cout<<"\n";
        }
        */

        cout << "Execution time = " << duration.count() << " microseconds\n";

    }
    else{
        cout << "Multiplication not possible" << "\n";
    }

    return 0;
}