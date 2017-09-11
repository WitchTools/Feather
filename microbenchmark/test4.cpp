// Basic R-W /W-R false sharing test
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


/* We expect samples at A.x to be reporting R-W false sharing and samples at A.y to be reporting  W-R false sharing */

void Work(int me){
    volatile int dummy = 0;
    for(long i = 0; i < N; i++) {
        if ((me & 1) == 0)
LBL1:			A.x = 1; // MUST be involved in  R-W false sharing
        else
LBL2:			dummy += A.y; // MUST be involved W-R false sharing
    }
}

int main(){
    thread threadObj1([]{Work(0);});
    thread threadObj2([]{Work(1);});
    threadObj1.join();
    threadObj2.join();
    cout<<"Test should find accesses to A.x at LBL1 to be involved in R-W false shairng and accesses to A.y at LBL2 to be involved in W-R false sharing\n";
    return 0;
}
