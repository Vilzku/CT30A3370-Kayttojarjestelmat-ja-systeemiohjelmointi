#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int grep(char[], FILE*);

int main(int argc, char *argv[]) {

	// No searchterm given
	if(argc < 2) {
		printf("my-grep: searchterm [file ...]\n");
		exit(1);
	}
			
	// No input files given
	else if(argc == 2) {
		grep(argv[1], stdin);
	}

	else {

		// Loop through all given files
		for(int i=2; i<argc; i++) {

			// Open file and set as an input
			FILE* file = fopen(argv[i], "r");
			if(file == NULL) {
				printf("my-grep: cannot open file\n");
				exit(1);
			}
			grep(argv[1], file);
			fclose(file);
		}
	}

	return 0;
}

int grep(char searchterm[], FILE* stream) {

	char* line_buf;
	size_t bufsize = 0;
	while(getline(&line_buf, &bufsize, stream) != -1) {
		if(strstr(line_buf, searchterm) != NULL) {
			printf("%s", line_buf);
		}
	}
	free(line_buf);
	return 0;
}

