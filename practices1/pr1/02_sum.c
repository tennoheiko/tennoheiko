#include <stdio.h>
#include <assert.h>

int main()
{
         double x,y;
         int t = scanf("%lf%lf",&x,&y);
         assert (t == 2 );
         printf("%lf\n",x+y);
         return 0;
}
