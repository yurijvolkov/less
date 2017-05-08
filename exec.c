#include "loader.h"
#include "exec.h"

int exec (int command, Context* ctx) {
    switch(command)  {
        case NEXT_FILE_COMMAND :
            print_s("executing NEXT_FILE");
            break;
        default :
            print_s("Undefined command");

    }
}