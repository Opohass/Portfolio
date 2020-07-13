#include "Header.h"

void free_char(void * data)
{
	free(data);
}
BOOL cmp_char(void* a, void* b)
{
	int i;
	if (*(char*)a  == *(char*)b)
		return TRUE;
	return FALSE;
}

void print_char(void * data)
{
	printf("%c \n", *(char*)data);
}


int main()
{
	char ch, *temp;
	int n, i;
	BOOL res;
	PNode head = NULL, tail = NULL;

	printf("Enter number of characters ");
	scanf("%d", &n);
	printf("\nEnter %d characters,separated by enter", n);
	for (i = 0; i<n; i++)
	{
		temp = (char*)malloc(sizeof(char));
		if (NULL == temp)
		{
			printf("\nCan't allocate data memory");
			freeAll(&head, free_char);
			return 1;
		}
		scanf(" %c", temp);
		res = insertEntry(&head, &tail, temp, cmp_char);
		if (FALSE == res)  /* if FALSE==res than there is something wrong with malloc */
		{
			printf("\nCan't allocate node memory or data is allready exists");
			freeAll(&head, free_char);
			return 1;
		}
	}
	printAll(head, print_char);

	printf("\nEnter an element for deleting");
	scanf(" %c", &ch);
	res = deleteNode(&head, &tail, &ch, cmp_char, free_char);
	if (FALSE == res)
		printf("%c don't exists in list\n", ch);

	printAll(head, print_char);

	freeAll(&head, free_char);
	printf("\nYour list was destroyed\n");
	getch();
	return 0;
}