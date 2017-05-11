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
#include "buffer.h"

int _max(int a, int b) {
    return a > b ? a : b;
}

int prev_line(Context *ctx, struct winsize win_size) {
    int start_offset;
    int read_count;

    scrl(-1);
  
    return 0;
}

int next_line_buf(Context *ctx, struct winsize win_size, int n) {
    int r_code;
    int start_id;
    int x, y;

    start_id = 0;
    if(ctx->cur_line + n <= ctx->max_line) {
        if(ctx->cur_line >= 0)
            start_id = ctx->lines[ctx->cur_line];
        
        getyx(stdscr,y,x);
        if(y == win_size.ws_row - 2){
            scrl(n);
            y-=n;
        }
        
        
        mvaddnstr(y,x,ctx->buf_forward + start_id, ctx->lines[ctx->cur_line+n]-start_id);
        ctx->cur_ofsset = ctx->lines[ctx->cur_line+n] + ctx->buf_start;
        ctx->cur_line += n;
     
        return 0;
    }

    while(ctx->cur_line + 1 <= ctx->max_line) {
        start_id = ctx->lines[ctx->cur_line];

        addnstr( ctx->buf_forward + start_id, ctx->lines[ctx->cur_line + 1] - start_id );
        ctx->cur_ofsset = ctx->lines[ctx->cur_line+1] + ctx->buf_start;
        ctx->cur_line ++;
        n--;
    }

    bufferise(ctx, win_size);
    return next_line_buf(ctx, win_size, n);

}

int next_page(Context *ctx, struct winsize win_size){
    int lines;

    lines = win_size.ws_row;
    while(--lines > 0 )
        next_line_buf(ctx, win_size, 1);
    
    return 0;
}

int exec (char command, Context *ctx) {
    struct winsize win_size;
    char input;
    char ret_code;
 
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win_size); 
    
    if(ctx->cur_desc == -1){
        ctx->cur_desc = open(ctx -> file_names[ctx->cur_file], O_RDONLY);
    }

    switch(command)  {
        case NEXT_FILE_COMMAND :
            bufferise(ctx, win_size);
            next_page(ctx, win_size);
            break;  
        case NEXT_LINE_COMMAND:
            next_line_buf(ctx, win_size,1);
            break;  
        case PREV_LINE_COMMAND:
            prev_line(ctx, win_size);
            break;
        case NEXT_PAGE_COMMAND:
            next_page(ctx, win_size);
            break;
        case QUIT_COMMAND:
            return 0;
        default :
            printw("Undefined commands");
    }

    refresh();
    wmove(ctx->win,0,0);
    waddch(ctx->win, ':');
    input = wgetch(ctx->win);
    exec(input, ctx);

}
