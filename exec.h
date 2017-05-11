#include "loader.h"
#define NEXT_FILE_COMMAND 'z' 
#define NEXT_LINE_COMMAND 'j'
#define PREV_LINE_COMMAND 'k'
#define NEXT_PAGE_COMMAND 'f'
#define QUIT_COMMAND 'q'
int exec (char command, Context *ctx);
