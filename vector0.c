# include <stdio.h>
# include <stdlib.h>
#include <time.h>


int main(int argc, char **argv)
{
    int i, n=10;
    double v1[10], v2[10];

    for(i=0; i<n; i++){
        v1[i] = (double)(i+1);
        v2[i] = 0.0;
    }

    #pragma acc kernels
    for(i=0; i<n; i++){
        v2[i] = v1[i] * 2.0;
    }
    for(i=0; i<n; i++){ printf(" %.2f", v1[i]); }
    printf("\n");
    for(i=0; i<n; i++){ printf(" %.2f", v2[i]); }
    printf("\n");

    return 0;
}