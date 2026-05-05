#include <stdio.h>
#include <unistd.h>

int main() {
    int i;
    printf("Starting Recovery Test. Phase 1: Aggressive (30s)\n");

    /* PHASE 1: Aggressive behavior. */
    for(i = 0; i < 30; i++) {
        unsigned long long j;
        for(j = 0; j < 500000000ULL; j++); 
        if (i % 10 == 0) printf("Phase 1: Being aggressive... (%ds/30s)\n", i);
    }

    printf("Phase 2: Starting to behave (Interactive) for 30s...\n");

    /* PHASE 2: Cooperative behavior. */
    for(i = 0; i < 60; i++) {
        usleep(500000); 
        if (i % 20 == 0) printf("Phase 2: Recovering... (%ds/60s)\n", i/2);
    }

    printf("Recovery test completed.\n");
    return 0;
}