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

		// Loop through all lines
		while((char_buf = fgetc(file)) != EOF) {

			if(char_buf == character) {
				count++;
			} else {
				if(count > 0) {
					fwrite(&count, 4, 1, stdout);
					fwrite(&character, 1, 1, stdout);
				}
				character = char_buf;
				count = 1;
			}
		}

		// hexdump -C out <---------------------------------------

		// pittää vielä loppuun kirjottaa \n ku se i ei tuu sieltä itestää
		character = '\n';
		//fwrite(&count, sizeof(int), 1, stdout); <--- ei toimiiiiiiiiiiiiiii
		//fwrite(&character, sizeof(char), 1, stdout);

		fclose(file);
	}

	return 0;
}