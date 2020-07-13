#include <stdio.h>
#define N 18
#define DENOM 7
extern void mod_sort( unsigned long int arr[], int n, unsigned long int denom,  int count_arr[],int pos_arr[], unsigned long int mod_sorted[]);
extern void mod_count( unsigned long int arr[], int n, unsigned long int denom,  int count_arr[]);

int main()
{
 unsigned long int arr1[N] = {10, 20, 30, 40, 50, 60, 70, 
    				80, 90, 100, 110, 120, 130, 140,
    				150, 160, 170, 180};
 unsigned long int arr2[N]; 
 int count_arr[DENOM];
 int pos_arr[DENOM];
 unsigned long int denom = DENOM;
 int i, j;

 printf("arr1:\n");

 mod_count(arr1, N, denom,  count_arr);

 mod_sort(arr1, N, denom,  count_arr, pos_arr, arr2);

 for(i=0; i < N; i++)
   printf("%lu %% %lu = %lu\n", arr1[i], denom, arr1[i] % denom);

 for(i=0; i < denom; i++)
   printf("count_arr[%d] = %d\n", i, count_arr[i]);

 printf("arr1:\n");
 for(i=0; i < N; i++)
   printf("%lu %% %lu = %lu\n", arr2[i], denom, arr2[i] % denom);


} // main
