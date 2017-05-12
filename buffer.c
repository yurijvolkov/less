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



int bufferise(Context *ctx, struct winsize win_size) {
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


