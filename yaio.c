#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "yaio.h"
#include <curses.h>

int print_s(char *s) {
    write(1, s, strlen(s));
    return 0;
}

int print_s_r(char *s, size_t count) {
    write(1, s, count);
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

    do {
        str[cur_pos--] = v % 10 + 48;
        v /= 10;
    } while(v > 0);

    strcpy(res , str + cur_pos + 1);
    return 0;
}

int print_str(char *s, int width) {
    int i;

    i = 0; 
    while(s[i] != '\n' && --width > 0)
        addch(s[i++]);
    addch('\n');
    return i+1;
}

int print_str_buf(char* buf, int width, int start) {
    int i;
    i = start; 
    while(buf[i] != 0 && buf[i] != '\n' && --width > 0)
        addch(buf[i++]);
    addch('\n');

    return i+1-start;
}


int print_n_str_buf(char* buf, int width, int start, int n) {
   int i;
   int _width;

   _width = width;
    i = start; 
    while(n-- > 0) {
        while(buf[i] != '\n' && --width > 0){
            addch(buf[i++]);
        }
        width = _width;
        i++;
        addch('\n');
    }
    return i-start;
    
}