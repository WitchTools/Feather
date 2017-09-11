// Proportion of false sharing
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
struct alignas(CACHE_LINE_SIZE) {
    atomic<int> x;
    atomic<int> y;
} B;
struct alignas(CACHE_LINE_SIZE) {
    atomic<int> x;
    atomic<int> y;
} C;

// 3:2:1 proportion of false sharing between A, B, and C variables.
void Work(int me){
    // iterate 3N  times
    for(long i = 0; i < 3 * N; i++) {
        if ((me & 1) == 0) {
            A.x = 1; // Must contribute to 3/6 of total W-W false sharing
        } else {
            A.y = 1; // Must contribute to 3/6 of total W-W false sharing
        }
    }
    // Iterate 2N times
    for(long i = 0; i < 2 * N; i++) {
        if ((me & 1) == 0) {
            B.x = 1; // Must contribute to 2/6 of total W-W false sharing
        } else {
            B.y = 1; // Must contribute to 2/6 of total W-W false sharing
        }
    }
    // Iterate N times
    for(long i = 0; i < N; i++) {
        if ((me & 1) == 0) {
            C.x = 1; // Must contribute to 1/6 of total W-W false sharing
        } else {
            C.y = 1; // Must contribute to 1/6 of total W-W false sharing
        }
    }
}

int main(){
    thread threadObj1([]{Work(0);});
    thread threadObj2([]{Work(1);});
    threadObj1.join();
    threadObj2.join();
    cout<<"Test should attribute 50% of false sharing to A.x:A.y pair, 33% false sharing to B.x:B.y pair and 17% false sharing to C.x:C.y pair\n";
    return 0;
}
