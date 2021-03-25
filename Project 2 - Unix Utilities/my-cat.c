// my-cat.c
// Prints out contents of input file(s) to stdout.

#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 1024


int main(int argc, char const *argv[])
{
	int i;

	for (i=1;i<argc;i++) {
		char *s = "";
		FILE* fp = fopen(argv[i], "r");
		if (fp == NULL) {
			perror("Couldn't open file.");
			exit(1);
		}

		while (fgets(s, MAXLEN, fp)) {
			printf("%s", s);
		}
	}

	return 0;
}