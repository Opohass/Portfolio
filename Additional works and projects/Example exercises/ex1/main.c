#include "Header.h"

/* add sum and num */
void Int_Sum(void *sum, void *num)
{
	*(int*)sum += *(int*)num;
}

/* sub sum and num */
void Int_Sub(void *sum, void *num)
{
	*(int*)sum -= *(int*)num;
}

/* initialize data */
void Init(void *p)
{
	*(int*)p = 0;
}

/* compares 2 integers */
int Int_Comp(void *a, void *b)
{
	if (*(int*)a == *(int*)b)
		return 1;
	return 0;
}


int main()
{
	int num[] = { 5, 8, 23, 20, 23 }, i, answer;
	void *p_num[N];
	void(*p_Init)(void*) = Init;
	void(*p_Sum)(void*, void*) = Int_Sum;
	void(*p_Sub)(void*, void*) = Int_Sub;
	int(*p_Comp)(void*, void*) = Int_Comp;

	for (i = 0; i < N;i++)
		(int*)p_num[i] = &num[i];
	answer = Do_It(&answer, p_num, p_Init, p_Sum, p_Sub, p_Comp);/*checks for */
	if (answer == 1)
		printf("The answer is 'Yes'");/* such a number exists*/
	else
		printf("The answer is 'No'");/* no such number exists*/
	getch();
	return 0;
}