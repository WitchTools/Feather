// Array not involved in any false sharing
#include<atomic>
#include<iostream>
#include<thread>
#define N (1L << 28)
#define CACHE_LINE_SIZE (64)
using namespace std;

struct alignas(CACHE_LINE_SIZE) {
    atomic<int> x[CACHE_LINE_SIZE/sizeof(int)];
    atomic<int> y[CACHE_LINE_SIZE/sizeof(int)];
} A;

// No false sharing at all.
void Work(int me){
    for(long i = 0; i < N; i++) {
        if ((me & 1) == 0) {
            for(int j = 0 ; j < CACHE_LINE_SIZE/sizeof(int); j++)
                A.x[j] = 1; // MUST not be involved in false sharing
        } else {
            for(int j = 0 ; j < CACHE_LINE_SIZE/sizeof(int); j++)
                A.y[j] = 1; // MUST not be involved in false sharing
        }
    }
}

int main(){
    thread threadObj1([]{Work(0);});
    thread threadObj2([]{Work(1);});
    threadObj1.join();
    threadObj2.join();
    cout<<"Test should find no false sharing\n";
    return 0;
}
