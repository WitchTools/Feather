// True sharing NOT a false sharing test
#include<atomic>
#include<iostream>
#include<thread>
#define N (1L << 28)
#define CACHE_LINE_SIZE (64)
using namespace std;

struct alignas(CACHE_LINE_SIZE) {
    atomic<int> x;
} A;


/* There is contention (true sharing) but no false sharing */

void Work(int me){
    for(long i = 0; i < N; i++) {
        A.x ++; // Atomic Add: true sharing but not a false sharing
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
