#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Starting interactive test. Yielding CPU periodically...\n");
    
    while(1) {
        /* Simulate light activity and voluntary yield */
        for(int i = 0; i < 1000000; i++); 
        usleep(500000); /* Suspends process to avoid quantum exhaustion */
    }
    
    return 0;
}