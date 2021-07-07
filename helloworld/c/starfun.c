#include "starfun.h"
#include <stdio.h>
int star1()
{
    int i, j, k;
    for(k = 1; k <= NUM; ++k)
    {
        for(i=1; i <= (NUM-k); ++i)
        {
            printf(" ");
        }
        for(j = 1; j <= (2*k-1); ++j)
        {
	    printf("*");
	}
        printf("\n");
    }
    return 0;
}
int star2()
{
    int i, j, k;
    for(k = NUMBER; k >= 0; --k)
    {
        for(i=1; i <= (NUMBER-k+1); ++i)
        {
            printf(" ");
        }
        for(j = 1; j <= (2*k-1); ++j)
        {
	    printf("*");
	}
        printf("\n");
    }
    return 0;
}


