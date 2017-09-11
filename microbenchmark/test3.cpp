// Basic R-W false sharing test
#include<atomic>
#include<iostream>
#include<thread>
#define N (1L << 28)
#define CACHE_LINE_SIZE (64)
using namespace std;

struct alignas(CACHE_LINE_SIZE) {
    atomic<int> x;
    atomic<int> y;
} A;


/* We expect samples to be reporting R-W or W-R false sharing */

void Work(int me){
    for(long i = 0; i < N; i++) {
        if ((me & 1) == 0)
            A.x += 1; // MUST be involved in R-W or W-R false sharing
        else
            A.y += 1; // MUST be involved in R-W or W-R false sharing
    }
}

int main(){
    thread threadObj1([]{Work(0);});
    thread threadObj2([]{Work(1);});
    threadObj1.join();
    threadObj2.join();
    cout<<"Test should find its samples involved in R-W or R-W false sharing\n";
    return 0;
}
