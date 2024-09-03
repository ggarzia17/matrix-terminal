#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "line.h"

#define LINE_LEN 15


void setup(){
    initscr();
    use_default_colors();
    curs_set(0);
    raw();
    noecho();
    cbreak();
    timeout(1);
    srandom(time(NULL));

    //colors
    start_color();
    init_pair(1, COLOR_BLACK, -1);
    init_pair(2, COLOR_RED, -1);
    init_pair(3, COLOR_GREEN, -1);
    init_pair(4, COLOR_YELLOW, -1);
    init_pair(5, COLOR_BLUE, -1);
    init_pair(6, COLOR_MAGENTA, -1);
    init_pair(7, COLOR_CYAN, -1);
    init_pair(8, COLOR_WHITE, -1);
    
}

int resetWindow(){
    refresh();
    int q = getch();
    if (q != ERR){
        return 1;
    }
    usleep(30000);
    erase();
    return 0;
}

void stepLines(line** lines, int len){
    for (int i = 0; i < len; i++){
        if (lines[i]){
            drawLine(lines[i]);
            step(lines[i]);
        }
    }
}

int main(int argc, char** argv){
    //init screen and set colors
    setup();
    int colors = argc > 1 && !strcmp(argv[1], "-r");

    //windows size
    int rows = 0;
    int cols = 0;
    getmaxyx(stdscr, rows, cols);

    line** lines = malloc(sizeof(line) * cols);
    memset(lines, 0, sizeof(*lines));
    //loop
    while(1){
        int newLine = 1;
        if(newLine){
            int col = random() % cols;
            for(int i = 0; i < 10 && lines[col]; i++){
                col = random() % cols;
            }
            if(!lines[col]){
                int color = COLOR_GREEN;
                if(colors){
                    color = random() % 8;
                }
                lines[col] = createLine(LINE_LEN, col, color, rows);
            }
        }

        cleanLines(lines, cols);
        stepLines(lines, cols);
        if(resetWindow()){
            break;
        }

    }
    endwin();

    return 0;
}