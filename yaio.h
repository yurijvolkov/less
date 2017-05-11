#include <unistd.h>
#include <string.h>
#include <stdio.h>

int print_s(char *s);
int print_st(size_t v);
int print_s_r(char *s, size_t count);
int st_to_str(char *res, size_t v);
int print_str(char *s, int width);
int print_str_buf(char* buf, int width, int start);
int print_n_str_buf(char* buf, int width, int start, int n);