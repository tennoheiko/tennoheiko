#include <stdio.h>
#include <stdlib.h>

void quickSort(int *arr, int a, int b, int n, FILE *file) 
{
    int i;
    if (a < b)
    {
        int left = a, right = b, middle = arr[(left + right) / 2];
        do
        {
            while (arr[left] < middle) left++;
            while (arr[right] > middle) right--;
            if (left <= right)
            {
	       	for (i=0; i<n; i++)
	            fprintf(file, "%d ", arr[i]);
	            fprintf(file, "\n");
	            int tmp = arr[left];
                arr[left] = arr[right];
                arr[right] = tmp;
                left++;
                right--;
            }
        } 
        while (left <= right);
	    quickSort(arr, a, right, n, file);
        quickSort(arr, left, b, n, file);
    }
}

void Swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void siftDown(int arr[], int root, int bottom) 
{
	int maxChild;
	int done = 0;
	while ((root * 2 <= bottom) && (!done))
	{
		if (root * 2 == bottom)
		{
			maxChild = root * 2;
		}
		else if (arr[root * 2] > arr[root * 2 + 1])
		{
			maxChild = root * 2;
		}
		else
		{
			maxChild = root * 2 + 1;
		}
		if (arr[root] < arr[maxChild])
		{
			Swap(&arr[root], &arr[maxChild]);
			root = maxChild;
		}
		else
		{
			done = 1;
		}
	}
}

void heapSort(int* arr, int arr_size, FILE *file) 
{
	for (int i = (arr_size / 2) - 1; i >= 0; i--) 
	{
		for (int j=0; j<arr_size; j++)
        		fprintf(file, "%d ", arr[j]);
		fprintf(file, "\n");
		siftDown(arr, i, arr_size - 1);
	}
	for (int i = arr_size - 1; i >= 1; i--) 
	{
		for (int j=0; j<arr_size; j++)
           		fprintf(file, "%d ", arr[j]);
       		fprintf(file, "\n");
		Swap(&arr[0], &arr[i]);
		siftDown(arr, 0, i - 1);
	}
}


int main ()
{
	int i, n, b;
        scanf("%d", &n);
	int *a = (int*)malloc(n*sizeof(int));
	int *c = (int*)malloc(n*sizeof(int));
        for (i=0; i<n; i++) {
                scanf("%d", &b);
                a[i]=b;
        	c[i]=b;
	}
        FILE *file;
        file = fopen("quicksort.log", "w");
	quickSort(a, 0, n-1, n, file);
        fclose(file);
        FILE *file2;
        file2 = fopen("heapsort.log", "w");
	heapSort(c, n, file2);
        fclose(file2);
	printf("\n");
        for (i=0; i<n; i++)
                printf("%d ", c[i]);
	return 0;
}
