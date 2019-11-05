#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Defines Student struct */
typedef struct {
	char code[4];
	char stud_id[16];
	char studname[17];
}Student;

void Get_Lost(char *);
void Find(FILE *, char *course);

int main()
{
	char course[4];
	FILE *file;
	file = fopen("Stud.txt", "rt");
	if (file == NULL)
		Get_Lost("Cannot open file");
	printf("\nEnter the name of course,up to 3 letters: ");
	gets(course); // Gets course code
	Find(file, course);
	fclose(file);
	return 0;
}


void Get_Lost(char *s)
{
	puts(s);
	exit(1);
}

/* The Find func recieves the ptr for the file and the chosen course and sorts it */
void Find(FILE *in, char *course)
{
	int ibtemp;
	char temp[5];
	char filename[8];
	FILE *out;
	Student tempstud;
	/* Gets the name for the file */
	strcpy(filename, course);
	strcat(filename, ".txt");
	out = fopen(filename, "w"); // Opens file for writing with the chosen file name
	if (out == NULL)
		Get_Lost("Couldn't create file");
	fgets(tempstud.code, 4, in);
	while (feof(in) == 0) // Sorting the information to check if appropriate for file entry
	{
		fgets(temp, 5, in);
		ibtemp = atoi(temp); // turns the inputed char numbers to int
		itoa(ibtemp, tempstud.stud_id, 2); // turns the int number to binary
		fgets(tempstud.studname, 17, in);
		if (strcmp(tempstud.code, course) == 0)
		{
			fprintf(out, "%s, %s, %s\n",tempstud.stud_id, tempstud.studname, tempstud.code); // Print to file if condition is met
		}
		fgets(tempstud.code, 4, in); // Recieves the next course code for the next loop
	}
	fclose(out);
}