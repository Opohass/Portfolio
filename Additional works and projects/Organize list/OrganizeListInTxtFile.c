#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX 256

/* Defines Book and Library structs */
typedef struct{
	char code[10];
	char *bookname;
}Book;

typedef struct {
	char name[MAX];
	int num_books;
	Book *arr;
}Library;

/* Declares functions for program */
void Get_Lost(char* str);
void input_book(Book* B, FILE *in);
void input_library(Library *L, FILE *in);
void output_book(Book* B, FILE *out);
void output_library(Library* L, FILE *out);

void main()
{
	FILE *in, *out;
	Library Libr;
	int i;
	if (!(in = fopen("input.txt", "r")))                   // Opening input file and checking if opened
		printf("Failed to open file");
	else
	{
		input_library(&Libr, in);
		fclose(in);
		if (!(out = fopen("output.txt", "w")))             // Creating file and checking if created
			printf("Failed to create file");
		else
		{
			output_library(&Libr, out);
			fclose(out);
			for (i = 0; i < Libr.num_books; i++)
			{
				free(Libr.arr[i].bookname);
			}
			free(Libr.arr);
		}
	}
}


/* Recieves information and creating appropriate amount of Books */
void input_library(Library *L, FILE *in){
	int i;
	fscanf(in, "%s %d", L->name, &(*L).num_books);
	(*L).arr = (Book*)malloc((*L).num_books*sizeof(Book)); // Creates an array of books
	if ((*L).arr == NULL)  // Allocation check
	{
		printf("Allocation failed");
	}
	else
	{
		for (i = 0; i < (*L).num_books; i++)
		{
			input_book(&(*L).arr[i], in);                 //Sending each of the Books allocated to func: input_book
		}
	}
}

/* Recieves ptr for book in Libr.arr and trasfers information to it */
void input_book(Book* B, FILE *in){
	int i = 0;
	char temp[MAX];
	int len;
	fscanf(in, "%s%s", B->code, temp);
	len = strlen(temp);
	B->bookname = (char*)malloc(len * sizeof(char) + 1); // Memory allocation for bookname
	if (B->bookname == NULL)                             // Allocation check
		printf("Allocation failed");
	else
		strcpy(B->bookname, temp);
}

/* Writes library information to output file and sends books to func: output_book */
void output_library(Library* L, FILE *out){
	int i;
	fprintf(out, "%s\n\n", L->name);
	for (i = 0; i < L->num_books; i++)
	{
		output_book(&L->arr[i], out);
	}
}

/* Writes code and book name to output file */
void output_book(Book* B, FILE *out) {
	fprintf(out, "%-10s %s\n", B->code, B->bookname);
}