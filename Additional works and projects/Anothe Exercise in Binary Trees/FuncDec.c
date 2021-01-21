#include "Header.h"


// f return the int value the key of the right type
BOOL AddBranch(Tree* root, void* key, compare_func f)
{
	Tree* branch;

	if ((f(key)) == f(root->key))

	{
		printf("Already in tree.\n");
		return FALSE;
	}


	if (f(key) > f(root->key))
	{
		if (root->RIGHT == NULL)
		{
			branch = (Tree*)malloc(sizeof(Tree));
			branch->key =key;
			root->RIGHT = branch;
			return TRUE;
		}
		AddBranch(root->RIGHT, key, f);
	}
	if (f(key) < f(root->key))
	{
		if (root->LEFT == NULL)
		{
			branch = (Tree*)malloc(sizeof(Tree));
			branch->key = key;
			root->LEFT = branch;
			return TRUE;
		}
		AddBranch(root->LEFT, key, f);
	}
	
	return FALSE;
}

int PrintPos(Tree* root, void* key, compare_func cmpf)
{
	int i;
	i = cmpf(root->key, key);
	if (root->LEFT == NULL)
	{
		if (root->RIGHT == NULL)
			return i;
		return i + PrintPos(root->RIGHT, key, cmpf);
	}
	else if (root->RIGHT == NULL)
		return i + PrintPos(root->LEFT, key, cmpf);
	else
		return i + PrintPos(root->LEFT, key, cmpf) + PrintPos(root->RIGHT, key, cmpf);
}

void PrintLow(Tree* root, void* maxkey, print_data printfunc, intval value, deckey deckeyval)
{
	int i = 0;
	if (root->LEFT == NULL)
	{
		i = value(maxkey);
		deckeyval(maxkey);
		if (i > 0)
			printfunc(root->key);
		if (root->RIGHT != NULL)
			PrintLow(root->RIGHT, maxkey, printfunc, value, deckeyval);
		else
			return;
	}
	else if (root->RIGHT == NULL)
	{
		PrintLow(root->LEFT, maxkey, printfunc, value, deckeyval);
		i = value(maxkey);
		deckeyval(maxkey);
		if (i > 0)
			printfunc(root->key);
	}
	else
	{
		PrintLow(root->LEFT, maxkey, printfunc, value, deckeyval);
		i = value(maxkey);
		deckeyval(maxkey);
		if (i > 0)
			printfunc(root->key);
		PrintLow(root->RIGHT, maxkey, printfunc, value, deckeyval);
	}
}

void PrintPst(Tree* root, print_data printfunc)
{
	if (root->LEFT == NULL)
	{
		if (root->RIGHT != NULL)
			PrintPst(root->RIGHT, printfunc);
		printfunc(root->key);
	}
	else if (root->RIGHT == NULL)
	{
		PrintPst(root->LEFT, printfunc);
		printfunc(root->key);
	}
	else
	{
		PrintPst(root->LEFT, printfunc);
		PrintPst(root->RIGHT, printfunc);
		printfunc(root->key);
	}
}