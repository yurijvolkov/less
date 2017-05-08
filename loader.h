typedef struct {
    char **file_names;
    int cur_file;
    int files_count; //TODO: REFACTOR FIELD NAMES
    int flags[20];
} Context;

int parse_keys(int argc, char *argv[], Context *ctx ) ;

int initialise_ctx(int argc, char* argv[],  Context **ctx) ;