#include <stdio.h>
#include <assert.h>

int main()
{
        int k, answer;
        int i = 1;
        int sum = 0;
        int check = scanf("%d", &k);
        assert(check == 1);
while (i <= k)
{
        check = scanf("%d", &answer);
        assert(check == 1);
        answer  = (i % 2) * answer*answer;
        sum = sum + answer;
        i++;
}
        printf("%d\n", sum);
        return 0;
}