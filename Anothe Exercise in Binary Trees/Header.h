#ifndef _FuncDec
#define _FuncDec
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef int(*compare_func)(void*, void*);
typedef int(func)(void*);
typedef int(*intval)(void*);
typedef void(*print_data)(void*);
typedef void(*deckey)(void*);
typedef enum{ FALSE, TRUE } BOOL;

typedef struct Tree
{
	void *key;
	int id;
	struct Tree* LEFT;
	struct Tree* RIGHT;
}Tree;


BOOL AddBranch(Tree* ,void*, compare_func);
int PrintPos(Tree*,void*,compare_func);
void PrintLow(Tree*, void*, print_data, intval, deckey);
void PrintPst(Tree*, print_data);
void* FuncStruct(void*);









#endif