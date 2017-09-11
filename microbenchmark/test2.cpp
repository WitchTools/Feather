// Basic no false sharing test
#include<atomic>
#include<iostream>
#include<thread>
#define N (1L << 32)
#define CACHE_LINE_SIZE (64)
using namespace std;

struct alignas(CACHE_LINE_SIZE) {
    atomic<int> x;
    atomic<int> y;
} A;


/* We expect no false sharing */

void Work(int me){
    volatile int dummy = 0;
    for(long i = 0; i < N; i++) {
        if ((me & 1) == 0)
            dummy += A.x; // MUST NOT be any false sharing
        else
            dummy += A.y; // MUST NOT be any false sharing
    }
}

int main(){
    thread threadObj1([]{Work(0);});
    thread threadObj2([]{Work(1);});
    threadObj1.join();
    threadObj2.join();
    cout<<"Test should find no false sharing at all\n";
    return 0;
}
