#include "loader.h"
#include <stdlib.h>
#include "yaio.h"

int parse_keys(int argc, char *argv[], Context* ctx) {
	for(int i = 1; i < argc; i++) {
		if(argv[i][0] != '-')
			return i;
        switch(argv[i][1]) {
			case 'a' : 
                print_s("Option \'a\' parsed.\n"); 
                ctx -> flags[0] = 1;
                break;
			case 'b' : 
                print_s("Option \'b\' parsed.\n"); 
                ctx -> flags[1] = 1;
                break;
			default : print_s("Unknown option.\n");
		} 
	}
	return argc;
}

int initialise_ctx(int argc, char* argv[],  Context **ctx) {
    int first_file;
	
    *ctx = (Context*)malloc(sizeof(Context));

    first_file = parse_keys(argc, argv, *ctx);
    (*ctx) -> file_names = argv + first_file;
    (*ctx) -> cur_file = 0;
    (*ctx) -> files_count = argc - first_file;
    return 0;
}