// my-zip.c
// Compresses the file with Run-Length-Encoding

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

	// Not any files given
	if(argc < 2) {
		printf("my-zip: file1 [file2 ...]\n");
		exit(1);
	}

	int count = -1;
	int character = -1;
	int char_buf;

	// Loop through all given files
	for(int i=1; i<argc; i++) {

		// Open file
		FILE* file = fopen(argv[i], "r");
		if(file == NULL) {
			printf("my-zip: cannot open file\n");
			exit(1);
		}

		// Loop through all characters
		int loop = 1;
		do {

			// End of file
			if((char_buf = fgetc(file)) == EOF) {
				char_buf = '\n';
				loop = 0;
			}

			// Increase count
			if(char_buf == character) {
				count++;

			// Write count and character
			} else {
				if(count > 0) { // First character
					fwrite(&count, 4, 1, stdout);
					fwrite(&character, 1, 1, stdout);
				}
				character = char_buf;
				count = 1;
			}
		} while (loop);

		fclose(file);
	}

	// Compress last newline characters if there are any
	if(count > 1) {
		count--; // EOF is interpret as \n
		fwrite(&count, 4, 1, stdout);
		fwrite(&character, 1, 1, stdout);
	}

	return 0;
}