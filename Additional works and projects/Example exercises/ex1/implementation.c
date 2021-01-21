#include "Header.h"

/* checks if the sum of previous index values is equal to current value of index */
int Do_It(void *sum, void** array, void(*p_Init)(void *), void(*p_Sum)(void*, void*), void(*p_Sub)(void*, void*), int(*p_Comp)(void*, void*))
{
	int i;
	p_Init(sum);
	for (i = 0; i < N-1; i++)
	{
		if ((i % 2) == 0) /* if index is even*/
			p_Sum(sum, (array[i]));
		else /* index is odd*/
			p_Sub(sum, (array[i]));
		if (p_Comp(sum, (array[i + 1])))/* if the sum of previous numbers is equal to current number */
			return 1;
	}
	return 0;
}
