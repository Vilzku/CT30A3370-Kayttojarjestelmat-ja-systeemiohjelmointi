// my-cat.c
// Prints out contents of input file(s) to stdout.

#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 1024
// There was no mention of maximum linesize in the assignment
// Yet using fgets() was recommended. We decided to just use 1024.

int main(int argc, char const *argv[])
{
	int i;

	// If no input file is given
	if (argc == 1)				
		exit(0);

	// Loop through every input file
	for (i=1;i<argc;i++) {		
		char s[MAXLEN];
		FILE* fp = fopen(argv[i], "r");
		if (fp == NULL) {
			printf("my-cat: cannot open file\n");
			exit(1);
		}
		// Loop through every line in current file, printing them out as we go
		while (fgets(s, MAXLEN, fp) != NULL) {
			printf("%s", s);
		}
		fclose(fp);
	}
	return 0;
}