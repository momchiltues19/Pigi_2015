#include <stdio.h>
#include <stdlib.h>

int main()
{
int n, c, i, m;
    do
    {
        printf("\n Input positive n:");
        scanf("%d", &n);
    } while (n<=0);
    c=0;
    i=2;
    do
    {
        if (n%i==0)
        {
            m=2;
            while (i%m!=0) m=m+1;
            if (i==m)
            {
                printf("\n %d is a prime divider", i);
                c=c+1;
            }
        }
        i=i+1;
    } while (i<=n);

    printf("\n the count of prime dividers is %d", c);
}
