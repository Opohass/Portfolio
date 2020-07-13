#include "Header.h"


typedef struct  ListNode
{
	void* data;
	struct  ListNode *next;
} ListNode;

BOOL insertEntry(PNode* head, PNode* tail, void *data, compare_func func)
{
	PNode temp  = (*head);

	while (temp)
	{
		if (func(temp->data, data))
			return FALSE;
		temp = temp->next;
	}
	if (!(temp = (PNode)malloc(sizeof(ListNode))))
			return FALSE;
	temp->data = data;
	temp->next = NULL;
	if (*head == NULL)
		 *head = temp;
	else
		(*tail)->next = temp;
	*tail = temp;
	return TRUE;
	
}

BOOL deleteNode(PNode* head, PNode* tail, void *todel, compare_func func1, free_func func2)
{
	PNode curr,prev;
	curr = prev =(*head);
	while (!(func1(curr->data, todel)) && curr)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL)
		return FALSE;
	if (curr == (*head))
		*head = (*head)->next;
	if (curr == (*tail))
	{
		*tail = prev;
		(*tail)->next = NULL;
	}
	else
		prev->next = curr->next;
	func2(curr->data);
	free(curr);
	return TRUE;
}
void printAll(PNode head, print_func func)
{
	PNode temp = head;
	printf("The list is:\n");
	while (temp)
	{
		func(temp->data);
		temp = temp->next;
	}
}
void freeAll(PNode* head, free_func func)
{
	PNode temp = (*head);
	while (temp)
	{
		func((*head)->data);
		(*head) = (*head)->next;
		free(temp);
		temp = (*head);
	}
}