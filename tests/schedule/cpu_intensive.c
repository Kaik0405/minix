#include <stdio.h>
#include <unistd.h>

int main() {
    int i;
    printf("Starting CPU-intensive test. Duration: 60s.\n");

    /* Automatic exit after 60 seconds */
    for(i = 0; i < 60; i++) {
        unsigned long long j;
        /* Busy-wait loop to force quantum exhaustion */
        for(j = 0; j < 500000000ULL; j++); 
        
        if (i % 10 == 0) printf("CPU-intensive process running... (%ds/60s)\n", i);
    }

    printf("CPU-intensive test completed.\n");
    return 0;
}