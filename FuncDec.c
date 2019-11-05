#include "Header.h"

/* Tree structure */
typedef struct Tree
{
	void *key;
	int id;
	struct Tree* LEFT;
	struct Tree* RIGHT;
}Tree, *PTree;

/* Adds a branch to the tree */
void AddBranch(PTree root,void* key ,func f)
{
	Tree* branch;

	if ((f(key,root->key) == 2)) // checks that id doesn't exist in tree

	{
		printf("Already in tree,value was not added to the tree.\n");
		return;
	}


	if (f(key, root->key) == 1) // if new key is larger than the current root 
	{
		if (root->RIGHT == NULL) // check if there is already a right child
		{
			branch = (PTree)malloc(sizeof(Tree)); // Allocate new branch
			if (branch == NULL)                   // Allocation check
			{
				printf("insufficient memory");
				return;
			}
			branch->key =key;                     // Transfer information to new branch's key
			branch->LEFT = NULL;                  // make sure both LEFT and RIGHT are NULL
			branch->RIGHT = NULL;               
			branch->id = 0;                       
			root->RIGHT = branch;                 // insert new branch to right child
		}
		else
			AddBranch(root->RIGHT, key, f);       // if right child exists re-enter func with right child as new root
	}
	if (f(key,root->key) == 0)                    // if new value is smaller than root value
	{
		if (root->LEFT == NULL)                   // if left child is non-existant
		{
			branch = (PTree)malloc(sizeof(Tree)); // Allocate new branch
			if (branch == NULL)                   // Allocation check
			{
				printf("insufficient memory");
				return;
			}
			branch->key = key;                    // Transfer information to new branch's key
			branch->LEFT = NULL;                  // make sure both LEFT and RIGHT are NULL
			branch->RIGHT = NULL;
			branch->id = 1;
			root->LEFT = branch;                  // insert new branch to left child
		}
		else
			AddBranch(root->LEFT, key, f);        // if right child exists re-enter func with right child as new root
	}
	
	return ;
}

/* creates main root */
void* CreateRoot(void* key)
{
	PTree root;
	root = (PTree)malloc(sizeof(Tree)); // Allocation
	if (root == NULL)                   // Allocation check
	{
		printf("insufficient memory");
		return;
	}
	root->key = key;                    // Transfer information to root's key
	root->id = 1;
	root->RIGHT = NULL;                 // make sure both LEFT and RIGHT are NULL
	root->LEFT = NULL;
	return root;                        // return root to main
}

/* Prints out the K smallest values in tree */
void PrintLow(Tree* root, void* maxkey, print_data printfunc, intval value, deckey deckeyval)
{
	int i = 0;
	if (root->LEFT == NULL)                                              // if LEFT child is NULL
	{
		i = value(maxkey);                                               // i recieves maxkey's value
		deckeyval(maxkey);                                               // decrease maxkey by 1
		if (i > 0)                                                       
			printfunc(root->key);                                        // if i > 0 print current root stored values
		if (root->RIGHT != NULL)
			PrintLow(root->RIGHT, maxkey, printfunc, value, deckeyval);  // if RIGHT child isn't NULL re-enter function with RIGHT child as root
		else
			return;                                                      // return if both childs are NULL
	}
	else if (root->RIGHT == NULL)                                        // if LEFT child isn't NULL and RIGHT child is
	{
		PrintLow(root->LEFT, maxkey, printfunc, value, deckeyval);       // Re-enter function with LEFT child as root
		i = value(maxkey);                                               // i recieves maxkey's value
		deckeyval(maxkey);                                               // decrease maxkey by 1
		if (i > 0)
			printfunc(root->key);                                        // if i > 0 print current root's stored values
	}
	else                                                                 // if both LEFT and RIGHT children aren't NULL
	{
		PrintLow(root->LEFT, maxkey, printfunc, value, deckeyval);       // Re-enter with LEFT as root
		i = value(maxkey);
		deckeyval(maxkey);
		if (i > 0)
			printfunc(root->key);
		PrintLow(root->RIGHT, maxkey, printfunc, value, deckeyval);
	}
}

/* function to print tree in post-order traversal */
void PrintPst(Tree* root, print_data printfunc)
{
	if (root->LEFT == NULL)                                             // if LEFT child is NULL
	{
		if (root->RIGHT != NULL)                                        // if RIGHT child isn't NULL
			PrintPst(root->RIGHT, printfunc);                           // Re-enter fumction with RIGHT child as root
		printfunc(root->key);                                           // Print current child's value/s
	}
	else if (root->RIGHT == NULL)                                       // if RIGHT child is NULL and left isn't
	{
		PrintPst(root->LEFT, printfunc);                                // Re-enter function with LEFT child as root
		printfunc(root->key);                                           // Print current root's value/s
	}
	else                                                                // if both aren't NULL go to LEFT first then RIGHT
	{
		PrintPst(root->LEFT, printfunc);
		PrintPst(root->RIGHT, printfunc);
		printfunc(root->key);                                           // Print current root's value/s
	}
}

/* returns desired value's position in tree */
int PrintPos(Tree* root, void* key, compare_func cmpf)
{
	int i;
	i = cmpf(root->key, key);                                          // i = (1 if root->key <= desired key and 2 if otherwise)
	if (root->LEFT == NULL)                                            // if LEFT child is NULL
	{
		if (root->RIGHT == NULL)                                       // if RIGHT child is NULL
			return i;
		return i + PrintPos(root->RIGHT, key, cmpf);                   // return i value plus RIGHT child return value
	}
	else if (root->RIGHT == NULL)                                      // if LEFT chils isn't NULL and RIGHT child is
		return i + PrintPos(root->LEFT, key, cmpf);                    // return i value plus LEFT child return value
	else                                                               // if both children aren't NULL
		return i + PrintPos(root->LEFT, key, cmpf) + PrintPos(root->RIGHT, key, cmpf); // return i value plus RIGHT and LEFT children's return value
}

/* deletes tree */
void DelTree(Tree* root, del_data todel)
{
	if (root->LEFT != NULL)             // if LEFT child isn't NULL
		DelTree(root->LEFT, todel);     // Re-enter function with LEFT child
	if (root->RIGHT != NULL)            // if RIGHT child isn't NULL
		DelTree(root->RIGHT, todel);    // re-enter function with LEFT child
	todel(root->key);                   // free current's value
	free(root);                         // free current
}
