#ifndef _FuncDec
#define _FuncDec
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef int(func)(void*);                                  // compares 2 integers and returns 2,1 or 0
typedef struct Tree Tree,* PTree;                          // struct tree names
typedef int(*intval)(void*);                               // returns integer value
typedef void(*print_data)(void*);                          // print data from tree intersection
typedef void(*deckey)(void*);                              // decrease integer by 1
typedef void(*del_data)(void*);                            // free allocated data
typedef int(*compare_func)(void*, void*);                  // compares 2 integers and returns 1 or 0

void PrintLow(PTree, void*, print_data, intval, deckey);   // print k lowest values in tree
void AddBranch(PTree, void*,func);                         // add branch to current tree
int PrintPos(Tree*, void*, compare_func);                  // returns position of desired value in tree
void PrintPst(Tree*, print_data);                          // print tree in post-order
void DelTree(Tree*, del_data);                             // free tree data
void* CreateRoot(void*);                                   // creates first root in tree







#endif