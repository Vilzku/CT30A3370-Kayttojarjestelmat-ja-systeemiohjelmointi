#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

	// Not any files given
	if(argc < 2) {
		printf("my-unzip: file1 [file2 ...]\n");
		exit(1);
	}

	int count = -1;
	int character = -1;

	// Loop through all given files
	for(int i=1; i<argc; i++) {

		// Open file
		FILE* file = fopen(argv[i], "r");
		if(file == NULL) {
			printf("my-unzip: cannot open file\n");
			exit(1);
		}

		// Loop through the compressed characters
		while(fread(&count, 4, 1, file) > 0 && 
			fread(&character, 1, 1, file) > 0) {

			for(int i=0; i<count; i++)
				printf("%c", character);
		}
		
		fclose(file);
	}

	return 0;
}