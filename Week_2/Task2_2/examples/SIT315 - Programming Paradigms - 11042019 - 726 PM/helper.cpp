
#include<stdio.h>
#include<time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <thread>

using namespace std;

int main(int argc, char** argv) {

     int cores = std::thread::hardware_concurrency();
     printf(" Number of cores on this machine = %d\n", cores);

    int sleep_interval = 0;
    for(int i = 0; i < argc ; i++) {
        printf(" arg[%d] = %s \n", i, argv[i]);
    }
    
    if(argc < 2) sleep_interval = 3;
    else sleep_interval = atoi(argv[1]);


    double time_elapsed = 0.0;
    //measuring time -- using clock
    long clock_start = clock();
    sleep(sleep_interval);
    long clock_end = clock();
    time_elapsed = (clock_end - clock_start) / CLOCKS_PER_SEC;

    printf("%.2f\n", time_elapsed);

    //measuring time using system time
    struct timeval timecheck;
    gettimeofday(&timecheck, NULL);
    long timeofday_start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
    sleep(sleep_interval);
    gettimeofday(&timecheck, NULL);
    long timeofday_end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
    
    time_elapsed = timeofday_end - timeofday_start;
    printf("%.2f\n", time_elapsed);

    //using time library
    time_t t_start = time(NULL);
    sleep(sleep_interval);
    time_t t_end = time(NULL);
    time_elapsed = t_end - t_start;
    printf("%.2f\n", time_elapsed);


    
}