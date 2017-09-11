// Basic Write-Write false sharing test
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


/* We expects samples to be reporting W-W false sharing */

void Work(int me){
    for(long i = 0; i < N; i++) {
        if ((me & 1) == 0)
            A.x = 1; // W-W false share with A.y
        else
            A.y = 1; // W-W false share with A.x
    }
}

int main(){
    thread threadObj1([]{Work(0);});
    thread threadObj2([]{Work(1);});
    threadObj1.join();
    threadObj2.join();
    cout<<" Test should find samples to be involved in W-W false sharing\n";
    return 0;
}
