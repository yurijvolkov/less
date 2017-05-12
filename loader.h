#include <curses.h>

#define BUF_SIZE 10000
typedef struct {
    char **file_names;
    char* buf_forward;
    char* buf_backward;
    int buf_f_size;
    int buf_start;

    int cur_file;
    int cur_ofsset;

    int cur_desc; 
    int files_count; 
    int flags[20];

    int cur_line;
    int max_line;
    int* lines;
    WINDOW* win;
} Context;

int parse_keys(int argc, char *argv[], Context *ctx ) ;

int initialise_ctx(int argc, char* argv[],  Context **ctx) ;
