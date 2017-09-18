#include "stdio.h"
#include "stdlib.h"

#include "time.h"


int main(void)
{
    int a[16 * 16];
    int i;

    clock_t start = clock();

    for(i = 0; i < 16 * 16; i++)
    {
	a[i] = i * i;
    }

    clock_t end = clock();
    double runtime = (double)(end - start)/(double)CLOCKS_PER_SEC;

    printf("run time = %f\n", runtime);

    return 0;

}