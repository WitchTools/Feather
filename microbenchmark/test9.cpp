// Insignificant amount of false sharing
#include<atomic>
#include<iostream>
#include<thread>
#include<pthread.h>

#define N (1L << 28)
#define CACHE_LINE_SIZE (64)
#define NUM_THREADS (2)
using namespace std;

struct alignas(CACHE_LINE_SIZE) {
    atomic<int> x;
    atomic<int> y;
} A;
struct alignas(CACHE_LINE_SIZE) {
    atomic<int> x;
    atomic<int> y;
} B;
struct alignas(CACHE_LINE_SIZE) {
    atomic<int> x;
    atomic<int> y;
} C;


pthread_barrier_t barrier;

// Accesses are separated by a barrier hence although there is false sharing
// it should be insignificant compared to the total number of samples taken in execution.

void Work(int me){
    for(long i = 0; i < N; i++) {
        if ((me & 1) == 0) {
            A.x = 1;
        } else {
            B.y = 1;
        }
    }
    pthread_barrier_wait(&barrier);
    for(long i = 0; i < N; i++) {
        if ((me & 1) == 0) {
            B.x = 1;
        } else {
            C.y = 1;
        }
    }
    pthread_barrier_wait(&barrier);
    for(long i = 0; i < N; i++) {
        if ((me & 1) == 0) {
            C.x = 1;
        } else {
            A.y = 1;
        }
    }
}

int main(){
    pthread_barrier_init(&barrier, 0, NUM_THREADS);
    thread threadObj1([]{Work(0);});
    thread threadObj2([]{Work(1);});
    threadObj1.join();
    threadObj2.join();
    pthread_barrier_destroy(&barrier);
    cout<<"Test might detect false sharing among pair A.x:A.y, B.x:B.y, and C.x:C.y, but the amount of false sharing must be insignificant compared to the number of samples taken\n";
    return 0;
}
