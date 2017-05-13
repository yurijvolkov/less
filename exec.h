#include "loader.h"
#define NEXT_FILE_COMMAND 'z' 

#define NEXT_LINE_COMMAND_1 'j'
#define NEXT_LINE_COMMAND_2 'e'
#define NEXT_LINE_COMMAND_3 10

#define PREV_LINE_COMMAND_1 'k'
#define PREV_LINE_COMMAND_2 'y'

#define NEXT_PAGE_COMMAND_1 'f'
#define NEXT_PAGE_COMMAND_2 ' '

#define PREV_PAGE_COMMAND 'b'

#define NEXT_HALF_PAGE_COMMAND 'd'
#define PREV_HALF_PAGE_COMMAND 'u'

#define QUIT_COMMAND_1 'q'
#define QUIT_COMMAND_2 'Q'

#define FIND_COMMAND '/'

int exec (char command, Context *ctx);
