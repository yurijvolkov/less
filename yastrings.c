#include <string.h>
#include "yaio.h"

int first_indexof(char *s, char c) {
    int i;
    
    i = 0; 
    while(s[i] != 0) {
        if(s[i] == c)
            return i;
        i++;
    }
    return -1;
}

int last_n_indexof(char* s, char c, int n) {
    int i;
    i = strlen(s);
    while(n > 0 && i-- >= 0) {
        if(s[i] == c){
            n--;
        }
    }
    if(n == 0)
        return i;
    return -1;
}

int prev_n_line(char *s, char sep, int n, int line_length) {
    int i;
    int cur_line_length;

    i = strlen(s) - 1;
    cur_line_length = 0;
    while(n > 0 && i >= 0) {
        if(s[i--] == sep || cur_line_length == line_length) {
            cur_line_length = 0;
            n--;      
        } 
        else
            cur_line_length++;
    }

    return i+2;
}
