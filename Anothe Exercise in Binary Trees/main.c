#include "Header.h"

int cmp_int(void* rkey, void* key)
{
	if (*(int*)rkey <= *(int*)key)
		return 1;
	else
		return 0;
}

int cmpS_int(void* rkey, void* key)
{
	if (((Person*)rkey)->id <= *(int*)key)
		return 1;
	else
		return 0;
}

void print_val(void* data)
{
	printf("%d ", *(int*)data);
}

void printS_val(void* data)
{
	printf("ID: %d Name: %s\n", ((Person*)data)->id, ((Person*)data)->name);
}

int void_val(void* k)
{
	return *(int*)k;
}

int void_Sval(void* k)
{
	return ((Person*)k)->id;
}

void dec_int(void * key)
{
	(*(int*)key)--;
}
typedef struct person
{
	int id;
	char * name;
}Person;

void main()
{
	char type;
	printf("Choose rather you like the key to be structure or integer:(I/S) ");
	scanf("%c", &type);

}