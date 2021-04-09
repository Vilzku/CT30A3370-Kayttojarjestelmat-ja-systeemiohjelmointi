#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
	int argument;
	if(strcmp(argv[1], "-r") == 0) {
		argument = -1;
		printf(1, "Counter has been reset, last value was: ");
	} else {
		argument = atoi(argv[1]);
	}

	printf(1, "%d\n", getcnt(argument));
	exit();
}