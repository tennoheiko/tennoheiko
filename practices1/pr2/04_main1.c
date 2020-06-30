#include <stdio.h>
#include <assert.h>

int main()
{
        int n, answer;
        int i = 1;
        int sum = 0;
        int check = scanf("%d", &n);
        assert(check == 1);
while (i <= n)
{
       check = scanf("%d", &answer);
       assert(check == 1);
       sum = sum - answer;
       i++;
}
       printf("%d\n", sum);
       return 0;
} 