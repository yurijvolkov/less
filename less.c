#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <curses.h>
#include "exec.h"
#include <locale.h>
#include "buffer.h"

int main(int argc, char *argv[]) {
	struct termios _new, _old;
	Context* ctx;


    ioctl( STDIN_FILENO, TCGETS, &_new);
	_old = _new;
	_new.c_lflag =  ~(ICANON | ECHO) & _new.c_lflag ;
    _new.c_cc[VTIME] = 0;
    _new.c_cc[VMIN] = 1;
	ioctl( STDIN_FILENO, TCSETS, &_new);

    setlocale (LC_ALL, "");

	initscr();
	
    initialise_ctx(argc, argv, &ctx);
	
	exec(NEXT_FILE_COMMAND, ctx);
	
	endwin();
	ioctl( STDIN_FILENO, TCSETS, &_old);
	return EXIT_SUCCESS;	
}
