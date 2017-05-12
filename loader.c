#include "loader.h"
#include <stdlib.h>
#include "yaio.h"
#include "buffer.h"

int parse_keys(int argc, char *argv[], Context* ctx) {
	int i;
    for( i = 1; i < argc; i++) {
		if(argv[i][0] != '-')
			return i;
        switch(argv[i][1]) {
			case 'a' : 
                ctx -> flags[0] = 1;
                break;
			case 'b' : 
                ctx -> flags[1] = 1;
                break;
			default : print_s("Unknown option.\n");
		} 
	}
	return argc;
}

int initialise_ctx(int argc, char* argv[],  Context **ctx) {
    int first_file;
	struct winsize win_size;

    *ctx = (Context*)malloc(sizeof(Context));

    first_file = parse_keys(argc, argv, *ctx);
    (*ctx) -> file_names = argv + first_file;
    (*ctx) -> cur_file = 0;
    (*ctx) -> files_count = argc - first_file;
    (*ctx) -> cur_ofsset = 0;
    (*ctx) -> cur_desc = -1;


    //cbreak();
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win_size);
    (*ctx) -> win = newwin(1, win_size.ws_col, win_size.ws_row - 1, 0);
    wrefresh( (*ctx) -> win);
    
    stdscr = newwin(win_size.ws_row - 1, win_size.ws_col, 0,0);
    scrollok(stdscr,TRUE);
	noecho();
    //idlok(stdscr, TRUE);
    refresh();

    return 0;
}
