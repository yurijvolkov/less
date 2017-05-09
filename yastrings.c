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