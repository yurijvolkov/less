#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "yaio.h"

int print_s(char *s) {
    write(1, s, strlen(s));
    return 0;
}

int print_st(size_t v) {
    char out[21];

    st_to_str(out, v);
    print_s(out);

    return 0;
}

int st_to_str(char *res, size_t v) {
    int max_len = 20;
    char str[max_len];
    int cur_pos = max_len - 2;

    str[max_len - 1] = 0; 

    while(v > 0) {
        str[cur_pos--] = v % 10 + 48;
        v /= 10;
    }

    strcpy(res , str + cur_pos + 1);
    return 0;
}
