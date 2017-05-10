
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "yaio.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include "yastrings.h"
#include "commands.h"
#include "exec.h"
int line_down(Context *ctx, struct winsize win_size) {
    char buf[win_size.ws_col+1];
    int out_len;
    int read_count;

    memset(buf,0,win_size.ws_col+1 );

    read_count = pread(ctx ->cur_desc, buf, win_size.ws_col, ctx->cur_ofsset);
    
    out_len = first_indexof(buf, '\n');

    if(out_len != -1) {
        ctx->cur_ofsset += out_len + 1;
        print_s_r(buf, out_len);
    }
    else if(read_count > 0) {
        ctx->cur_ofsset += read_count;
        print_s_r(buf, read_count);
    }
     else
        print_s("EOF");
   
    print_s("\n");
   fflush(stdout);
}

int page_down(Context *ctx, struct winsize win_size) {
    int lines;

    lines = win_size.ws_row;
    while(--lines > 0) 
        line_down(ctx, win_size);
    
    return 0;
}

int _max(int a, int b) {
    return a > b ? a : b;
}

int line_up(Context *ctx, struct winsize win_size) {
    char buf[win_size.ws_col * win_size.ws_row ];
    int start_offset;
    int read_count;
    int real_offset;

    memset(buf, 0,win_size.ws_col * win_size.ws_row  );
    start_offset = _max( ctx -> cur_ofsset - win_size.ws_col * win_size.ws_row , 0);
    read_count = pread(ctx->cur_desc, buf, ctx->cur_ofsset - start_offset, start_offset);
    real_offset = prev_n_line(buf, '\n', win_size.ws_row+1, win_size.ws_col);
  
    
    if(real_offset == -1)
        ctx ->cur_ofsset = 0;
    else
        ctx->cur_ofsset = real_offset;
     page_down(ctx, win_size);
   
   
    return 0;
}
