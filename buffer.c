#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "yastrings.h"
#include "exec.h"
#include "yaio.h"
#include <curses.h>

int get_line(Context *ctx,  struct winsize win_size) {
    int pos_in_buffer;
    int i;
    int length;

    length = 0;
    i = pos_in_buffer = ctx->cur_ofsset - ctx->buf_start;
 
    while(ctx->buf_forward[i] != '\n' && length++ < win_size.ws_col) {
        if(i++ >= ctx->buf_f_size)
            return -1;
    } 

    return i - pos_in_buffer + 1;
}



int bufferise_forward(Context *ctx, struct winsize win_size) {
    int i;
    int length;
    int crit1, crit2;
           
    ctx->buf_forward = (char*)malloc(sizeof(char)*BUF_SIZE);
    ctx->lines = (int*)malloc(sizeof(int)*BUF_SIZE);
    memset(ctx->lines, 0, BUF_SIZE);
    memset(ctx->buf_forward, 0, BUF_SIZE);
    
    ctx -> buf_f_size = pread(ctx->cur_desc, ctx->buf_forward, BUF_SIZE-1, ctx->cur_ofsset);
    ctx -> buf_start = ctx -> cur_ofsset;
    ctx -> max_line = -1;
    ctx -> cur_line = -1;
    length = 0;
    for(i = 0; i < ctx -> buf_f_size; i++) {
        if(++length == win_size.ws_col ||  ctx->buf_forward[i] == '\n' ) {
            ctx->lines[++(ctx->max_line)] = i;
            length = 0;
        }
    }

    return 0;
}

int max(int a, int b){
    return a > b ? a : b;
}

int make_lines(Context* ctx,  struct winsize win_size, int start_offset) {
    int first_line;
    int count_back_lines;
    int length;
    int pos_in_buf;

    pos_in_buf = start_offset - ctx->buf_start;
    count_back_lines = 0;
    first_line = pos_in_buf;
    length = 0;
    while(pos_in_buf-- >= 0) {
        if(ctx->buf_forward[pos_in_buf] == '\n' || ++length == win_size.ws_col) {
            first_line = pos_in_buf + 1;
            length = 0;
        }
    }

    if(ctx->buf_start == 0)
        first_line = 0;
    return first_line + ctx ->buf_start;
}

int bufferise(Context *ctx, struct winsize win_size ) {
    int start_offset;
    int i;
    int cur_line_start;
    int first_line;
    start_offset = ctx -> cur_ofsset;
    ctx->cur_ofsset = max(ctx->cur_ofsset - BUF_SIZE/2, 0);
    bufferise_forward(ctx, win_size);

    ctx->cur_ofsset = make_lines(ctx, win_size, start_offset);
    bufferise_forward(ctx, win_size);

    ctx->cur_ofsset = start_offset;
    
    i = 0;

    cur_line_start = ctx->buf_start;
    while(cur_line_start != start_offset) {
        i++;
        cur_line_start = ctx -> buf_start + ctx -> lines[i - 1];
    }

    ctx->cur_line = i-1;
    
    return 0;
}

