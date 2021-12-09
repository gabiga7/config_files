#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int *func(int a)
{
    int* array=malloc(sizeof(int)*SIZE);
    for(int i=0;i<SIZE;i++)
        array[i]=i*a;
    return array;
}


int main(void)
{
   int* tab1=malloc(sizeof(int)*SIZE);
   tab1=func(2);
   for(size_t i=0;i<SIZE;i++)
       printf("%d ",tab1[i]);
   printf("\n");
    return 1;
}


