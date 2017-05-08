#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include "yaio.h"
#include <string.h>

int main(int argc, char *argv[]) {
	struct winsize win_size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win_size);

	size_t a = 12345006;
	print_st(win_size.ws_row);
	return EXIT_SUCCESS;	
}

int parse_keys(int argc, char *argv[]) {
	for(int i = 0; i < argc; i++) {
		if(argv[i][0] != '-')
			return i;
		switch(argv[i][1]) {
			case 'a' : printf("Option \'a\' parsed.\n");
			case 'b' : printf("Option \'b\' parsed.\n");
			default : printf("Unknown option.\n");
		} 
	}
	return argc;
}

