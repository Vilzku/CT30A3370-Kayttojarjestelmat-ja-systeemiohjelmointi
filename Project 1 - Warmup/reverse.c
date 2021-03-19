// reverse.c
// Read lines from user-specified input (either a file or stdin)
// And prints read line in reverse order to stdout or user-specified file

// Sources:
//		Getfile usage: https://c-for-dummies.com/blog/?p=1112
//		Main structure of the program: Week 9 exercise 4
//		

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lines
{
	char * string;
	struct lines * prev;
	struct lines * next;
};

int read_lines(struct lines **line, FILE * stream)
{
	char *buf;
	size_t bufsize = 32; 	// Not an assumption. Getline() just needs some value
							// for the initial buffer size.  According to man getline,
							// getline() updates this value dynamically with realloc()
							// if the read line is longer.
	struct lines * lp;	

	// Buffer allocation
	buf = (char*)malloc(bufsize * sizeof(char*));
	if (buf == NULL) {
		fprintf(stderr, "Malloc failed\n");
		exit(1);
	}
	
	while (getline(&buf, &bufsize, stream) != -1) {
		
		if (*line == NULL) {
			if ((*line = lp = malloc(sizeof(struct lines))) == NULL) {
				fprintf(stderr, "Malloc failed\n");
				return -1;
			}
			lp->prev = lp->next = NULL;
		} else {
			if ( (lp->next = malloc(sizeof(struct lines))) == NULL) {
				fprintf(stderr, "Malloc failed\n");
				return -1;
			}

			lp->next->prev = lp; // Seuraavan noden prev-kohtaan nykyinen node
			lp = lp->next;		 // Siirrytään seuraavaan nodeen

		}
		
		if ( (lp->string = malloc(strlen(buf) + 1)) == NULL) {
			fprintf(stderr, "Malloc failed\n");
			return -1;
		}
		
		strcpy(lp->string, buf);
	}
	
	return 0;
}

void print_lines(struct lines *line, FILE * stream)
{
	struct lines * lp;
	lp = line;
		while (lp->next != NULL) {		// Kuljetaan listan loppuun, viimeisellä alkiolla ei ole next-alkiota
			lp = lp->next;
		}

		while (lp->prev != NULL) {		// Kuljetaan takaisin alkuun, ensimmäisellä alkiolla ei ole prev-alkiota
			fputs(lp->string, stream);	// Tulostetaan jokaisen noden string
			lp = lp->prev;
		}
	fputs(lp->string, stream);
}

void delete_lines(struct lines * line)
{
	struct lines * lp;
	lp = line;
	while (lp != NULL) {
		line = lp->next;
		free(lp->string);
		free(lp);
		lp = line;
	}
}


int main(int argc, char* argv[])
{

	struct lines * line = NULL;


	if (argc == 1) {

		// Luetaan stdinistä ja kirjoitetaan stdoutiin, sama koodi kuin viikkotehtävässä
		if (read_lines(&line, stdin) == -1)
			exit(1);

		print_lines(line, stdout);
		delete_lines(line);
	

	} else if (argc == 2) {

		// Luetaan annetusta tiedostosta ja kirjoitetaan stdoutiin

		FILE* fp;

		if ((fp = fopen(argv[1], "r")) == NULL) {
			fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
			exit(1);
		}

		if (read_lines(&line, fp) == -1)
			exit(1);
		
		fclose(fp);
		print_lines(line, stdout);
		delete_lines(line);

	} else if ((argc == 3) && (strcmp(argv[1], argv[2]) == 0)) {
		fprintf(stderr, "input and output must differ.\n");
		exit(1);

	} else if (argc == 3) {

		// Luetaan annetusta tiedostosta argv[1] ja kirjoitetaan annettuun tiedostoon argv[2]

		FILE* fp;

		if ((fp = fopen(argv[1], "r")) == NULL) {
			fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
			exit(1);
		}

		if (read_lines(&line, fp) == -1)
			exit(1);

		fclose(fp);

		if ((fp = fopen(argv[2], "w")) == NULL) {
			fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
			exit(1);
		}
		
		print_lines(line, fp);
		delete_lines(line);
		fclose(fp);

	} else {
		fprintf(stdout, "Usage: reverse <input> <output>\n");
		exit(1);
	}
	
	return 0;


