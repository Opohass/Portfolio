#include "Header.h"

typedef struct person
{
	int id;
	char* name;
}Person;

/* compare 2 ints, if rkey is smaller or equals to key return 1 else return 0 */
int cmp_int(void* rkey, void* key)
{
	if (*(int*)rkey <= *(int*)key)
		return 1;
	else
		return 0;
}

/* compare struct->key and int, if rkey is smaller or equals to key return 1 else return 0 */
int cmpS_int(void* rkey, void* key)
{
	if (((Person*)rkey)->id <= *(int*)key)
		return 1;
	else
		return 0;
}

/* prints an integer */
void print_val(void* data)
{
	printf("%d ", *(int*)data);
}

/* prints an integer from a struct */
void printS_val(void* data)
{
	printf("ID: %d Name: %s\n", ((Person*)data)->id, ((Person*)data)->name);
}

/* return int value */
int void_val(void* k)
{
	return *(int*)k;
}

/* return struct->int value */
int void_Sval(void* k)
{
	return ((Person*)k)->id;
}

/* decreases given integer value by 1 */
void dec_int(void * key)
{
	(*(int*)key)--;
}

/* returns 1 if num > num2, 2 if both are equal and 0 otherwise */
int UpdateInt(void* num,void* num2)
{
	if (*(int*)num >*(int*)num2)
		return 1;
	if (*(int*)num == *(int*)num2)
		return 2;
	return 0;
}
/* returns 1 if p1 > p2, 2 if both are equal and 0 otherwise */
int UpdateStruct(Person* p1,Person* p2)
{
	if (p1->id >p2->id)
		return 1;
	if (p1->id == p2->id)
		return 2;
	return 0;
}

/* returns value of of person->id */
int GetValueP(void* key)
{
	return ((Person*)(key))->id;
}

/* returns integer value */
int ReturnP(void* key)
{
	return *(int*)key;
}

/* free integer */
void del_val(void* data)
{
	free((int*)data);
}

/* free person->integer */
void del_Sval(void* data)
{
	free(((Person*)data)->name);
	free((Person*)data);
}
 
void main()
{
	Person* p = NULL;                        // pointer to allocated memory
	char type=NULL, temp[256];               // type = user selection I/S, temp = temporary input name
	int root, option=0,K , i;     // root = branch input value, option = desired user function, k = desired print value/amount to print, i = position
	int* NewBranch;                          // recieves value of integer
	void* treeroot;                          // recieves tree root address
	
	while (option != 5) // while the user doesn't wish to terminate program
	{
		printf("\n------------------------------------------------------------------\n");
		printf("\nMain Menu\n1:Add a branch.\n2:Print postorder keys.\n3:Print a desired value's position in tree.\n4:Print the K lowest values in the tree.\n5:Exit.\nYou choose:");
		scanf("%d", &option); // user selected option
		flushall();
		if (option == 1) // if user wishes to add a branch / create tree
		{
			if (type == NULL) //if a type wasn't previously selected
			{
				printf("\n------------------------------------------------------------------\n");
				printf("Choose rather you like the key to be structure or integer:(I/S) ");        // request to select integer or structure
				scanf("%c", &type);                            // input selection
				flushall();
				printf("\nplease enter the key value for the tree's root: ");  // input initial integer value
				scanf("%d", &root);   // recieves input
				flushall();
				if (type == 'S' || type == 's')    // checks for type (structure0
				{
					printf("\nWhat is the name you want for you root?"); // name input request
					scanf("%s", temp); // recieve input (temp)
					p = (Person*)malloc(sizeof(Person)); // memory allocation
					p->id = root;                        // enter user integer input into allocated struct
					p->name = (char*)malloc(sizeof(strlen(temp) + 1)); // allocate memory for name
					strcpy(p->name, temp);  // copies temp into allocated name space
					treeroot = CreateRoot(p); // create root
				}
				else // if selection (I/S) was already made previously
				{
					NewBranch = (int*)malloc(sizeof(int)); // memory allocation (int)
					*NewBranch = root;                     // inpur relocation to NewBranch
					treeroot = CreateRoot(NewBranch);      // create branch
				}
				printf("\n------------------------------------------------------------------\n");
			}
			if (type == 'I' || type == 'i') // create and allocate new branch if user selected i/I
			{
				{
					NewBranch = (int*)malloc(sizeof(int));
					if (NewBranch == NULL)
					{
						printf("insufficient memory");
						getch();
						return;
					}
					printf("\n------------------------------------------------------------------\n");
					printf("\nPlease enter the value you wish to add to the tree:"); // value input request
					scanf("%d", NewBranch);                                          // input value
					AddBranch(treeroot, NewBranch, UpdateInt);                       // add new branch
				}
			}
			if (type == 'S' || type == 's') // create and allocate new branch if user selected s/S
			{
				p = (Person*)malloc(sizeof(Person));
				if (p == NULL)
				{
					printf("insufficient memory");
					getch();
					return;
				}
				printf("\n------------------------------------------------------------------\n");
				printf("\nPlease enter the value you wish to add to the tree:");
				scanf("%d", &(p->id));
				printf("\nPlease enter the name for this branch:");
				scanf("%s", temp);
				p->name = (char*)malloc(strlen(temp) + 1);
				strcpy(p->name, temp);
				AddBranch(treeroot, p, UpdateStruct);
			}
			
			
		}
		if (option == 2) // print tree in post-order
		{
			if (type == 'I' || type == 'i') // sends appropriate function in case of integer only
				PrintPst(treeroot, print_val);
			else if (type == 's' || type == 'S') // sends appropriate function in case of structure
				PrintPst(treeroot, printS_val);
			else
				printf("Unregistered data type");
		}
		if (option == 3) // prints a desired value's position in tree (in-order)
		{
			printf("Enter a value to recieve current position in tree:"); // user input request 
			scanf("%d", &K);           // recieve user input
			if (type == 'I' || type == 'i') // send appropriate function in case of integer only
				i = PrintPos(treeroot, &K, cmp_int);
			else if (type == 's' || type == 'S') // send appropriate function in case of structure only
				i =PrintPos(treeroot, &K, cmpS_int);
			else
				printf("Unregistered data type\n");
			printf("Desired value's position is: %d\n", i); // print PrintPos return value
		}
		if (option == 4) // prints the k lowest (user input) values in tree
		{
			printf("Please enter the number of values you're looking for "); // user input request
			scanf("%d", &K); // recieve input
			flushall();

			if (type == 's' || type == 'S')   // send appropriate function in case of structure only
				PrintLow(treeroot, &K, printS_val, void_Sval, dec_int);
			else                              // send appropriate function in case of integer only
				PrintLow(treeroot, &K, print_val, void_val, dec_int);
			flushall();
		}
	}
	if (type == 's' || type == 'S') // delete tree if data is structure type
		DelTree(treeroot, del_Sval);
	else                            // delete tree if data is integer type only
		DelTree(treeroot, del_val);
	getch();
}


